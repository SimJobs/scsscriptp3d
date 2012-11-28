/*
 *	I don't remember where I download this code, and who author.
 *  If anybody know who author of this code, mail me to except134@gmail.com please.
 */

#include "PCH.h"

namespace SCSScript
{
	VersionInfo::VersionInfo(VS_FIXEDFILEINFO* pver)
	{
		SetFromFFI(pver);
	}

	VersionInfo::VersionInfo(const VersionInfo& ver)
	{
		SetFromVerInfo(ver);
	}

	VersionInfo::VersionInfo(LPCTSTR strVer)
	{
		Reset();
		SetFromString(strVer);
	}

	VersionInfo::VersionInfo(HMODULE hmod)
	{
		SetFromInstance(hmod);
	}

	VersionInfo::VersionInfo()
	{
		Reset();
	}

	VersionInfo::~VersionInfo()
	{

	}

	void VersionInfo::Reset()
	{
		m_verMajor=0;
		m_verMinor=0;
		m_verAux=0;
		m_verMaintenance=0;
		m_strProductName.assign(TEXT(""));
		m_strCompany.assign(TEXT(""));
		m_strLegal.assign(TEXT(""));
	}

	void VersionInfo::SetFromVerInfo(const VersionInfo& ver)
	{
		m_verMajor=ver.m_verMajor;
		m_verMinor=ver.m_verMinor;
		m_verAux=ver.m_verAux;
		m_verMaintenance=ver.m_verMaintenance;
		m_strProductName=ver.m_strProductName;
		m_strCompany=ver.m_strCompany;
		m_strLegal=ver.m_strLegal;
	}

	void VersionInfo::SetFromFFI(VS_FIXEDFILEINFO* pver)
	{
		m_verMajor=HIWORD(pver->dwFileVersionMS);
		m_verMinor=LOWORD(pver->dwFileVersionMS);
		m_verAux=HIWORD(pver->dwFileVersionLS);
		m_verMaintenance=LOWORD(pver->dwFileVersionLS);
	}

	void VersionInfo::SetFromString(LPCTSTR strVer)
	{
		const char chDelim='.';
		LPCTSTR pch=strVer;
		HPVER *ppVer[]={ &m_verMajor, 
			&m_verMinor, 
			&m_verAux, 
			&m_verMaintenance, 
			NULL };
		HPVER **ppVerNext=ppVer;

		while (pch && *pch)
		{
#ifdef _UNICODE
			**ppVerNext=(HPVER)_wtoi(pch);
			pch=wcschr(pch, chDelim);
#else
			**ppVerNext=atoi(pch);
			pch=strchr(pch, chDelim);
#endif
			if (pch) 
				pch++;
			ppVerNext++;
			if (!*ppVerNext)
				break;
		}
	}

	void VersionInfo::SetFromInstance(HMODULE hmod)
	{
		TCHAR szFile[MAX_PATH];

		if (NULL == hmod)
		{
			Reset();
			return;
		}
		GetModuleFileName(hmod, szFile, sizeof(szFile));
		GetVersionOfFile(szFile);
	}

	void VersionInfo::SetFromFilename(LPCTSTR tszFile)
	{
		GetVersionOfFile(tszFile);
	}

	void VersionInfo::SetMajor(HPVER verMajor)
	{
		m_verMajor=verMajor;
	}

	void VersionInfo::SetMinor(HPVER verMinor)
	{
		m_verMinor=verMinor;
	}

	void VersionInfo::SetAux(HPVER verAux)
	{
		m_verAux=verAux;
	}

	void VersionInfo::SetMaintenance(HPVER verMaintenance)
	{
		m_verMaintenance=verMaintenance;
	}


	void VersionInfo::AsResource(LPTSTR str) const
	{
		sprintf_s(str,BUFSIZ,TEXT("%d,%d,%d,%d"),m_verMajor,m_verMinor,m_verAux,m_verMaintenance);
	}

	LPTSTR VersionInfo::AsString(LPTSTR tszStrOut) const
	{
		sprintf_s(tszStrOut,BUFSIZ,TEXT("%d.%d.%d.%d"), m_verMajor,m_verMinor,m_verAux,m_verMaintenance);
		return tszStrOut;
	}

	LPTSTR VersionInfo::AsStringShort(LPTSTR tszStrOut) const
	{
		sprintf_s(tszStrOut,BUFSIZ,TEXT("%d.%d"),m_verMajor,m_verMinor);
		return tszStrOut;
	}

	LPCTSTR VersionInfo::AsString()
	{
		return AsString(m_tszStrOut);
	}

	LPCTSTR VersionInfo::AsString(std::string& str) const
	{
		TCHAR tszVer[CBVERSTR];
		str=AsString(tszVer);
		return str.data();
	}

	LPCTSTR VersionInfo::AsStringShort(std::string& str) const
	{
		TCHAR tszVer[CBVERSTR];
		str=AsStringShort(tszVer);
		return str.data();
	}

	LPCTSTR VersionInfo::GetCompanyName() const
	{
		return m_strCompany.data();
	}

	LPCTSTR VersionInfo::GetExtProductName(std::string* pstr) const
	{
		std::string str;
		pstr->assign(m_strProductName);
		pstr->append(TEXT(" "));
		pstr->append(AsStringShort(str));
		return pstr->data();
	}

	LPCTSTR VersionInfo::GetProductName() const
	{
		return m_strProductName.data();
	}

	LPCTSTR VersionInfo::GetLegalInfo() const
	{
		return m_strLegal.data();
	}

	//
	// Compare methods and Operators
	//

	//Compare: 1 is >, -1 is <, 0 is ==
	UINT VersionInfo::Compare(const VersionInfo& ver) const
	{
		HPVER rgVerThis[]={ m_verMajor,m_verMinor,m_verAux,m_verMaintenance };
		HPVER rgVer[]={ ver.m_verMajor,ver.m_verMinor,ver.m_verAux,ver.m_verMaintenance };
		int ixRg=0;

		assert(sizeof(rgVerThis)==sizeof(rgVer));

		while(ixRg<(sizeof(rgVerThis)/sizeof(HPVER))) {
			if(rgVerThis[ixRg]>rgVer[ixRg])
				return 1;
			if(rgVerThis[ixRg]<rgVer[ixRg])
				return -1;
			ixRg++;
		}
		return 0;
	}

	VersionInfo& VersionInfo::operator=(const VersionInfo& ver)
	{
		SetFromVerInfo(ver);
		return *this;
	}

	BOOL VersionInfo::operator==(const VersionInfo& ver) const
	{
		return (0==Compare(ver));
	}

	BOOL VersionInfo::operator<(const VersionInfo& ver) const
	{
		return (-1==Compare(ver));
	}

	BOOL VersionInfo::operator>(const VersionInfo& ver) const
	{
		return (1==Compare(ver));
	}

	void GetVersionString(LPTSTR lpVI,LPTSTR tszStr,WORD* lng,std::string* pstr)
	{
		DWORD dwBufSize; 
		TCHAR tszVerStrName[CBVERSTR];
		LPVOID lpt;

		sprintf_s(tszVerStrName,TEXT("\\StringFileInfo\\%04x%04x\\%s"),lng[0],lng[1],tszStr);
		if(VerQueryValue(lpVI,tszVerStrName,&lpt,(UINT*)&dwBufSize))
			pstr->assign((LPTSTR)lpt);
	}

	BOOL VersionInfo::GetVersionOfFile(LPCTSTR szFile) 
	{
		DWORD dwBufSize; 
		VS_FIXEDFILEINFO* lpFFI; 
		LPTSTR lpVI=GetVersionInfo(szFile); 
		BOOL bRet=FALSE;
		WORD* langInfo;
		UINT cbLang;

		if (!lpVI)
			return FALSE;
		if (bRet=VerQueryValue(lpVI, TEXT("\\"),(LPVOID *)&lpFFI,(UINT *)&dwBufSize)) {
			SetFromFFI(lpFFI);
		}
		VerQueryValue(lpVI,TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&langInfo,&cbLang);
		GetVersionString(lpVI,TEXT("ProductName"),langInfo,&m_strProductName);
		GetVersionString(lpVI,TEXT("CompanyName"),langInfo,&m_strCompany);
		GetVersionString(lpVI,TEXT("LegalCopyright"),langInfo,&m_strLegal);
		GlobalFree((HGLOBAL)lpVI); 
		return bRet; 
	} 

	LPTSTR VersionInfo::GetVersionInfo(LPCTSTR szFile) 
	{
		DWORD dwLen, dwUseless; 
		LPTSTR lpVI; 

		dwLen=GetFileVersionInfoSize((LPTSTR)szFile,&dwUseless); 
		if(dwLen==0) 
			return 0; 

		lpVI=(LPTSTR)GlobalAlloc(GPTR, dwLen); 
		if(lpVI) {
			GetFileVersionInfo((LPTSTR)szFile,NULL,dwLen,lpVI); 
			return lpVI;
		}   
		return NULL; 
	}
}

