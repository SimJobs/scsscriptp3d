/*
    This file is part of SCSScript.

    Copyright (C) 2006-2012 by Nick Sharmanzhinov

    SCSScript is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SCSScript is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SCSScript.  If not, see <http://www.gnu.org/licenses/>.

    Nick Sharmanzhinov
    except134@gmail.com
*/

#include "PCH.h"

namespace SCSScript
{
	namespace SoundEngine
	{
		Sound::Sound(LPDIRECTSOUNDBUFFER* apDSBuffer,DWORD dwDSBufferSize,DWORD dwNumBuffers,WaveFile* pWaveFile,DWORD dwCreationFlags) 
			:	m_Volume(0),
			m_LoopEventHandle(0),
			m_DirectSoundNotify(0),
			m_MuteFlag(false)
		{
			if(dwNumBuffers<=0)
				return;

			m_Buffer=new LPDIRECTSOUNDBUFFER[dwNumBuffers];

			if(nullptr!=m_Buffer) {
				for(DWORD i=0;i<dwNumBuffers;i++)
					m_Buffer[i]=apDSBuffer[i];

				m_BufferSize			= dwDSBufferSize;
				m_NumberOfBuffers				= dwNumBuffers;
				m_WaveFile					= pWaveFile;
				m_CreationFlags			= dwCreationFlags;
				FillBufferWithSound(m_Buffer[0],false);
			}

			if(m_LoopEventHandle) {
				m_PositionNotify.dwOffset		= m_StopPosition;
				m_PositionNotify.hEventNotify	= m_LoopEventHandle;
			};
		}

		Sound::~Sound()
		{
			for(DWORD i=0;i<m_NumberOfBuffers;i++) {
				Helpers::SafeRelease(m_Buffer[i]);
			}
			Helpers::SafeDeleteArray(m_Buffer);
			Helpers::SafeDelete(m_WaveFile);
			if(m_LoopEventHandle)
				::CloseHandle(m_LoopEventHandle);
			Helpers::SafeRelease(m_DirectSoundNotify);
		}

		HRESULT Sound::FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB,BOOL bRepeatWavIfBufferLarger)
		{
			HRESULT hr;
			VOID*   pDSLockedBuffer     =nullptr;
			DWORD   dwDSLockedBufferSize=0;   
			DWORD   dwWavDataRead       =0;   

			if(pDSB==nullptr) {
				throw Exception("Direct sound buffer is null. May be CoInitialize has not been called?");
				return CO_E_NOTINITIALIZED;
			}

			if(m_WaveFile->m_SampleLoops) {
				if(FAILED(hr=pDSB->QueryInterface(IID_IDirectSoundNotify,(VOID**)&m_DirectSoundNotify))) {
					throw Exception(DXGetErrorDescription(hr));
				}
				m_LoopEventHandle=::CreateEvent(nullptr,true,false,nullptr);
				m_StartPosition=m_WaveFile->m_SampleLoops[0].dwStart*m_WaveFile->m_WaveFormat->nChannels*m_WaveFile->m_WaveFormat->wBitsPerSample/8;
				m_StopPosition=m_WaveFile->m_SampleLoops[0].dwEnd*m_WaveFile->m_WaveFormat->nChannels*m_WaveFile->m_WaveFormat->wBitsPerSample/8;
			};

			if(FAILED(hr=RestoreBuffer(pDSB,nullptr)))
				throw Exception(DXGetErrorDescription(hr));

			if(FAILED(hr=pDSB->Lock(0,m_BufferSize,&pDSLockedBuffer,&dwDSLockedBufferSize,nullptr,nullptr,0L)))
				throw Exception(DXGetErrorDescription(hr));

			m_WaveFile->ResetFile();

			if(FAILED(hr=m_WaveFile->Read((PBYTE)pDSLockedBuffer,dwDSLockedBufferSize,&dwWavDataRead)))
				throw Exception(DXGetErrorDescription(hr));

			if(dwWavDataRead==0) {
				FillMemory((PBYTE)pDSLockedBuffer,dwDSLockedBufferSize,(BYTE)(m_WaveFile->m_WaveFormat->wBitsPerSample==8?128:0));
			} else if(dwWavDataRead<dwDSLockedBufferSize) {
				if(bRepeatWavIfBufferLarger) {
					DWORD dwReadSoFar=dwWavDataRead;    
					while(dwReadSoFar<dwDSLockedBufferSize) {
						if(FAILED(hr=m_WaveFile->ResetFile()))
							throw Exception(DXGetErrorDescription(hr));

						hr=m_WaveFile->Read((PBYTE)pDSLockedBuffer+dwReadSoFar,dwDSLockedBufferSize-dwReadSoFar,&dwWavDataRead);
						if(FAILED(hr))
							throw Exception(DXGetErrorDescription(hr));

						dwReadSoFar+=dwWavDataRead;
					}
				} else {
					FillMemory((PBYTE)pDSLockedBuffer+dwWavDataRead,dwDSLockedBufferSize-dwWavDataRead,(BYTE)(m_WaveFile->m_WaveFormat->wBitsPerSample==8?128:0));
				}
			}

			pDSB->Unlock(pDSLockedBuffer,dwDSLockedBufferSize,nullptr,0);
			return S_OK;
		}

		HRESULT Sound::RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB,BOOL* pbWasRestored)
		{
			HRESULT hr;

			if(pDSB==nullptr)
				return CO_E_NOTINITIALIZED;
			if(pbWasRestored)
				*pbWasRestored=false;

			DWORD dwStatus;
			if(FAILED(hr=pDSB->GetStatus(&dwStatus)))
				throw Exception(DXGetErrorDescription(hr));

			if(dwStatus&DSBSTATUS_BUFFERLOST) {
				do {
					hr=pDSB->Restore();
					if(hr==DSERR_BUFFERLOST)
						Sleep(10);
				}while((hr=pDSB->Restore())==DSERR_BUFFERLOST);

				if(pbWasRestored!=nullptr)
					*pbWasRestored=true;

				return S_OK;
			} else {
				return S_FALSE;
			}
		}

		LPDIRECTSOUNDBUFFER Sound::GetFreeBuffer()
		{
			if(m_Buffer==nullptr)
				return false;

			DWORD i;
			for(i=0;i<m_NumberOfBuffers;i++) {
				if(m_Buffer[i]) {
					DWORD dwStatus=0;
					m_Buffer[i]->GetStatus(&dwStatus);
					if((dwStatus&DSBSTATUS_PLAYING)==0)
						break;
				}
			}

			if(i!=m_NumberOfBuffers)
				return m_Buffer[i];
			else
				return m_Buffer[rand()%m_NumberOfBuffers];
		}

		LPDIRECTSOUNDBUFFER Sound::GetBuffer(DWORD dwIndex)
		{
			if(m_Buffer==nullptr)
				return nullptr;
			if(dwIndex>=m_NumberOfBuffers)
				return nullptr;
			return m_Buffer[dwIndex];
		}

		HRESULT Sound::Play(DWORD dwFlags,DWORD dwPriority,LONG lVolume,LONG lFrequency,LONG lPan)
		{
			HRESULT hr;
			BOOL    bRestored;

			if(m_Buffer==nullptr)
				return CO_E_NOTINITIALIZED;

			LPDIRECTSOUNDBUFFER pDSB;
			if(m_LoopEventHandle)
				pDSB=m_Buffer[0];
			else
				pDSB=GetFreeBuffer();

			if(pDSB==nullptr)
				throw Exception("Direct sound buffer is null. May be CoInitialize has not been called?");

			if(FAILED(hr=RestoreBuffer(pDSB,&bRestored)))
				throw Exception(DXGetErrorDescription(hr));

			if(bRestored) {
				if(FAILED(hr=FillBufferWithSound(pDSB,false)))
					throw Exception(DXGetErrorDescription(hr));
			}

			if(m_CreationFlags&DSBCAPS_CTRLVOLUME) {
				if(lVolume)
					SetVolume(lVolume);
			}

			if(lFrequency!=-1&&(m_CreationFlags&DSBCAPS_CTRLFREQUENCY)) {
				pDSB->SetFrequency(lFrequency);
			}

			if(m_CreationFlags&DSBCAPS_CTRLPAN) {
				pDSB->SetPan(lPan);
			}

			if(m_LoopEventHandle) {
				if(!IsSoundPlaying()) {
					m_DirectSoundNotify->SetNotificationPositions(1,&m_PositionNotify);
					return pDSB->Play(0,dwPriority,dwFlags);
				} else {
					DWORD dwCurrentPlayCursor;
					m_Buffer[0]->GetCurrentPosition(&dwCurrentPlayCursor,nullptr);
					if(dwCurrentPlayCursor>m_StopPosition) {
						m_Buffer[0]->Stop();
						m_DirectSoundNotify->SetNotificationPositions(1,&m_PositionNotify);
						DWORD dwActualPos=m_BufferSize-dwCurrentPlayCursor;
						if(dwActualPos>m_StartPosition)
							dwActualPos=m_StartPosition;
						m_Buffer[0]->SetCurrentPosition(dwActualPos);
						return pDSB->Play(0,dwPriority,dwFlags);
					};
					return S_OK;
				};
				return S_OK;
			} else {
				pDSB->SetCurrentPosition(0);
				return pDSB->Play(0,dwPriority,dwFlags);
			}
		}

		HRESULT Sound::Stop()
		{
			if(m_Buffer==nullptr)
				return CO_E_NOTINITIALIZED;

			HRESULT hr=0;

			if(m_LoopEventHandle) {
				DWORD dwStatus;
				m_Buffer[0]->GetStatus(&dwStatus);
				if((dwStatus&DSBSTATUS_PLAYING)!=0) {
					m_Buffer[0]->Stop();
					DWORD dwCurrentPlayCursor;
					m_Buffer[0]->GetCurrentPosition(&dwCurrentPlayCursor,nullptr);
					m_DirectSoundNotify->SetNotificationPositions(0,nullptr);
					if(dwCurrentPlayCursor<m_StartPosition) {
						DWORD dwActualPos=m_BufferSize-dwCurrentPlayCursor;
						if(dwActualPos<m_StopPosition)
							dwActualPos=m_StopPosition+2*m_WaveFile->m_WaveFormat->nChannels*m_WaveFile->m_WaveFormat->wBitsPerSample/8;
						m_Buffer[0]->SetCurrentPosition(dwActualPos);
					} else if(dwCurrentPlayCursor<m_StopPosition) {
						m_Buffer[0]->SetCurrentPosition(m_StopPosition);
					}
					m_Buffer[0]->Play(0,0,0);
				}
			} else {
				for(DWORD i=0;i<m_NumberOfBuffers;i++)
					hr|=m_Buffer[i]->Stop();
			}
			return hr;
		}

		HRESULT Sound::Reset()
		{
			if(m_Buffer==nullptr)
				return CO_E_NOTINITIALIZED;

			HRESULT hr=0;

			for(DWORD i=0;i<m_NumberOfBuffers;i++)
				hr|=m_Buffer[i]->SetCurrentPosition(0);
			return hr;
		}

		BOOL Sound::IsSoundPlaying()
		{
			BOOL bIsPlaying=false;

			if(m_Buffer==nullptr)
				return false;

			for(DWORD i=0;i<m_NumberOfBuffers;i++) {
				if(m_Buffer[i]) {
					DWORD dwStatus=0;
					m_Buffer[i]->GetStatus(&dwStatus);
					bIsPlaying|=((dwStatus&DSBSTATUS_PLAYING)!=0);
				}
			}
			return bIsPlaying;
		}

		HRESULT Sound::SetVolume(int lVolume)
		{
			HRESULT hr=0;

			if(m_Volume!=lVolume) {
				m_Volume=lVolume;
				if(!m_MuteFlag) {
					for(DWORD i=0;i<m_NumberOfBuffers;i++)
						hr=m_Buffer[i]->SetVolume(m_Volume);
					return hr;
				}
			}
			return S_FALSE;
		}

		HRESULT Sound::Mute(int lVolume)
		{
			HRESULT hr=0;

			if(!m_MuteFlag) {
				m_MuteFlag=true;
				for(DWORD i=0;i<m_NumberOfBuffers;i++)
					hr=m_Buffer[i]->SetVolume(lVolume);
				return hr;
			}
			return S_FALSE;
		}

		HRESULT Sound::RestoreVolume(void)
		{
			HRESULT hr=0;

			if(m_MuteFlag) {
				m_MuteFlag=false;
				for(DWORD i=0;i<m_NumberOfBuffers;i++)
					hr=m_Buffer[i]->SetVolume(m_Volume);
				return hr;
			};
			return S_FALSE;
		}

		HRESULT	Sound::Pause(void)
		{
			HRESULT hr=0;
			for(DWORD i=0;i<m_NumberOfBuffers;i++)
				hr=m_Buffer[i]->Stop();
			return hr;
		}

		HRESULT Sound::Replay(void)
		{
			HRESULT hr=0;
			for(DWORD i=0;i<m_NumberOfBuffers;i++)
				hr=m_Buffer[i]->Play(0,0,0);
			return hr;
		}
	}
}

