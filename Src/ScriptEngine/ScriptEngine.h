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
	namespace ScriptEngine
	{
		class ScriptEngineMessageCallback
		{
		public:
			void Message(asSMessageInfo *msg) 
			{ 
				const Char* msgType=0;
				if(msg->type==asMSGTYPE_ERROR) 
					msgType="Error  ";
				if(msg->type==asMSGTYPE_WARNING) 
					msgType="Warning";
				if(msg->type==asMSGTYPE_INFORMATION) 
					msgType="Info   ";
				Char buf[MAX_BUFFER_LENGTH];
				Sprintf(buf,"%s (%d, %d) : %s : %s\n",msg->section,msg->row,msg->col,msgType,msg->message);
				LOG.Write(buf);
				_cprintf(buf);
			}
		};

		class ScriptEngine : boost::noncopyable
		{
		private:
			String						scriptsPath;
			String						startupFile;
			asIScriptEngine*			engine;
			asIScriptContext*			ctx;
			ScriptEngineMessageCallback	messageCallback;
			DWORD						timeOut;
			DWORD						waitTime;

		private:
			int							CompileScript(asIScriptEngine* engine);
			void						FreeCtx();
			void						FreeEngine();

		public:
			ScriptEngine();
			virtual ~ScriptEngine();

			void						Init();
			void						DeInit();
			void						PreInstall(const String& path,const String& file,DWORD wt) { scriptsPath=path; startupFile=file; waitTime=wt; };
			void						CompileScriptFinal();
			void						ExecuteScript(Char* func);
			asIScriptEngine*			GetEngine() const { return engine; };
		};
	}
}

