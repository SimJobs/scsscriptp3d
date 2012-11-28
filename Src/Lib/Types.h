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
	#define List				std::list
	#define Map					std::map
	#define Pair				std::pair
	#define Vector				std::vector
	#define Queue				std::queue
	#define HashMap				std::unordered_map
	#define Sort				std::sort	

	#define Strcpy				strcpy_s
	#define Sprintf				sprintf_s
	#define Stricmp				_strcmpi
	#define Strcat				strcat_s

	typedef char				Char;
	typedef std::string			String;
	typedef std::stringstream	StringStream;
	typedef std::fstream		FileStream;
	typedef std::ifstream		IFileStream;
	typedef std::ofstream		OFileStream;
	typedef std::ios			Ios;
	typedef std::istringstream	Istringstream;

	typedef char				Byte;
	typedef short				Short;
	typedef int					Int32;
	typedef long				Long;
	typedef __int64				Int64;
	
	typedef unsigned char		Ubyte;
	typedef unsigned short		Ushort;
	typedef unsigned int		Uint32;
	typedef unsigned long		Ulong;
	typedef unsigned __int64	Uint64;
}

