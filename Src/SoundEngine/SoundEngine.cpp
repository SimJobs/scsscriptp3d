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
		SoundEngine::SoundEngine() :	m_pDS(0),
										s_bIsTerminating(false),
										s_nEventsCount(0),
										m_nSoundsCount(0)
		{
			for(DWORD i=0;i<MAX_SND_SOCKETS;i++) {
				m_Sounds[i]=nullptr;
			}
		}

		SoundEngine::~SoundEngine()
		{
		}

		void SoundEngine::Init(HWND hwnd,DWORD dwCoopLevel)
		{
			HRESULT hr=DS_OK;
			Helpers::SafeRelease(m_pDS);

			if(!hwnd)
				throw Exception("Active window handle is null");

			if(dwCoopLevel<DSSCL_NORMAL||dwCoopLevel>DSSCL_WRITEPRIMARY)
				dwCoopLevel=DSSCL_NORMAL;

			if(FAILED(hr=DirectSoundCreate8(nullptr,&m_pDS,nullptr)))
				throw Exception(DXGetErrorDescription(hr));

			if(FAILED(hr=m_pDS->SetCooperativeLevel(hwnd,dwCoopLevel)))
				throw Exception(DXGetErrorDescription(hr));

			s_hEvents[s_nEventsCount]=::CreateEvent(nullptr,true,false,nullptr);
			s_LoopSounds[s_nEventsCount]=nullptr;
			s_nEventsCount++;

			//m_hThread=::CreateThread(nullptr,0,SoundEventHandler,this,0,&m_dwThreadID);
			m_hThread=(HANDLE)_beginthreadex(0,0,&SoundEventHandler2,this,0,&m_dwThreadID);
		}

		void SoundEngine::DeInit()
		{
			s_bIsTerminating=true;
			::SetEvent(s_hEvents[0]);
			//::TerminateThread(m_hThread,0);
			CloseHandle(m_hThread);

			for(DWORD i=0;i<m_nSoundsCount;i++) {
				Helpers::SafeDelete(m_Sounds[i]);
			}
			Helpers::SafeRelease(m_pDS);
		}

		HRESULT SoundEngine::SetPrimaryBufferFormat(DWORD dwPrimaryChannels,DWORD dwPrimaryFreq,DWORD dwPrimaryBitRate)
		{
			HRESULT             hr;
			LPDIRECTSOUNDBUFFER pDSBPrimary=nullptr;

			if(m_pDS==nullptr) {
				throw Exception("Direct sound buffer is null. May be CoInitialize has not been called?");
				return CO_E_NOTINITIALIZED;
			}

			DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
			dsbd.dwSize       =sizeof(DSBUFFERDESC);
			dsbd.dwFlags      =DSBCAPS_PRIMARYBUFFER;
			dsbd.dwBufferBytes=0;
			dsbd.lpwfxFormat  =nullptr;

			if(FAILED(hr=m_pDS->CreateSoundBuffer(&dsbd,&pDSBPrimary,nullptr))) {
				throw Exception(DXGetErrorDescription(hr));
				return hr;
			}

			WAVEFORMATEX wfx;
			ZeroMemory(&wfx,sizeof(WAVEFORMATEX));
			wfx.wFormatTag     =(WORD)WAVE_FORMAT_PCM;
			wfx.nChannels      =(WORD)dwPrimaryChannels;
			wfx.nSamplesPerSec =(DWORD)dwPrimaryFreq;
			wfx.wBitsPerSample =(WORD)dwPrimaryBitRate;
			wfx.nBlockAlign    =(WORD)(wfx.wBitsPerSample/8*wfx.nChannels);
			wfx.nAvgBytesPerSec=(DWORD)(wfx.nSamplesPerSec*wfx.nBlockAlign);

			if(FAILED(hr=pDSBPrimary->SetFormat(&wfx))) {
				throw Exception(DXGetErrorDescription(hr));
				return hr;
			}

			Helpers::SafeRelease(pDSBPrimary);
			return S_OK;
		}

		BOOL SoundEngine::AddAndNotify(Sound* pSound)
		{
			m_Sounds[m_nSoundsCount++]=pSound;
			if(pSound->m_LoopEventHandle) {
				s_LoopSounds[s_nEventsCount]=pSound;
				s_hEvents[s_nEventsCount]=pSound->m_LoopEventHandle;
				s_nEventsCount++;
				::SetEvent(s_hEvents[0]);
			};
			return true;
		}

		HRESULT SoundEngine::Create(Sound** ppSound,char* strWaveFileName,HINSTANCE g_hInstance,DWORD dwCreationFlags,GUID guid3DAlgorithm,DWORD dwNumBuffers)
		{
			DWORD   i;
			HRESULT hr;
			HRESULT hrRet=S_OK;

			LPDIRECTSOUNDBUFFER* apDSBuffer    =nullptr;
			DWORD                dwDSBufferSize=0;
			WaveFile*            pWaveFile     =nullptr;

			if(!Helpers::FileExists(strWaveFileName))
				return E_FAIL;

			if(m_pDS==nullptr) {
				throw Exception("Direct sound buffer is null. May be CoInitialize has not been called?");
				return CO_E_NOTINITIALIZED;
			}

			if(strWaveFileName==nullptr||ppSound==nullptr||dwNumBuffers<1) {
				throw Exception("Something wrong with pointers.");
				return E_INVALIDARG;
			}

			apDSBuffer=new LPDIRECTSOUNDBUFFER[dwNumBuffers];
			if(apDSBuffer==nullptr) {
				Helpers::SafeDelete(pWaveFile);
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception("Out of memory");
				return E_OUTOFMEMORY;
			}

			pWaveFile=new WaveFile();
			if(pWaveFile==nullptr) {
				Helpers::SafeDelete(pWaveFile);
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception("Out of memory");
				return E_OUTOFMEMORY;
			}

			pWaveFile->Open(strWaveFileName,nullptr,(HMODULE)g_hInstance);

			if(pWaveFile->GetSize()==0) {
				Helpers::SafeDelete(pWaveFile);
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception("Wave is blank,so don't create it");
				return E_FAIL;
			}

			if(pWaveFile->m_WaveFormat->wFormatTag!=WAVE_FORMAT_PCM) {
				Helpers::SafeDelete(pWaveFile);
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception("Wave isn't PCM,so don't create it");
				return E_FAIL;
			}

			dwDSBufferSize=pWaveFile->GetSize();

			DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
			dsbd.dwSize         =sizeof(DSBUFFERDESC);
			if(pWaveFile->m_SampleLoops)
				dsbd.dwFlags        =dwCreationFlags|DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_CTRLPOSITIONNOTIFY|DSBCAPS_LOCSOFTWARE;
			else
				dsbd.dwFlags        =dwCreationFlags;
			dsbd.dwBufferBytes  =dwDSBufferSize;
			dsbd.guid3DAlgorithm=guid3DAlgorithm;
			dsbd.lpwfxFormat    =pWaveFile->m_WaveFormat;

			hr=m_pDS->CreateSoundBuffer(&dsbd,&apDSBuffer[0],nullptr);

			if(hr==DS_NO_VIRTUALIZATION)
				hrRet=DS_NO_VIRTUALIZATION;

			if(FAILED(hr)) {
				Helpers::SafeDelete(pWaveFile);
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception(DXGetErrorDescription(hr));
				return hr;
			}

			if((dwCreationFlags&DSBCAPS_CTRLFX)==0) {
				for(i=1;i<dwNumBuffers;i++) {
					if(FAILED(hr=m_pDS->DuplicateSoundBuffer(apDSBuffer[0],&apDSBuffer[i]))) {
						Helpers::SafeDelete(pWaveFile);
						Helpers::SafeDeleteArray(apDSBuffer);
						throw Exception(DXGetErrorDescription(hr));
						return hr;
					}
				}
			} else {
				for(i=1;i<dwNumBuffers;i++) {
					hr=m_pDS->CreateSoundBuffer(&dsbd,&apDSBuffer[i],nullptr);
					if(FAILED(hr)) {
						Helpers::SafeDelete(pWaveFile);
						Helpers::SafeDeleteArray(apDSBuffer);
						throw Exception(DXGetErrorDescription(hr));
						return hr;
					}
				}
			}

			*ppSound=new Sound(apDSBuffer,dwDSBufferSize,dwNumBuffers,pWaveFile,dwCreationFlags);

			AddAndNotify(*ppSound);

			Helpers::SafeDeleteArray(apDSBuffer);
			return hrRet;
		}

		HRESULT SoundEngine::CreateFromMemory(Sound** ppSound,PBYTE pbData,ULONG ulDataSize,LPWAVEFORMATEX pwfx,DWORD dwCreationFlags,GUID guid3DAlgorithm,DWORD dwNumBuffers)
		{
			HRESULT hr;
			DWORD   i;
			LPDIRECTSOUNDBUFFER* apDSBuffer    =nullptr;
			DWORD                dwDSBufferSize=0;
			WaveFile*            pWaveFile     =nullptr;

			if(m_pDS==nullptr)
				throw Exception("Direct sound buffer is null. May be CoInitialize has not been called?");

			if(pbData==nullptr||ppSound==nullptr||dwNumBuffers<1)
				throw Exception("Something wrong with pointers.");

			apDSBuffer=new LPDIRECTSOUNDBUFFER[dwNumBuffers];
			if(apDSBuffer==nullptr) {
				throw Exception("Out of memory");
			}

			pWaveFile=new WaveFile();
			if(pWaveFile==nullptr) {
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception("Out of memory");
			}

			pWaveFile->OpenFromMemory(pbData,ulDataSize,pwfx);
			dwDSBufferSize=ulDataSize;

			DSBUFFERDESC dsbd;
			ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
			dsbd.dwSize         =sizeof(DSBUFFERDESC);
			dsbd.dwFlags        =dwCreationFlags;
			dsbd.dwBufferBytes  =dwDSBufferSize;
			dsbd.guid3DAlgorithm=guid3DAlgorithm;
			dsbd.lpwfxFormat    =pwfx;

			if(FAILED(hr=m_pDS->CreateSoundBuffer(&dsbd,&apDSBuffer[0],nullptr))) {
				Helpers::SafeDeleteArray(apDSBuffer);
				throw Exception(DXGetErrorDescription(hr));
			}

			if((dwCreationFlags&DSBCAPS_CTRLFX)==0) {
				for(i=1;i<dwNumBuffers;i++) {
					if(FAILED(hr=m_pDS->DuplicateSoundBuffer(apDSBuffer[0],&apDSBuffer[i]))) {
						Helpers::SafeDeleteArray(apDSBuffer);
						throw Exception(DXGetErrorDescription(hr));
					}
				}
			} else {
				for(i=1;i<dwNumBuffers;i++) {
					hr=m_pDS->CreateSoundBuffer(&dsbd,&apDSBuffer[i],nullptr);
					if(FAILED(hr)) {
						Helpers::SafeDeleteArray(apDSBuffer);
						throw Exception(DXGetErrorDescription(hr));
					}
				}
			}

			*ppSound=new Sound(apDSBuffer,dwDSBufferSize,dwNumBuffers,pWaveFile,dwCreationFlags);
			AddAndNotify(*ppSound);
			Helpers::SafeDeleteArray(apDSBuffer);
			return S_OK;
		}

		DWORD SoundEngine::SoundEventHandler()
		{
			while(!s_bIsTerminating) {
				DWORD dwRes=::WaitForMultipleObjects(s_nEventsCount,s_hEvents,false,INFINITE);
				if(dwRes==WAIT_OBJECT_0) {
					::ResetEvent(s_hEvents[0]);
					continue;
				};
				if(dwRes==WAIT_ABANDONED_0)
					_endthreadex(0);
				//::ExitThread(0);
				if(dwRes>=WAIT_OBJECT_0&&dwRes<s_nEventsCount) {
					DWORD dwObjIndex=dwRes-WAIT_OBJECT_0;
					::ResetEvent(s_hEvents[dwObjIndex]);
					Sound *pSound=s_LoopSounds[dwObjIndex];
					assert(pSound!=nullptr);
					LPDIRECTSOUNDBUFFER pDSB=(pSound->m_Buffer[0]);
					assert(pDSB!=nullptr);
					pDSB->SetCurrentPosition(pSound->m_StartPosition);
				}
				continue;
			}
			_endthreadex(0);
			//::ExitThread(0);
			return 0;
		}

		Sound* SoundEngine::Load(const String& fn)
		{
			String filename=fn;
			boost::algorithm::to_lower(filename);
			if(m_SoundMap.find(filename)!=m_SoundMap.end()) {
				m_SoundMap[filename].iCount++;
				return m_SoundMap[filename].pSound;
			}

			SoundType st;
			st.iCount=1;
			HRESULT hr=Create(&st.pSound,(char*)(m_MediaPath+filename).c_str(),GetModuleHandle(nullptr));
			if(hr!=S_OK)
				return nullptr;
			m_SoundMap.insert(SoundPair(filename,st));
			return m_SoundMap[filename].pSound;
		}

		void SoundEngine::Play(const String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->Play();
		}

		void SoundEngine::Stop(const String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->Stop();
		}

		bool SoundEngine::IsPlaying(const String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				return snd->IsSoundPlaying()==1;
			return false;
		}

		void SoundEngine::SetVolume(String& filename,int vol)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->SetVolume(vol);
		}

		int SoundEngine::GetVolume(String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				return snd->GetVolume();
			return -10000;
		}

		void SoundEngine::Mute(String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->Mute();
		}

		void SoundEngine::UnMute(String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->RestoreVolume();
		}

		void SoundEngine::Pause(String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->Pause();
		}

		void SoundEngine::UnPause(String& filename)
		{
			Sound* snd=Load(filename);
			if(snd)
				snd->Replay();
		}

		void SoundEngine::PlayIfNotPlaying(const String& filename)
		{
			if(!IsPlaying(filename))
				Play(filename);
		}

		void SoundEngine::MuteAll()
		{
			for(SoundMapConstIte i=m_SoundMap.begin();i!=m_SoundMap.end();++i) {
				i->second.pSound->Mute();
			}
		}

		void SoundEngine::UnMuteAll()
		{
			for(SoundMapConstIte i=m_SoundMap.begin();i!=m_SoundMap.end();++i) {
				i->second.pSound->RestoreVolume();
			}
		}

		void SoundEngine::PauseAll()
		{
			for(SoundMapConstIte i=m_SoundMap.begin();i!=m_SoundMap.end();++i) {
				i->second.pSound->Pause();
			}
		}

		void SoundEngine::UnPauseAll()
		{
			for(SoundMapConstIte i=m_SoundMap.begin();i!=m_SoundMap.end();++i) {
				i->second.pSound->Replay();
			}
		}

		void SoundEngine::StopAll()
		{
			for(SoundMapConstIte i=m_SoundMap.begin();i!=m_SoundMap.end();++i) {
				i->second.pSound->Stop();
			}
		}

		void SoundEngine::StopIfPlaying(const String& filename)
		{
			if(IsPlaying(filename))
				Stop(filename);
		}
	}
}

