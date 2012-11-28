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

class SimConnect;

class Application
{
private:
	SimConnect* simConnect;

	String	panelCustomParameter;
	String	m_RootPath;
	String	m_ConfigFile;
	String	m_ScriptsPath;
	String	m_MediaPath;
	String	m_StartupScript;
	String	m_SaveLoadSection;
	bool	m_ShowDebugConsole;
	bool	m_ConsoleActivated;
	bool	m_ReloadScriptsOnEyeReset;
	bool	m_CheckForSimQuiet;
	bool	m_CheckForSimPaused;
	bool	m_RunFirstTime;
	DWORD	m_WaitTimeForScript;
	int		m_Muted[2];
	int		m_Paused[2];
	bool	m_Installed;

public:
	Application();
	~Application();

	bool Init(SimConnect* simconnect);
	void DeInit();
	void Update();

	void ReadConfig();

	void SetPanelCustomParameter(const String& str);
	void CheckSimMuteFlag();
	void CheckSimPauseFlag();
};


