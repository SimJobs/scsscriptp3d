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

//////////////////////////////////////////////////////////////////////////
// System
#include <windows.h>
#include <shlwapi.h>
#include <time.h>
#include <conio.h>
#include <tchar.h>
#include <process.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <exception>

//////////////////////////////////////////////////////////////////////////
// DirectX
#include <dsound.h>
#include <dxerr.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dxerr.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dxguid.lib")

//////////////////////////////////////////////////////////////////////////
// Angelscript
#include "angelscript.h"
#include "scriptstring.h"
#include "scriptstdstring.h"
#include "scriptbuilder.h"

//////////////////////////////////////////////////////////////////////////
// Boost
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/noncopyable.hpp>

//////////////////////////////////////////////////////////////////////////
// Prepar3D
#include "gauges.h"
#include "simconnect.h"

#pragma comment(lib,"simconnect.lib")

//////////////////////////////////////////////////////////////////////////
// Local

const size_t MAX_BUFFER_LENGTH=4096;

#include "../Res/VersionNo.h"
#include "../Res/resource.h"

extern HMODULE gHModule;

//////////////////////////////////////////////////////////////////////////
// Library

#include "Lib/Types.h"
#include "Lib/Helpers.h"
#include "Lib/Exception.h"
#include "Lib/DateTime.h"
#include "Lib/VersionInfo.h"
#include "Lib/WriterASCII.h"
#include "Lib/Logger.h"
#include "Lib/IniFile.h"

//////////////////////////////////////////////////////////////////////////
// Sound Engine

#include "SoundEngine/SoundEngineWavReader.h"
#include "SoundEngine/SoundEngineSound.h"
#include "SoundEngine/SoundEngine.h"

//////////////////////////////////////////////////////////////////////////
// Script Engine

#include "ScriptEngine/ScriptEngine.h"

//////////////////////////////////////////////////////////////////////////
// Logic

using namespace SCSScript;

#include "SimHelpers.h"
#include "SimVars.h"
#include "Application.h"
#include "SimConnectWrapper.h"


