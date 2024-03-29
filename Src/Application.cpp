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

ID32    gKeyPressed=KEY_NULL;
UINT32  gKeyData=0;

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
	rootPath.assign(temp);

	configFile=rootPath+panelCustomParameter;

	if(!Helpers::FileExists(configFile)) {
		char buf[BUFSIZ];
		Sprintf(buf,"Config file %s not found.",configFile.c_str());
		LOG.Write(buf);
		throw Exception(buf);
		//MessageBoxA(NULL,buf,"Critical error!",0);
	}

	ReadConfig();

	simConnect->scriptEngine->PreInstall(scriptsPath,startupScript,waitTimeForScript);
	simConnect->soundEngine->PreInstall(mediaPath);
	simConnect->saveLoadEngine->PreInstall(rootPath,saveLoadSection);
	simConnect->autopilotEngine->PreInstall();

	if(showDebugConsole&&!consoleActivated) {
		consoleActivated=(AllocConsole()!=0);
	}

	runFirstTime=true;

	muted[0]=muted[1]=simConnect->soundMaster;
	paused[0]=paused[1]=simConnect->simPaused;

	StartKey();

	installed=true;
}

bool Application::Init(SimConnect* simconnect)
{
	simConnect=simconnect;

	showDebugConsole=false;
	consoleActivated=false;
	reloadScriptsOnEyeReset=false;
	checkForSimQuiet=false;
	checkForSimPaused=false;
	installed=false;

	runFirstTime=false;

	RegisterScriptFunctions();

	return true;
}

void Application::DeInit()
{
	StopKey();

	runFirstTime=true;
	if(showDebugConsole&&consoleActivated) {
		consoleActivated=(FreeConsole()==0);
	}
}

void Application::Update()
{
	if(!installed)
		return;

	if(runFirstTime) {
		simConnect->scriptEngine->CompileScriptFinal();
		send_key_event(KEY_THROTTLE_FULL,0);
		send_key_event(KEY_THROTTLE_CUT,0);
		simConnect->scriptEngine->ExecuteScript("void OnStartup()");
		simConnect->saveLoadEngine->Load();
		simConnect->autopilotEngine->Load();
		runFirstTime=false;
	}

	simConnect->saveLoadEngine->Update();
	simConnect->autopilotEngine->Update();

	CheckSimMuteFlag();
	CheckSimPauseFlag();

	if(paused[0])
		return;

	simConnect->scriptEngine->ExecuteScript("void OnUpdate()");

}

void Application::CheckSimMuteFlag()
{
	muted[0]=simConnect->soundMaster;
	if(muted[0]!=muted[1]) {
		if(checkForSimQuiet) {
			if(muted[0]) {
				simConnect->soundEngine->UnMuteAll();
			} else {
				simConnect->soundEngine->MuteAll();
			}
		}
		muted[1]=muted[0];
	}
}

void Application::CheckSimPauseFlag()
{
	paused[0]=simConnect->simPaused;
	if(paused[0]!=paused[1]) {
		if(checkForSimPaused) {
			if(paused[0]) {
				simConnect->soundEngine->UnPauseAll();
			} else {
				simConnect->soundEngine->PauseAll();
			}
		}
		paused[1]=paused[0];
	}
}

void Application::ReadConfig()
{
	waitTimeForScript		= Helpers::FromString<int>(   IniFile::GetValue("ScriptWaitTime"          ,"Debug"   ,configFile));
	showDebugConsole		= Helpers::ParseStringForBool(IniFile::GetValue("DebugConsole"            ,"Debug"   ,configFile));
	reloadScriptsOnEyeReset	= Helpers::ParseStringForBool(IniFile::GetValue("ReloadScriptsOnEyeReset" ,"Debug"   ,configFile));
	checkForSimQuiet		= Helpers::ParseStringForBool(IniFile::GetValue("CheckForSimQuiet"        ,"Sound"   ,configFile));
	checkForSimPaused		= Helpers::ParseStringForBool(IniFile::GetValue("CheckForSimPaused"       ,"Sound"   ,configFile));
	mediaPath				= rootPath+					  IniFile::GetValue("MediaPath"               ,"General" ,configFile)+"\\";
	scriptsPath				= rootPath+					  IniFile::GetValue("ScriptPath"              ,"General" ,configFile)+"\\";
	startupScript			=							  IniFile::GetValue("MainScript"			  ,"General" ,configFile);
	saveLoadSection			=							  IniFile::GetValue("SaveSection"             ,"SaveLoad",configFile);
}

bool Application::fnKeyHandler(ID32 event,UINT32 evdata)
{
	gKeyPressed=event;
	gKeyData=evdata;
	switch(event) {
		case KEY_SITUATION_RESET:
			simConnect->saveLoadEngine->Load();
		break;
		case KEY_EYEPOINT_RESET:
			if(reloadScriptsOnEyeReset) {
				simConnect->scriptEngine->CompileScriptFinal();
				simConnect->scriptEngine->ExecuteScript("void OnStartup()");
				LOG.Write("Script reloaded.\n");
			}
		break;
	}
	return true;
}

#include "ScripEngineFunctions.h"

void Application::RegisterScriptFunctions()
{
	// System
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void Print(string& in)"					,asFUNCTION(PrintStr)				,asCALL_CDECL);

	// Sound
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void PlaySound(string& in)"				,asFUNCTION(sndPlay)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void StopSound(string& in)"				,asFUNCTION(sndStop)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void MuteSound(string& in)"				,asFUNCTION(sndMute)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void UnMuteSound(string& in)"				,asFUNCTION(sndUnMute)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void PauseSound(string& in)"				,asFUNCTION(sndPause)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void UnPauseSound(string& in)"			,asFUNCTION(sndUnPause)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void PlaySoundIfNotPlay(string& in)"		,asFUNCTION(sndPlayIfNotPlaying)	,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("bool IsSoundPlaying(string& in)"			,asFUNCTION(sndIsPlaying)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("int GetSoundVolume(string& in)"			,asFUNCTION(sndGetVolume)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void SetSoundVolume(string& in,int& in)"	,asFUNCTION(sndSetVolume)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void MuteAllSounds()"						,asFUNCTION(sndMuteAll)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void UnMuteAllSounds()"					,asFUNCTION(sndUnMuteAll)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void PauseAllSounds()"					,asFUNCTION(sndPauseAll)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void UnPauseAllSounds()"					,asFUNCTION(sndUnPauseAll)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void StopSoundIfPlay(string &in)"			,asFUNCTION(sndStopIfPlaying)		,asCALL_CDECL);

	// Sim
	simConnect->scriptEngine->GetEngine()->RegisterGlobalProperty("int SimKeyPressed"						,&gKeyPressed);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalProperty("int SimKeyData"							,&gKeyData);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("double GetCToken(int &in)"				,asFUNCTION(GetCToken)				,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("double GetNamedVar(string &in)"			,asFUNCTION(GetNamedVar)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void SetNamedVar(string &in,double &in)"	,asFUNCTION(SetNamedVar)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("int GetNamedVarBoolReset(string &in)"		,asFUNCTION(GetNamedVarBoolReset)	,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("int GetViewMode()"						,asFUNCTION(GetViewMode)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void SetSimEvent(int &in,int &in)"		,asFUNCTION(SetSimEvent)			,asCALL_CDECL);

	// Save load
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("void SaveVar(string &in,double &in)"		,asFUNCTION(SaveVariable)			,asCALL_CDECL);
	simConnect->scriptEngine->GetEngine()->RegisterGlobalFunction("double LoadVar(string &in)"				,asFUNCTION(LoadVariable)			,asCALL_CDECL);

}
