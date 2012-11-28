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
	namespace ScriptEngine
	{
		static void LineCallback(asIScriptContext* ctx,DWORD* timeOut)
		{
			if(*timeOut<timeGetTime())
				ctx->Abort();
		}

		ScriptEngine::ScriptEngine() :	engine(nullptr),
										ctx(nullptr),
										timeOut(0)
		{
		}

		ScriptEngine::~ScriptEngine()
		{
		}

		void ScriptEngine::Init()
		{
			if(engine==nullptr)
				engine=asCreateScriptEngine(ANGELSCRIPT_VERSION);
			if(!engine) {
				throw Exception("Cannot create script engine core.");
			}
			engine->SetMessageCallback(asMETHOD(ScriptEngineMessageCallback,Message),&messageCallback,asCALL_THISCALL);
			RegisterScriptString(engine);
			RegisterScriptStringUtils(engine);
		}

		void ScriptEngine::DeInit()
		{
			FreeCtx();
			FreeEngine();
		}

		void ScriptEngine::FreeCtx()	
		{
			Helpers::SafeRelease(ctx);
		}

		void ScriptEngine::FreeEngine()
		{
			Helpers::SafeRelease(engine);
		}

		void ScriptEngine::CompileScriptFinal()
		{
			if(!engine)
				return;

			int r=CompileScript(engine);
			if(r<0) {
				FreeEngine();
				throw Exception("Cannot compile script");
			}

			if(ctx==NULL)
				ctx=engine->CreateContext();

			if(ctx==0)  {
				FreeEngine();
				throw Exception("Failed to create the script context");
				return;
			}

			timeOut=timeGetTime()+waitTime;
			r=ctx->SetLineCallback(asFUNCTION(LineCallback),&timeOut,asCALL_CDECL);

			if(r<0) {
				FreeCtx();
				FreeEngine();
				throw Exception("Failed to set the line callback function");
			}
			Char* textResult="Script compiled succesfully.\n";
			_cprintf(textResult);
			LOG.Write(textResult);
		}

		int ScriptEngine::CompileScript(asIScriptEngine* engine)
		{
			if(!engine)
				return -1;

			int r;
			CScriptBuilder builder(scriptsPath);

			r=builder.BuildScriptFromFile(engine,0,startupFile.c_str());
			if(r<0) {
				Char* textResult="Script build failed.\n";
				_cprintf(textResult);
				LOG.Write(textResult);
				return r;
			}

			return 0;
		}

		void ScriptEngine::ExecuteScript(char *func)
		{
			if(!engine)
				return;

			int funcId=engine->GetModule(0,asGM_CREATE_IF_NOT_EXISTS)->GetFunctionIdByDecl(func);
			if(funcId<0) {
				String textResult="The function '"+String(func)+"' was not found.\n";
				_cprintf(textResult.c_str());
				LOG.Write(textResult);
				//FreeCtx();
				//FreeEngine();
				return;
			}

			int r=ctx->Prepare(funcId);
			if(r<0) {
				//FreeCtx();
				//FreeEngine();
				//SCS_EXCEPT(Exception::ERR_ANGELSCRIPT,"Failed to prepare the context","ScriptEngine::ExecuteScript()");
				String textResult="Failed to prepare the context. '"+String(func)+"'\n";
				_cprintf(textResult.c_str());
				LOG.Write(textResult);
				return;
			}
			timeOut=timeGetTime()+waitTime;
			r=ctx->Execute();

			if(r!=asEXECUTION_FINISHED) {
				if(r==asEXECUTION_ABORTED) {
					Char* textResult="The script was aborted before it could finish. Probably it timed out.\n";
					_cprintf(textResult);
					LOG.Write(textResult);
				} else if(r==asEXECUTION_EXCEPTION) {
					Char* textResult="The script ended with an exception.\n";
					_cprintf(textResult);
					LOG.Write(textResult);

					int funcID=ctx->GetExceptionFunction();
					asIScriptFunction* func=engine->GetFunctionDescriptorById(funcID);
					char buf[BUFSIZ];
					sprintf_s(buf,"func: %s\nmodl: %s\nsect: %s\nline: %d\ndesc: %s\n",func->GetDeclaration(),func->GetModuleName(),
						func->GetScriptSectionName(),ctx->GetExceptionLineNumber(),
						ctx->GetExceptionString());
					throw Exception(buf);
				} else {
					String textResult="The script ended for some unforeseen reason ("+Helpers::ToString(r)+").\n";
					_cprintf(textResult.c_str());
					LOG.Write(textResult);
				}
			}

		}
	}
}
