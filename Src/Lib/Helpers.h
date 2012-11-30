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
	namespace Helpers
	{
		inline errno_t SafeFopen(FILE*& f,const Char* n,const Char* m)
		{
			errno_t err=0;
			if(!f)
				err=fopen_s(&f,n,m);
			return err;
		}

		inline void SafeFclose(FILE*& f)
		{
			if(f) {
				fclose(f);
				f=nullptr;
			}
		}

		inline errno_t SafeFopen(FILE*& f,const String n,const String m)
		{
			return SafeFopen(f,n.c_str(),m.c_str());
		}

		template<typename T>
		void SafeNull(T& Value)
		{
			Value=nullptr;
		}

		template<typename T>
		void SafeDelete(T& Value)
		{
			if(Value!=nullptr) 
				delete Value;
			Value=nullptr;
		}

		template<typename T>
		void SafeFree(T& Value)
		{
			if(Value!=nullptr)
				free(Value);
			Value=nullptr;
		}

		template<typename T>
		void SafeDeleteArray(T& Array)
		{
			if(Array!=nullptr) 
				delete[] Array;
			Array=nullptr;
		}

		template<typename T>
		void SafeRelease(T& Value)
		{
			if(Value!=nullptr) 
				Value->Release();
			Value=nullptr;
		}

		template<typename T>
		void SafeNullArray(T* Array,size_t NumOfElements)
		{
			for(size_t i=0;i<NumOfElements;i++)
				Array[i]=T(0);
		}

		template<typename T> 
		class Singleton
		{
		public:
			static T& Instance() 
			{
				static T instance; 
				return instance;
			}
		};

		template<typename T>
		inline T FromString(const String& s) 
		{
			Istringstream is(s);
			T t;
			is >> t;
			return t;
		}

		inline std::string ConvertString(const std::wstring& str)
		{
			size_t i;
			char buf[MAX_BUFFER_LENGTH];
			wcstombs_s(&i,buf,MAX_BUFFER_LENGTH,str.c_str(),MAX_BUFFER_LENGTH);
			return std::string(buf);
		}

		inline std::wstring ConvertString(const std::string& str)
		{
			size_t i;
			wchar_t buf[MAX_BUFFER_LENGTH];
			mbstowcs_s(&i,buf,MAX_BUFFER_LENGTH,str.c_str(),MAX_BUFFER_LENGTH);
			return std::wstring(buf);
		}

		template<typename T>
		inline String ToString(const T& t) 
		{
			return boost::lexical_cast<String,T>(t);
		}

		inline String ToString(bool val)
		{
			return val?"True":"False";
		}

		inline bool CompareStringsNoCase(const String& rStr1,const String& rStr2)
		{
			return 0==Stricmp(rStr1.c_str(),rStr2.c_str());
		}

		inline bool ParseStringForBool(const String& str)
		{
			if(CompareStringsNoCase(str,"true")||CompareStringsNoCase(str,"1")||CompareStringsNoCase(str,"yes")||CompareStringsNoCase(str,"on"))
				return true;
			return false;
		}

		inline bool ParseStringForBool(const std::wstring& str)
		{
			return ParseStringForBool(ConvertString(str));
		}

		inline void Trim(String& str,bool left=true,bool right=true)
		{
			static const String delims=" \t\r";
			if(right)
				str.erase(str.find_last_not_of(delims)+1);
			if(left)
				str.erase(0,str.find_first_not_of(delims));
		}

		inline int GetFilesCountInDir(Char* mask)
		{
			int cnt=0;
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind=INVALID_HANDLE_VALUE;
			hFind=FindFirstFile(mask,&FindFileData);
			if(hFind!=INVALID_HANDLE_VALUE) {
				cnt++;
				while(FindNextFile(hFind,&FindFileData)!=0) {
					cnt++;
				}
				FindClose(hFind);
			}
			return cnt;
		}

		inline Vector<String> GetFileNamesFromDir(Char* mask) 
		{
			Vector<String> files;
			files.clear();
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind=INVALID_HANDLE_VALUE;
			hFind=FindFirstFile(mask,&FindFileData);
			if(hFind!=INVALID_HANDLE_VALUE) {
				files.push_back(FindFileData.cFileName);
				while(FindNextFile(hFind,&FindFileData)!=0) {
					files.push_back(FindFileData.cFileName);
				}
				FindClose(hFind);
			}
			return files;
		}

		inline void ExtractPath(Char* in)
		{
			in[strrchr((Char *)in,'\\')-(Char *)in+1]='\0';
		}

		inline void CheckForBackSlash(Char* temp)
		{
			if(temp[strlen(temp)-1]!='\\')
				Strcat(temp,MAX_PATH,"\\");
		}

		inline bool FileExists(Char* name)
		{
			FILE *f;
			errno_t err=fopen_s(&f,name,"r");
			if(err!=0)
				return false;

			fclose(f);
			return true;
		}

		inline bool FileExists(const String& fileName)
		{
			return FileExists((Char*)fileName.c_str());
		}

		template <class X>
		void SwapValue(X& p1,X& p2)
		{
			X t=p1;
			p1=p2;
			p2=t;
		}

		template <class X>
		X LimitValue(X v,X min,X max)
		{
			X ret=v;
			if(v<min)
				ret=min;
			if(v>max)
				ret=max;
			return ret;
		}

		template <class X>
		X LimitValueMin(X v,X min)
		{
			if(v<min)
				v=min;
			return v;
		}

		template <class X>
		X LimitValueMax(X v,X max)
		{
			if(v>max)
				v=max;
			return v;
		}

		inline void GetStringFromResource(String file,UINT id,String& ret,String def)
		{
			HANDLE hExe;
			CHAR sz[160];

			hExe = LoadLibraryA(file.c_str()); 

			if(hExe == NULL) { 
				ret=def;
				return;
			} 
			if(!LoadStringA((HINSTANCE)hExe,id,sz,sizeof(sz))) {
				ret=def;
				return;
			}

			if(!FreeLibrary((HINSTANCE)hExe)) { 
				ret=def;
				return;
			} 

			ret.assign(sz);
		}

	}
}

