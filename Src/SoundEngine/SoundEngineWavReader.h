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

#define DXUT_ERR(s,r)	r

namespace SCSScript
{
	namespace SoundEngine
	{
		typedef struct _SAMPLELOOP
		{
			DWORD dwCuePointID;
			DWORD dwType; 
			DWORD dwStart;
			DWORD dwEnd;
			DWORD dwFraction;
			DWORD dwPlayCount;
		}SAMPLELOOP,*PSAMPLELOOP,**PPSAMPLELOOP;

		typedef struct _SAMPLE 
		{ 
			DWORD dwManufacturer; 
			DWORD dwProduct; 
			DWORD dwSamplePeriod; 
			DWORD dwMIDIUnityNote; 
			DWORD dwMIDIPitchFraction; 
			DWORD dwSMPTEFormat; 
			DWORD dwSNPTEOffset; 
			DWORD dwNumSampleLoops; 
			DWORD dwSamplerData; 
		}SAMPLE,*PSAMPLE,**PPSAMPLE; 

		class WaveFile
		{
		protected:
			HRESULT			ReadMMIO();

		public:
			PWAVEFORMATEX	m_WaveFormat;        
			HMMIO			m_MmioHandle;       
			MMCKINFO		m_Chunk;          
			MMCKINFO		m_ChunkRiff;      
			DWORD			m_Size;      
			MMIOINFO		m_MmioInfoOut;	
			DWORD			m_Flags;
			BOOL			m_IsReadingFromMemory;
			PBYTE			m_Data;
			PBYTE			m_DataCursor;
			ULONG			m_DataSize;
			PCHAR			m_ResourceBuffer;
			SAMPLE			m_Sample;
			PSAMPLELOOP		m_SampleLoops;

		public:
			WaveFile();
			~WaveFile();

			HRESULT			Open(PCHAR strFileName,PWAVEFORMATEX pwfx,HMODULE hModule);
			HRESULT			OpenFromMemory(PBYTE pbData,ULONG ulDataSize,PWAVEFORMATEX pwfx);
			HRESULT			Close();
			HRESULT			Read(PBYTE pBuffer,DWORD dwSizeToRead,PDWORD pdwSizeRead);
			DWORD			GetSize() { return m_Size; };
			HRESULT			ResetFile();
			PWAVEFORMATEX	GetFormat() { return m_WaveFormat; };
		};
	}
}
