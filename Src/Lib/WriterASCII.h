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
	class WriterASCII
	{
	protected:
		enum EOutputType {
			OUTPUT_NONE=0,
			OUTPUT_STDOUT,
			OUTPUT_FILE,
			OUTPUT_WINDOW
		};

	private:
		EOutputType				eOutputType;
		FILE*					fileOut;
		HWND					hWndOut;
		int						nIndentation;

		bool WriteIndentation	() const;
		bool Flush				() const;
		bool WriteChar			(Char chCar)	const;

	public:
		WriterASCII				() : eOutputType(OUTPUT_NONE),fileOut(nullptr),hWndOut(nullptr),nIndentation(0) {};
		WriterASCII				(EOutputType eType,const String& strName);
		~WriterASCII			() { Close(); };

		bool InitStdout			();
		bool Close				();
		bool InitFile			(const String& strFile);
		bool InitWindow			(const String& strTitle);
		bool Write				(const Char* szMessage,...) const;
		bool Write				(const Char* file,const Char* func,const int ln,const Char* szMessage,...) const;
		bool Write				(const String& szMessage) const;
		bool Write				(const Char* file,const Char* func,const int ln,const String& szMessage) const;
		bool Ready				()					const	{ return eOutputType!=OUTPUT_NONE; };
		int  Indentation		()					const	{ return nIndentation; };
		void SetIndentation		(int nIndentChars)			{ nIndentation=nIndentChars; };
		void IncIndentation		(int nInc)					{ nIndentation+=nInc; };
		void DecIndentation		(int nDec)					{ nIndentation-=nDec; if(nIndentation<0){nIndentation=0;} };
	};
}


