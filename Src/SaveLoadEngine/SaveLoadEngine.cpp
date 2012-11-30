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

#define UI_GENERATEDFLIGHT_STRING_RES	8705
#define PREVIOUSFLIGHT_STRING_RES		8706

const String SIM_FLT_EXTENSION		= "flt";
const String SIM_FLT_GENERATED		= "Program generated temporary flight."+SIM_FLT_EXTENSION;
const String SIM_FLT_PREVIOUS		= "Previous flight."+SIM_FLT_EXTENSION;
const String SIM_LANG_MODULE		= "language.dll";

namespace SCSScript
{
	namespace SaveLoadEngine
	{
		void SaveLoadEngine::PrepareSimSaveFiles()
		{
			String tmp;
			tmp=rootPath;
			tmp+=SIM_LANG_MODULE;
			Helpers::GetStringFromResource(tmp,UI_GENERATEDFLIGHT_STRING_RES,m_UIGeneratedFlight,SIM_FLT_GENERATED);
			m_UIGeneratedFlight+="."+SIM_FLT_EXTENSION;
			Helpers::GetStringFromResource(tmp,PREVIOUSFLIGHT_STRING_RES,m_PrevoiusFlight,SIM_FLT_PREVIOUS);
			m_PrevoiusFlight+="."+SIM_FLT_EXTENSION;
		}

		void SaveLoadEngine::SaveLoadCheck()
		{
			if(simConnect->savedFileName[0]!='\0') {
				Strcpy(m_SaveFileName,MAX_BUFFER_LENGTH,simConnect->savedFileName);
				simConnect->savedFileName[0]='\0';
				Char* a=strrchr(m_SaveFileName,'\\')+1;
				if(_stricoll(a,m_UIGeneratedFlight.c_str())) {
					Save(m_SaveFileName);
				}
			}
			
			if(simConnect->loadedFileName[0]!='\0') {
				Strcpy(m_LoadFileName,MAX_BUFFER_LENGTH,simConnect->loadedFileName);
				simConnect->loadedFileName[0]='\0';
				Char* a=strrchr(m_LoadFileName,'\\')+1;
				if(_stricoll(a,m_UIGeneratedFlight.c_str())) {
					//simConnect->InitAll();
					Load();
				}
			}
		}

		void SaveLoadEngine::Init(SimConnect* simconnect)
		{
			simConnect=simconnect;

			m_PrevoiusFlight	= "";
			m_UIGeneratedFlight	= "";
			m_LoadFileName[0]	= '\0';
			m_SaveFileName[0]	= '\0';

			PrepareSimSaveFiles();
		}

		void SaveLoadEngine::DeInit()
		{
			SaveLoadCheck();
		}

		void SaveLoadEngine::PreInstall(const String& simpath,const String& savesection)
		{
			rootPath=simpath;
			saveSection=savesection;
		}

		void SaveLoadEngine::Load()
		{
			simConnect->scriptEngine->ExecuteScript("void OnLoad()");
		}

		void SaveLoadEngine::Save(const String& name)
		{
			simConnect->scriptEngine->ExecuteScript("void OnSave()");
		}

		void SaveLoadEngine::Update()
		{
			SaveLoadCheck();
		}

		void SaveLoadEngine::SaveVar(Char* nv,double val)
		{
			char tmp[MAX_BUFFER_LENGTH];
			Sprintf(tmp,"%f",val);
			WritePrivateProfileStringA(saveSection.c_str(),nv,tmp,m_SaveFileName);
		}

		double SaveLoadEngine::LoadVar(Char* nv)
		{
			char tmp[MAX_BUFFER_LENGTH];
			GetPrivateProfileStringA(saveSection.c_str(),nv,"-1234567890",tmp,MAX_BUFFER_LENGTH,m_SaveFileName);
			return boost::lexical_cast<double>(tmp);
		}
	}
}

