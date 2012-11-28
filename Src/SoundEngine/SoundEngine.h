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
		struct SoundType
		{
			Sound*	pSound;
			UINT	iCount;
		};

		typedef Map<String,SoundType>					SoundMap;
		typedef Pair<String,SoundType>					SoundPair;
		typedef Map<String,SoundType>::iterator			SoundMapIte;
		typedef Map<String,SoundType>::const_iterator	SoundMapConstIte;

#define MAX_SND_SOCKETS	1024

		class SoundEngine : boost::noncopyable
		{
		private:
			IDirectSound8*		m_pDS;
			HANDLE				m_hThread;
			UINT				m_dwThreadID;
			DWORD				s_nEventsCount;
			HANDLE				s_hEvents[MAX_SND_SOCKETS];
			Sound*				s_LoopSounds[MAX_SND_SOCKETS];
			BOOL				s_bIsTerminating;
			DWORD				m_nSoundsCount;
			Sound*				m_Sounds[MAX_SND_SOCKETS];
			SoundMap			m_SoundMap;
			String			m_MediaPath;

		public:
			SoundEngine();
			virtual ~SoundEngine();

			void				Init(HWND hwnd,DWORD dwCoopLevel=DSSCL_NORMAL);
			void				DeInit();
			LPDIRECTSOUND8		GetDirectSound() { return m_pDS; }
			HRESULT				SetPrimaryBufferFormat(DWORD dwPrimaryChannels,DWORD dwPrimaryFreq,DWORD dwPrimaryBitRate);
			BOOL				AddAndNotify(Sound* pSound);
			HRESULT				Create(Sound** ppSound,char *strWaveFileName,HINSTANCE g_hInstance,DWORD dwCreationFlags=DSBCAPS_CTRLVOLUME,GUID guid3DAlgorithm=GUID_NULL,DWORD dwNumBuffers=10);
			HRESULT				CreateFromMemory(Sound** ppSound,PBYTE pbData,ULONG ulDataSize,LPWAVEFORMATEX pwfx,DWORD dwCreationFlags=DSBCAPS_CTRLVOLUME,GUID guid3DAlgorithm=GUID_NULL,DWORD dwNumBuffers=10);
			DWORD				SoundEventHandler(void);
			static DWORD WINAPI	SoundEventHandler(LPVOID param)	{ return ((SoundEngine*)param)->SoundEventHandler(); };
			static unsigned __stdcall	SoundEventHandler2(LPVOID param)	{ return ((SoundEngine*)param)->SoundEventHandler(); };
			void				PreInstall(const String& path) { m_MediaPath=path; };
			Sound*				Load(const String& filename);
			void				Play(const String& filename);
			void				Stop(const String& filename);
			bool				IsPlaying(const String& filename);
			void				SetVolume(String& filename,int vol);
			int 				GetVolume(String& filename);
			void				Mute(String& filename);
			void				UnMute(String& filename);
			void				Pause(String& filename);
			void				UnPause(String& filename);
			void				PlayIfNotPlaying(const String& filename);
			void				StopIfPlaying(const String& filename);
			void				MuteAll();
			void				UnMuteAll();
			void				PauseAll();
			void				UnPauseAll();
			void				StopAll();
		};
	}
}

