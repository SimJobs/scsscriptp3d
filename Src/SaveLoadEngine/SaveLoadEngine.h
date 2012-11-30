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

namespace SCSScript
{
	namespace SaveLoadEngine
	{
		class SaveLoadEngine : boost::noncopyable
		{
		private:
			SimConnect* simConnect;
			String	rootPath;
			String	saveSection;
			String	prevoiusFlight;
			String	UIGeneratedFlight;
			Char	loadFileName[MAX_BUFFER_LENGTH];
			Char	saveFileName[MAX_BUFFER_LENGTH];

			void	PrepareSimSaveFiles();
			void	SaveLoadCheck();

		public:
			void	Init(SimConnect* simconnect);
			void	DeInit();
			void	PreInstall(const String& simpath,const String& savesection);
			void	Load();
			void	Save(const String& name);
			void	Update();
			void	SaveVar(Char* nv,double val);
			double	LoadVar(Char* nv);
		};
	}
}

