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
	WriterASCII::WriterASCII(EOutputType eType,const String& strName) : fileOut(nullptr),hWndOut(nullptr),nIndentation(0)
	{
		switch(eType) {
			case OUTPUT_STDOUT:
				InitStdout();
			break;
			case OUTPUT_FILE:
				InitFile(strName);
			break;
			case OUTPUT_WINDOW:
				InitWindow(strName);
			break;
			case OUTPUT_NONE:
			default:
			break;
		}
	}

	bool WriterASCII::InitStdout()
	{
		if(Ready()) {
			Close();
		}
		fileOut=stdout;
		if(fileOut==nullptr) {
			return false;
		}
		eOutputType=OUTPUT_STDOUT;
		return true;
	}

	bool WriterASCII::InitFile(const String& strFile)
	{
		if(strFile=="") {
			eOutputType=OUTPUT_NONE;
			return false;
		}

		if(Ready()) {
			Close();
		}

		Helpers::SafeFopen(fileOut,strFile,"wt");

		if(!fileOut) {
			throw Exception("Couldn't open "+strFile+" for output logging.");
		}
		eOutputType=OUTPUT_FILE;
		return true;
	}

	bool WriterASCII::InitWindow(const String& strTitle)
	{
		if(Ready()) {
			Close();
		}

		hWndOut=CreateWindow("EDIT",strTitle.data(),WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_LEFT|ES_MULTILINE|ES_NOHIDESEL|ES_WANTRETURN|ES_READONLY,20,20,640,480,nullptr,nullptr,nullptr,nullptr);

		if(hWndOut==nullptr) {
			throw Exception("Error creating a log window.");
		}

		UpdateWindow(hWndOut);
		eOutputType=OUTPUT_WINDOW;
		return true;
	}

	bool WriterASCII::Close()
	{
		switch(eOutputType) {
			case OUTPUT_NONE:
			break;
			case OUTPUT_STDOUT:
			break;
			case OUTPUT_FILE:
				Helpers::SafeFclose(fileOut);
			break;
			case OUTPUT_WINDOW:
				if(hWndOut) {
					DestroyWindow(hWndOut);
					hWndOut=nullptr;
				}
			break;
		default:
			break;
		}

		eOutputType=OUTPUT_NONE;
		nIndentation=0;
		return true;
	}

	bool WriterASCII::Write(const Char* szMessage,...) const
	{
		if(eOutputType==OUTPUT_NONE) {
			return true;
		}

		if(Ready()==false) {
			return false;
		}

		static Char szFormattedMessage[MAX_BUFFER_LENGTH];

		va_list arguments;
		va_start(arguments,szMessage);
		vsprintf_s(szFormattedMessage,szMessage,arguments);
		va_end(arguments);

#ifdef _DEBUG
		OutputDebugString(szFormattedMessage);
#endif

		size_t nCount,nLength=strlen(szFormattedMessage);

		for(nCount=0;nCount<nLength;nCount++) {
			if(szFormattedMessage[nCount]=='\n') {
				WriteChar('\n');
				if(eOutputType==OUTPUT_WINDOW) {
					WriteChar('\r');
				}
				WriteIndentation();
			} else {
				WriteChar(szFormattedMessage[nCount]);
			}
		}
		Flush();
		return true;
	}

	bool WriterASCII::Write(const Char* file,const Char* func,const int ln,const Char* szMessage,...)	const
	{
		if(eOutputType==OUTPUT_NONE) {
			return true;
		}

		if(Ready()==false) {
			return false;
		}

		static Char szFormattedMessage[MAX_BUFFER_LENGTH];

		va_list arguments;
		va_start(arguments,szMessage);
		vsprintf_s(szFormattedMessage,szMessage,arguments);
		va_end(arguments);
		return Write("%s, file: %s, function: %s, line: %d",szFormattedMessage,file,func,ln);
	}

	bool WriterASCII::WriteChar(Char chCar) const
	{
		int nWindowTextLength;

		switch(eOutputType) {
			case OUTPUT_NONE:
				return true;
			case OUTPUT_STDOUT:
			case OUTPUT_FILE:
				fputc(chCar,fileOut);
			break;
			case OUTPUT_WINDOW:
				nWindowTextLength=GetWindowTextLength(hWndOut)+1;
				String newText;
				newText.reserve(nWindowTextLength+1);
				GetWindowText(hWndOut,(Char *)newText.data(),nWindowTextLength);
				newText[nWindowTextLength]=chCar;
				SetWindowText(hWndOut,newText.data());
			break;
		}
		return true;
	}

	bool WriterASCII::WriteIndentation() const
	{
		if(eOutputType==OUTPUT_NONE) {
			return true;
		}

		for(int nCount=0;nCount<nIndentation;nCount++) {
			WriteChar(' ');
		}

		return true;
	}

	bool WriterASCII::Flush() const
	{
		if(Ready()==false) {
			return false;
		}

		switch(eOutputType) {
			case OUTPUT_NONE:
				return true;
			case OUTPUT_STDOUT:
			case OUTPUT_FILE:
				if(fileOut) {
					fflush(fileOut);
				}
			break;
			case OUTPUT_WINDOW:
				if(hWndOut)
					UpdateWindow(hWndOut);
			break;
		}

		return true;
	}

	bool WriterASCII::Write(const String& szMessage) const
	{
		return Write(szMessage.c_str());
	}

	bool WriterASCII::Write(const Char* file,const Char* func,const int ln,const String& szMessage) const
	{
		return Write(file,func,ln,szMessage.c_str());
	}
}
