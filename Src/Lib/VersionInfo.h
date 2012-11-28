/*
 *	I don't remember where I download this code, and who author.
 *  If anybody know who author of this code, mail me to except134@gmail.com please.
 */

#pragma once

namespace SCSScript
{
#pragma comment(lib,"version.lib")

	typedef unsigned short HPVER;

#define CBVERSTR 64

	class VersionInfo  
	{
	public:
		VersionInfo(const VersionInfo& ver);
		VersionInfo(VS_FIXEDFILEINFO*);
		VersionInfo(LPCTSTR strVer);   //Parse strVer as version
		VersionInfo(HMODULE);          //Read from module
		VersionInfo();
		virtual ~VersionInfo();

		//Set methods
		void SetFromString(LPCTSTR);
		void SetFromFFI(VS_FIXEDFILEINFO*);
		void SetFromVerInfo(const VersionInfo&);
		void SetMajor(HPVER verMajor);
		void SetMinor(HPVER verMinor);
		void SetAux(HPVER verAux);
		void SetMaintenance(HPVER verMaintenance);
		void SetFromInstance(HMODULE);
		void SetFromFilename(LPCTSTR);

		//Out methods
		void AsResource(LPTSTR) const;  //Use ',' as sep
		LPCTSTR AsString(std::string& str) const;
		// The "Short" methods only returns major and minor nums.
		LPCTSTR AsStringShort(std::string& str) const;
		LPTSTR AsStringShort(LPTSTR) const;
		LPTSTR AsString(LPTSTR) const;
		//Use internal buffer to format string
		LPCTSTR AsString();

		//For extended info
		LPCTSTR GetExtProductName(std::string*) const;
		LPCTSTR GetProductName() const;
		LPCTSTR GetCompanyName() const;
		LPCTSTR GetLegalInfo() const;

		//Compare method(s)
		UINT Compare(const VersionInfo& ver) const;

		// operators methods
		VersionInfo& operator=(const VersionInfo& ver);
		BOOL operator==(const VersionInfo& ver) const;
		BOOL operator<(const VersionInfo& ver) const;
		BOOL operator>(const VersionInfo& ver) const;

		//Static helpers
		static LPTSTR GetVersionInfo(LPCTSTR szFile);

	protected:
		BOOL GetVersionOfFile(LPCTSTR szFile);
		void Reset();

	private:
		TCHAR m_tszStrOut[128];

		HPVER m_verMaintenance;
		HPVER m_verAux;
		HPVER m_verMinor;
		HPVER m_verMajor;

		std::string m_strProductName;
		std::string m_strCompany;
		std::string m_strLegal;
	};
}
