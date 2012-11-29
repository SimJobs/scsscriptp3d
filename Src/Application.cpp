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

Application::Application() : simConnect(nullptr)
{
}

Application::~Application()
{
}

void Application::SetPanelCustomParameter(const String& str)
{
	panelCustomParameter=str;

	char temp[MAX_PATH];
	GetModuleFileNameA(NULL,temp,MAX_PATH);
	Helpers::ExtractPath(temp);
	Helpers::CheckForBackSlash(temp);
	m_RootPath.assign(temp);

	m_ConfigFile=m_RootPath+panelCustomParameter;

	if(!Helpers::FileExists(m_ConfigFile)) {
		char buf[BUFSIZ];
		Sprintf(buf,"Config file %s not found.",m_ConfigFile.c_str());
		LOG.Write(buf);
		throw Exception(buf);
		//MessageBoxA(NULL,buf,"Critical error!",0);
	}

	ReadConfig();

	simConnect->scriptEngine->PreInstall(m_ScriptsPath,m_StartupScript,m_WaitTimeForScript);
	simConnect->soundEngine->PreInstall(m_MediaPath);

	if(m_ShowDebugConsole&&!m_ConsoleActivated) {
		m_ConsoleActivated=(AllocConsole()!=0);
	}

	m_RunFirstTime=true;

	m_Muted[0]=m_Muted[1]=simConnect->soundMaster;
	m_Paused[0]=m_Paused[1]=simConnect->simPaused;

	m_Installed=true;
}

bool Application::Init(SimConnect* simconnect)
{
	simConnect=simconnect;

	m_ShowDebugConsole=false;
	m_ConsoleActivated=false;
	m_ReloadScriptsOnEyeReset=false;
	m_CheckForSimQuiet=false;
	m_CheckForSimPaused=false;
	m_Installed=false;

	m_RunFirstTime=false;

	//RegisterScriptFunctions();

	return true;
}

void Application::DeInit()
{
	m_RunFirstTime=false;
	if(m_ShowDebugConsole&&m_ConsoleActivated) {
		m_ConsoleActivated=(FreeConsole()==0);
	}
}

void Application::Update()
{
	if(!m_Installed)
		return;

	if(m_RunFirstTime) {
		simConnect->scriptEngine->CompileScriptFinal();
		//ImportTable.pPanels->send_key_event(KEY_THROTTLE_FULL,0);
		//ImportTable.pPanels->send_key_event(KEY_THROTTLE_CUT,0);
		simConnect->scriptEngine->ExecuteScript("void OnStartup()");
		//m_SaveLoadEngine->Load();
		//m_AutopilotEngine->Load();
		m_RunFirstTime=false;
	}

	CheckSimMuteFlag();
	CheckSimPauseFlag();

	if(m_Paused[0])
		return;

	simConnect->scriptEngine->ExecuteScript("void OnUpdate()");

}

void Application::CheckSimMuteFlag()
{
	m_Muted[0]=simConnect->soundMaster;
	if(m_Muted[0]!=m_Muted[1]) {
		if(m_CheckForSimQuiet) {
			if(m_Muted[0]) {
				simConnect->soundEngine->UnMuteAll();
			} else {
				simConnect->soundEngine->MuteAll();
			}
		}
		m_Muted[1]=m_Muted[0];
	}
}

void Application::CheckSimPauseFlag()
{
	m_Paused[0]=simConnect->simPaused;
	if(m_Paused[0]!=m_Paused[1]) {
		if(m_CheckForSimPaused) {
			if(m_Paused[0]) {
				simConnect->soundEngine->UnPauseAll();
			} else {
				simConnect->soundEngine->PauseAll();
			}
		}
		m_Paused[1]=m_Paused[0];
	}
}

void Application::ReadConfig()
{
	m_WaitTimeForScript			= Helpers::FromString<int>(   IniFile::GetValue("ScriptWaitTime"          ,"Debug"   ,m_ConfigFile));
	m_ShowDebugConsole			= Helpers::ParseStringForBool(IniFile::GetValue("DebugConsole"            ,"Debug"   ,m_ConfigFile));
	m_ReloadScriptsOnEyeReset	= Helpers::ParseStringForBool(IniFile::GetValue("ReloadScriptsOnEyeReset" ,"Debug"   ,m_ConfigFile));
	m_CheckForSimQuiet			= Helpers::ParseStringForBool(IniFile::GetValue("CheckForSimQuiet"        ,"Sound"   ,m_ConfigFile));
	m_CheckForSimPaused			= Helpers::ParseStringForBool(IniFile::GetValue("CheckForSimPaused"       ,"Sound"   ,m_ConfigFile));
	m_MediaPath					= m_RootPath+				  IniFile::GetValue("MediaPath"               ,"General" ,m_ConfigFile)+"\\";
	m_ScriptsPath				= m_RootPath+				  IniFile::GetValue("ScriptPath"              ,"General" ,m_ConfigFile)+"\\";
	m_StartupScript				=							  IniFile::GetValue("MainScript"			  ,"General" ,m_ConfigFile);
	m_SaveLoadSection			=							  IniFile::GetValue("SaveSection"             ,"SaveLoad",m_ConfigFile);
}
