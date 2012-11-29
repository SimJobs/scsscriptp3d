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
	String		panelCustomParameter;
	String		rootPath;
	String		configFile;
	String		scriptsPath;
	String		mediaPath;
	String		startupScript;
	String		saveLoadSection;
	bool		showDebugConsole;
	bool		consoleActivated;
	bool		reloadScriptsOnEyeReset;
	bool		checkForSimQuiet;
	bool		checkForSimPaused;
	bool		runFirstTime;
	DWORD		waitTimeForScript;
	int			muted[2];
	int			paused[2];
	bool		installed;

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


