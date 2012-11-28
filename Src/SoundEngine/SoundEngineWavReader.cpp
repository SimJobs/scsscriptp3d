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
		WaveFile::WaveFile() :	m_WaveFormat(0),
			m_MmioHandle(0),
			m_ResourceBuffer(0),
			m_Size(0),
			m_IsReadingFromMemory(false),
			m_SampleLoops(0)
		{
			ZeroMemory(&m_Sample,sizeof(SAMPLE));
		}

		WaveFile::~WaveFile()
		{
			Close();

			if(!m_IsReadingFromMemory)
				Helpers::SafeDeleteArray(m_WaveFormat);
			Helpers::SafeDeleteArray(m_SampleLoops);
		}

		HRESULT WaveFile::Open(PCHAR strFileName,PWAVEFORMATEX pwfx,HMODULE hModule)
		{
			HRESULT hr;

			m_IsReadingFromMemory=false;

			if(strFileName==nullptr)
				return E_INVALIDARG;

			Helpers::SafeDeleteArray(m_WaveFormat);

			m_MmioHandle=mmioOpenA(strFileName,nullptr,MMIO_ALLOCBUF|MMIO_READ);

			if(nullptr==m_MmioHandle) {
				HRSRC   hResInfo;
				HGLOBAL hResData;
				DWORD   dwSize;
				VOID*   pvRes;

				if(nullptr==(hResInfo=FindResourceA(hModule,strFileName,"WAVE"))) {
					if(nullptr==(hResInfo=FindResourceA(hModule,strFileName,"WAV"))) {
						if(nullptr==(hResInfo=FindResourceA(hModule,strFileName,MAKEINTRESOURCEA(10)))) {
							return DXUT_ERR(L"FindResource",E_FAIL);
						}
					}
				}

				if(nullptr==(hResData=LoadResource(hModule,hResInfo)))
					return DXUT_ERR(L"LoadResource",E_FAIL);

				if(0==(dwSize=SizeofResource(hModule,hResInfo)))
					return DXUT_ERR(L"SizeofResource",E_FAIL);

				if(nullptr==(pvRes=LockResource(hResData)))
					return DXUT_ERR(L"LockResource",E_FAIL);

				m_ResourceBuffer=new CHAR[dwSize];
				if(m_ResourceBuffer==nullptr) {
					return DXUT_ERR(L"new",E_OUTOFMEMORY);
				}

				memcpy(m_ResourceBuffer,pvRes,dwSize);

				MMIOINFO mmioInfo;
				ZeroMemory(&mmioInfo,sizeof(mmioInfo));
				mmioInfo.fccIOProc=FOURCC_MEM;
				mmioInfo.cchBuffer=dwSize;
				mmioInfo.pchBuffer=(PCHAR)m_ResourceBuffer;
				m_MmioHandle=mmioOpen(nullptr,&mmioInfo,MMIO_ALLOCBUF|MMIO_READ);
			}

			if(FAILED(hr=ReadMMIO()))
			{
				mmioClose(m_MmioHandle,0);
				return DXUT_ERR(L"ReadMMIO",hr);
			}

			if(FAILED(hr=ResetFile()))
				return DXUT_ERR(L"ResetFile",hr);

			m_Size=m_Chunk.cksize;

			return hr;
		}

		HRESULT WaveFile::OpenFromMemory(PBYTE pbData,ULONG ulDataSize,PWAVEFORMATEX pwfx)
		{
			m_WaveFormat=pwfx;
			m_DataSize=ulDataSize;
			m_Data=pbData;
			m_DataCursor=m_Data;
			m_IsReadingFromMemory=true;
			return S_OK;
		}

		HRESULT WaveFile::ReadMMIO()
		{
			MMCKINFO        ckIn;           
			PCMWAVEFORMAT   pcmWaveFormat;  

			m_WaveFormat=nullptr;

			if((0!=mmioDescend(m_MmioHandle,&m_ChunkRiff,nullptr,0)))
				return DXUT_ERR(L"mmioDescend",E_FAIL);

			if((m_ChunkRiff.ckid!=FOURCC_RIFF)||(m_ChunkRiff.fccType!=mmioFOURCC('W','A','V','E')))
				return DXUT_ERR(L"mmioFOURCC",E_FAIL);

			ckIn.ckid=mmioFOURCC('f','m','t',' ');
			if(0!=mmioDescend(m_MmioHandle,&ckIn,&m_ChunkRiff,MMIO_FINDCHUNK))
				return DXUT_ERR(L"mmioDescend",E_FAIL);

			if(ckIn.cksize<(LONG)sizeof(PCMWAVEFORMAT))
				return DXUT_ERR(L"sizeof(PCMWAVEFORMAT)",E_FAIL);

			if(mmioRead(m_MmioHandle,(HPSTR)&pcmWaveFormat,sizeof(pcmWaveFormat))!=sizeof(pcmWaveFormat))
				return DXUT_ERR(L"mmioRead",E_FAIL);

			if(pcmWaveFormat.wf.wFormatTag==WAVE_FORMAT_PCM) {
				m_WaveFormat=(PWAVEFORMATEX)new CHAR[sizeof(WAVEFORMATEX)];
				if(nullptr==m_WaveFormat)
					return DXUT_ERR(L"m_pwfx",E_FAIL);

				memcpy(m_WaveFormat,&pcmWaveFormat,sizeof(pcmWaveFormat));
				m_WaveFormat->cbSize=0;
			} else {
				WORD cbExtraBytes=0L;
				if(mmioRead(m_MmioHandle,(PCHAR)&cbExtraBytes,sizeof(WORD))!=sizeof(WORD))
					return DXUT_ERR(L"mmioRead",E_FAIL);

				m_WaveFormat=(PWAVEFORMATEX)new CHAR[sizeof(WAVEFORMATEX)+cbExtraBytes];
				if(nullptr==m_WaveFormat)
					return DXUT_ERR(L"new",E_FAIL);

				memcpy(m_WaveFormat,&pcmWaveFormat,sizeof(pcmWaveFormat));
				m_WaveFormat->cbSize=cbExtraBytes;

				if(mmioRead(m_MmioHandle,(PCHAR)(((PBYTE)&(m_WaveFormat->cbSize))+sizeof(WORD)),cbExtraBytes)!=cbExtraBytes) {
					Helpers::SafeDelete(m_WaveFormat);
					return DXUT_ERR(L"mmioRead",E_FAIL);
				}
			}

			if(0!=mmioAscend(m_MmioHandle,&ckIn,0)) {
				Helpers::SafeDelete(m_WaveFormat);
				return DXUT_ERR(L"mmioAscend",E_FAIL);
			}

			ckIn.ckid=mmioFOURCC('s','m','p','l');
			if(MMSYSERR_NOERROR==mmioDescend(m_MmioHandle,&ckIn,&m_ChunkRiff,MMIO_FINDCHUNK)) {
				if(mmioRead(m_MmioHandle,(PCHAR)&m_Sample,sizeof(SAMPLE))==sizeof(SAMPLE)) {
					m_SampleLoops=new SAMPLELOOP[m_Sample.dwNumSampleLoops];
					mmioRead(m_MmioHandle,(PCHAR)m_SampleLoops,sizeof(SAMPLELOOP)*m_Sample.dwNumSampleLoops);
				}
			}

			return S_OK;
		}

		HRESULT WaveFile::ResetFile()
		{
			if(m_IsReadingFromMemory) {
				m_DataCursor=m_Data;
			} else {
				if(m_MmioHandle==nullptr)
					return CO_E_NOTINITIALIZED;

				if(-1==mmioSeek(m_MmioHandle,m_ChunkRiff.dwDataOffset+sizeof(FOURCC),SEEK_SET))
					return DXUT_ERR(L"mmioSeek",E_FAIL);
				m_Chunk.ckid=mmioFOURCC('d','a','t','a');
				if(0!=mmioDescend(m_MmioHandle,&m_Chunk,&m_ChunkRiff,MMIO_FINDCHUNK))
					return DXUT_ERR(L"mmioDescend",E_FAIL);
			}
			return S_OK;
		}

		HRESULT WaveFile::Read(PBYTE pBuffer,DWORD dwSizeToRead,PDWORD pdwSizeRead)
		{
			if(m_IsReadingFromMemory) {
				if(m_DataCursor==nullptr)
					return CO_E_NOTINITIALIZED;
				if(pdwSizeRead!=nullptr)
					*pdwSizeRead=0;

				if((PBYTE)(m_DataCursor+dwSizeToRead)>(PBYTE)(m_Data+m_DataSize)) {
					dwSizeToRead=m_DataSize-(DWORD)(m_DataCursor-m_Data);
				}

				CopyMemory(pBuffer,m_DataCursor,dwSizeToRead);

				if(pdwSizeRead!=nullptr)
					*pdwSizeRead=dwSizeToRead;

				return S_OK;
			} else {
				MMIOINFO mmioinfoIn; 

				if(m_MmioHandle==nullptr)
					return CO_E_NOTINITIALIZED;
				if(pBuffer==nullptr||pdwSizeRead==nullptr)
					return E_INVALIDARG;

				if(pdwSizeRead!=nullptr)
					*pdwSizeRead=0;

				if(0!=mmioGetInfo(m_MmioHandle,&mmioinfoIn,0))
					return DXUT_ERR(L"mmioGetInfo",E_FAIL);

				UINT cbDataIn=dwSizeToRead;
				if(cbDataIn>m_Chunk.cksize)
					cbDataIn=m_Chunk.cksize;

				m_Chunk.cksize-=cbDataIn;

				for(DWORD cT=0;cT<cbDataIn;cT++) {
					if(mmioinfoIn.pchNext==mmioinfoIn.pchEndRead) {
						if(0!=mmioAdvance(m_MmioHandle,&mmioinfoIn,MMIO_READ))
							return DXUT_ERR(L"mmioAdvance",E_FAIL);

						if(mmioinfoIn.pchNext==mmioinfoIn.pchEndRead)
							return DXUT_ERR(L"mmioinfoIn.pchNext",E_FAIL);
					}

					*((PBYTE)pBuffer+cT)=*((PBYTE)mmioinfoIn.pchNext);
					mmioinfoIn.pchNext++;
				}

				if(0!=mmioSetInfo(m_MmioHandle,&mmioinfoIn,0))
					return DXUT_ERR(L"mmioSetInfo",E_FAIL);

				if(pdwSizeRead!=nullptr)
					*pdwSizeRead=cbDataIn;

				return S_OK;
			}
		}

		HRESULT WaveFile::Close()
		{
			mmioClose(m_MmioHandle,0);
			m_MmioHandle=nullptr;
			Helpers::SafeDeleteArray(m_ResourceBuffer);
			return S_OK;
		}
	}
}


