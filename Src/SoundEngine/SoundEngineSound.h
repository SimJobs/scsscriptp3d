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

#pragma once

namespace SCSScript
{
	namespace SoundEngine
	{
		class Sound
		{
			friend class SoundEngine;

		protected:
			DWORD					m_BufferSize;
			WaveFile*				m_WaveFile;
			DWORD					m_NumberOfBuffers;
			DWORD					m_CreationFlags;
			int 					m_Volume;
			LPDIRECTSOUNDBUFFER*	m_Buffer;
			HANDLE					m_LoopEventHandle;
			DWORD					m_StartPosition;
			DWORD					m_StopPosition;
			DSBPOSITIONNOTIFY		m_PositionNotify;
			LPDIRECTSOUNDNOTIFY		m_DirectSoundNotify;
			BOOL					m_MuteFlag;

		protected:
			HRESULT					RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB,BOOL* pbWasRestored);

		public:
			Sound(LPDIRECTSOUNDBUFFER* apDSBuffer,DWORD dwDSBufferSize,DWORD dwNumBuffers,WaveFile* pWaveFile,DWORD dwCreationFlags);
			virtual ~Sound();

			HRESULT					FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB,BOOL bRepeatWavIfBufferLarger);
			LPDIRECTSOUNDBUFFER		GetFreeBuffer();
			LPDIRECTSOUNDBUFFER		GetBuffer(DWORD dwIndex);

			HRESULT					Play(DWORD dwFlags=0,DWORD dwPriority=0,LONG lVolume=0,LONG lFrequency=-1,LONG lPan=0);
			HRESULT					Stop();
			HRESULT					Reset();
			BOOL					IsSoundPlaying();
			HRESULT					SetVolume(int lVolume);
			int 					GetVolume()				{ return m_Volume; };
			HRESULT					IncVolume(int lDec)		{ return SetVolume(m_Volume+lDec); };
			HRESULT					DecVolume(int lDec)		{ return SetVolume(m_Volume-lDec); };
			HRESULT					Mute(int lVolume=DSBVOLUME_MIN);
			HRESULT					RestoreVolume(void);
			HRESULT					Pause(void);
			HRESULT					Replay(void);
		};
	}
}
