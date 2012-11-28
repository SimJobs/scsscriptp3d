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
	const String DEFAULT_LOG_FILE="SCSScript.log.txt";

	Logger::Logger()
	{
		VersionInfo ver(gHModule);
		Char ret[MAX_BUFFER_LENGTH];
		ver.AsString(ret);
		String v=ver.GetProductName()+String(", version ")+String(ret); 
		Start(DEFAULT_LOG_FILE,v);
	}

	Logger::~Logger()
	{
		this->WriteEndHeader();
		this->Close();
	}

	bool Logger::WriteStartHeader(const String& prjStr)
	{
		Common::DateTime dt;
		String Arch="x32";
		String Build="Release";
#ifdef _WIN64
		Arch="x64";
#endif
#ifdef _DEBUG
		Build="Debug";
#endif

		Write("============================================================================\n");
		Write("  %s, Arch: %s, Build: %s\n",prjStr.c_str(),Arch.c_str(),Build.c_str());
		Write("  Log created on %s, at %s\n",dt.GetCurDate().c_str(),dt.GetCurTime().c_str());
		Write("============================================================================\n\n");
		return true;
	}

	bool Logger::WriteEndHeader()
	{
		Common::DateTime dt;
		Write("\n\n============================================================================\n");
		Write("  Log closed on %s, at %s\n",dt.GetCurDate().c_str(),dt.GetCurTime().c_str());
		Write("============================================================================\n\n");
		return true;
	}

	bool Logger::Start(const String& strFile,const String& prjStr)
	{
		this->InitFile(strFile);
		this->WriteStartHeader(prjStr);
		return true;
	}
}

