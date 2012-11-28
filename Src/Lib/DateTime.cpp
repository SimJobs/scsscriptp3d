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
	namespace Common
	{
		DateTime::DateTime()
		{

		}

		DateTime::~DateTime()
		{

		}

		String DateTime::GetCurDate()
		{
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);
			Char buf[MAX_BUFFER_LENGTH];
			Sprintf(buf,MAX_BUFFER_LENGTH,"%02u.%02u.%4u",sysTime.wDay,sysTime.wMonth,sysTime.wYear);
			return String(buf);
		}

		String DateTime::GetCurTime()
		{
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);
			Char buf[MAX_BUFFER_LENGTH];
			Sprintf(buf,MAX_BUFFER_LENGTH,"%02u:%02u:%02u",sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
			return String(buf);
		}

		String DateTime::GetCurDateTime()
		{
			return String(GetCurDate()+" "+GetCurTime());
		}

	}
}

