/*
    This file is part of SCSScript.

    Copyright (C) 2006-2012 by Nick Sharmanzhinov

    SCSScript is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation,either version 3 of the License,or
    (at your option) any later version.

    SCSScript is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SCSScript.  If not,see <http://www.gnu.org/licenses/>.

    Nick Sharmanzhinov
    except134@gmail.com
*/

#include "PCH.h"

#ifdef FSX
typedef HRESULT (__stdcall *XSimConnectOpen)(HANDLE* phSimConnect,LPCSTR szName,HWND hWnd,DWORD UserEventWin32,HANDLE hEventHandle,DWORD ConfigIndex);
typedef HRESULT (__stdcall *XSimConnectClose)(HANDLE hSimConnect);
typedef HRESULT (__stdcall *XSimConnectCallDispatch)(HANDLE hSimConnect,DispatchProc pfcnDispatch,void* pContext);
typedef HRESULT (__stdcall *XSimConnectSubscribeToSystemEvent)(HANDLE hSimConnect,SIMCONNECT_CLIENT_EVENT_ID EventID,const char* SystemEventName);
typedef HRESULT (__stdcall *XSimConnectAddToDataDefinition)(HANDLE hSimConnect,SIMCONNECT_DATA_DEFINITION_ID DefineID,const char* DatumName,const char* UnitsName,SIMCONNECT_DATATYPE DatumType,float fEpsilon,DWORD DatumID);
typedef HRESULT (__stdcall *XSimConnectRequestDataOnSimObject)(HANDLE hSimConnect,SIMCONNECT_DATA_REQUEST_ID RequestID,SIMCONNECT_DATA_DEFINITION_ID DefineID,SIMCONNECT_OBJECT_ID ObjectID,SIMCONNECT_PERIOD Period,SIMCONNECT_DATA_REQUEST_FLAG Flags,DWORD origin,DWORD interval,DWORD limit);
typedef HRESULT (__stdcall *XSimConnectSetDataOnSimObject)(HANDLE hSimConnect,SIMCONNECT_DATA_DEFINITION_ID DefineID,SIMCONNECT_OBJECT_ID ObjectID,SIMCONNECT_DATA_SET_FLAG Flags,DWORD ArrayCount,DWORD cbUnitSize,void* pDataSet);

extern "C" 
{
	XSimConnectOpen						SimConnectOpen=nullptr;						
	XSimConnectClose					SimConnectClose=nullptr;					
	XSimConnectCallDispatch				SimConnectCallDispatch=nullptr;				
	XSimConnectSubscribeToSystemEvent	SimConnectSubscribeToSystemEvent=nullptr;	
	XSimConnectAddToDataDefinition		SimConnectAddToDataDefinition=nullptr;		
	XSimConnectRequestDataOnSimObject	SimConnectRequestDataOnSimObject=nullptr;	
	XSimConnectSetDataOnSimObject		SimConnectSetDataOnSimObject=nullptr;		
}

HMODULE moduleSimConnect=nullptr;

const String nameSimConnectDll="SimConnectForSCSScript.dll";

#else

#define SimConnectOpen						SimConnect_Open						
#define SimConnectClose						SimConnect_Close					
#define SimConnectCallDispatch				SimConnect_CallDispatch
#define SimConnectSubscribeToSystemEvent	SimConnect_SubscribeToSystemEvent	
#define SimConnectAddToDataDefinition		SimConnect_AddToDataDefinition		
#define SimConnectRequestDataOnSimObject	SimConnect_RequestDataOnSimObject	
#define SimConnectSetDataOnSimObject		SimConnect_SetDataOnSimObject		

#endif

extern void CALLBACK fnSimConnectDispatchExt(SIMCONNECT_RECV* pData,DWORD cbData,void* pContext)
{
	SimConnect* pMyHandle=(SimConnect*)pContext;

	if(!pMyHandle->addingDefinitions) {
		for(size_t j=0;j<pMyHandle->definitionSimObjectsCount;j++) {
			bool found=false;
			for(size_t i=0;i<pMyHandle->alreadyDefinedCount;i++) {
				if(!_stricmp(pMyHandle->alreadyDefined[i],pMyHandle->definitionSimObjects[j].DatumName)) {
					found=true;
				}
			}
			if(!found) {
				SimConnectAddToDataDefinition(pMyHandle->simConnect,pMyHandle->definitionSimObjects[j].DefineID,pMyHandle->definitionSimObjects[j].DatumName,pMyHandle->definitionSimObjects[j].UnitsName,pMyHandle->definitionSimObjects[j].DatumType,0,SIMCONNECT_UNUSED);
				Strcpy(pMyHandle->alreadyDefined[pMyHandle->alreadyDefinedCount++],pMyHandle->definitionSimObjects[j].DatumName);
			}
		}
	}
	if(!pMyHandle->addingRequests) {
		for(size_t j=0;j<pMyHandle->requestSimObjectsCount;j++) {
			bool found=false;
			for(size_t i=0;i<pMyHandle->alreadyRequestedCount;i++) {
				if(pMyHandle->alreadyRequested[i]==pMyHandle->requestSimObjects[j].RequestID) {
					found=true;
				}
			}
			if(!found) {
				if(pMyHandle->requestSimObjects[j].RequestID!=-1) {
					SimConnectRequestDataOnSimObject(pMyHandle->simConnect,pMyHandle->requestSimObjects[j].RequestID,pMyHandle->requestSimObjects[j].DefineID,pMyHandle->requestSimObjects[j].ObjectID,pMyHandle->requestSimObjects[j].Period,pMyHandle->requestSimObjects[j].Flags,0,0,0); 
					pMyHandle->alreadyRequested[pMyHandle->alreadyRequestedCount++]=pMyHandle->requestSimObjects[j].RequestID;
				}
			}
		}
	}

	return pMyHandle->fnSimConnectDispatch(pData,cbData);
}

SimConnect::SimConnect() : simConnect(nullptr)
{
	simTick18=0;
	timeoutBeforeStartUpdate=1;
}

SimConnect::~SimConnect()
{
}

void SimConnect::InitAll()
{
	soundEngine->Init(windowHandle);
	scriptEngine->Init();
	saveLoadEngine->Init(this);
	autopilotEngine->Init();
	application->Init(this);
}

bool SimConnect::Init(HWND windowhandle)
{
	if(simConnect)
		return true;

#ifdef FSX
	GetModuleFileName(gHModule,gaugePath,MAX_BUFFER_LENGTH);
	Helpers::ExtractPath(gaugePath);
	String simconnectModuleName=gaugePath+nameSimConnectDll;

	moduleSimConnect=LoadLibrary(simconnectModuleName.c_str());
	if(!moduleSimConnect) {
		LOG.Write("Could not load SimConnectForSCSScript.dll\n");
		return false;
	}

	if (!(SimConnectOpen = (XSimConnectOpen)GetProcAddress(moduleSimConnect,"SimConnect_Open")))
		return false;
	if (!(SimConnectClose = (XSimConnectClose)GetProcAddress(moduleSimConnect,"SimConnect_Close")))
		return false;
	if (!(SimConnectCallDispatch = (XSimConnectCallDispatch)GetProcAddress(moduleSimConnect,"SimConnect_CallDispatch")))
		return false;
	if (!(SimConnectSubscribeToSystemEvent = (XSimConnectSubscribeToSystemEvent)GetProcAddress(moduleSimConnect,"SimConnect_SubscribeToSystemEvent")))
		return false;
	if (!(SimConnectAddToDataDefinition = (XSimConnectAddToDataDefinition)GetProcAddress(moduleSimConnect,"SimConnect_AddToDataDefinition")))
		return false;
	if (!(SimConnectRequestDataOnSimObject = (XSimConnectRequestDataOnSimObject)GetProcAddress(moduleSimConnect,"SimConnect_RequestDataOnSimObject")))
		return false;
	if (!(SimConnectSetDataOnSimObject = (XSimConnectSetDataOnSimObject)GetProcAddress(moduleSimConnect,"SimConnect_SetDataOnSimObject")))
		return false;

#endif 

	windowHandle=windowhandle;

	addingDefinitions=false;
	addingRequests=false;

	alreadyDefinedCount=0;
	definitionSimObjectsCount=0;

	alreadyRequestedCount=0;
	requestSimObjectsCount=0;

	for(size_t i=0;i<MAX_REQUESTS;i++) {
		requestSimObjects[i].DefineID=-1;
		requestSimObjects[i].RequestID=-1;
		requestSimObjects[i].Val=0;
		requestSimObjects[i].ValToSet=0;
		requestSimObjects[i].ValToSetFlag=false;
		alreadyRequested[i]=-1;
	}

	quitSignalCatch=false;

	savedFileName[0]='\0';
	loadedFileName[0]='\0';
	flightPlanActivated[0]='\0';

	flightPlanDeActivated=false;

	simPaused=true;

	crashed=false;
	crashReset=false;

	simFrameRate=0;
	simSpeed=0;

	simPauseFrameRate=0;
	simPauseSpeed=0;

	LOG.FakeInit();

	soundEngine		=boost::shared_ptr<SoundEngine::SoundEngine>(new SoundEngine::SoundEngine());
	scriptEngine	=boost::shared_ptr<ScriptEngine::ScriptEngine>(new ScriptEngine::ScriptEngine());
	saveLoadEngine	=boost::shared_ptr<SaveLoadEngine::SaveLoadEngine>(new SaveLoadEngine::SaveLoadEngine());
	autopilotEngine	=boost::shared_ptr<AutopilotEngine::AutopilotEngine>(new AutopilotEngine::AutopilotEngine());
	application		=boost::shared_ptr<Application>(new Application());

	soundEngine->Init(windowHandle);
	scriptEngine->Init();
	saveLoadEngine->Init(this);
	autopilotEngine->Init();
	application->Init(this);

	HRESULT hr=SimConnectOpen(&simConnect,"SCSScript",windowHandle,0,0,0);
	if(hr) {
		LOG.Write("SCSScript could not connect to Flight Simulator!\n","");   
		return false;
	}

	LOG.Write("SCSScript connected to Flight Simulator!\n","");   

	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_1SEC						,"1sec");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_4SEC						,"4sec");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_6HZ						,"6Hz");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_CRASHED					,"Crashed");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_CRASHRESET				,"CrashReset");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_FLIGHT_LOAD					,"FlightLoaded");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_FLIGHT_SAVE					,"FlightSaved");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_FLIGHTPLAN_ACTIVATED		,"FlightPlanActivated");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_FLIGHTPLAN_DEACTIVATED	,"FlightPlanDeactivated");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_FRAME					,"Frame");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_PAUSE					,"Pause");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_PAUSED					,"Paused");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_PAUSEFRAME				,"PauseFrame");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_POSITION_CHANGED			,"PositionChanged");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_SIM						,"Sim");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_START					,"SimStart");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_STOP						,"SimStop");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_SOUND					,"Sound");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_UNPAUSED					,"Unpaused");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_VIEW						,"View");
	SimConnectSubscribeToSystemEvent(simConnect,EVENT_SIM_WEATHER_MODE_CHANGED		,"WeatherModeChanged");

	SimConnectCallDispatch(simConnect,fnSimConnectDispatchExt,this);

	static bool m_AlreadyLoaded=false;

	if(!m_AlreadyLoaded) {
		panel_window_open_ident(IDENT_MAIN_PANEL);
		panel_window_close_ident(IDENT_MAIN_PANEL);
		m_AlreadyLoaded=true;
	} 

	InitVars();

	application->Update();

	return true;
}

void SimConnect::DeInit()
{
	if(simConnect) {
		SimConnectClose(simConnect);
		simConnect=nullptr;
	}

#ifdef FSX
	FreeLibrary(moduleSimConnect);
	moduleSimConnect=nullptr;
#endif

	application->DeInit();
	autopilotEngine->DeInit();
	saveLoadEngine->DeInit();
	scriptEngine->DeInit();
	soundEngine->DeInit();
}

void SimConnect::Update()
{
	try {
#ifdef FSX
		SimConnectCallDispatch(simConnect,fnSimConnectDispatchExt,this);
#endif 
		application->Update();
	} catch(Exception& e) {
		LOG.Write(e.what());
		MessageBox(NULL,e.what(),"An exception has occured!",MB_OK|MB_ICONERROR|MB_TASKMODAL);
	}
}

void SimConnect::fnSimConnectDispatch(SIMCONNECT_RECV *pData,DWORD cbData)
{
	switch(pData->dwID) {
		case SIMCONNECT_RECV_ID_EVENT_FILENAME: {
			SIMCONNECT_RECV_EVENT_FILENAME *evt = (SIMCONNECT_RECV_EVENT_FILENAME*)pData;
			switch(evt->uEventID) {
				case EVENT_FLIGHT_SAVE:
					Strcpy(savedFileName,MAX_PATH,evt->szFileName);
				break;
				case EVENT_FLIGHT_LOAD:
					Strcpy(loadedFileName,MAX_PATH,evt->szFileName);
				break;
				case EVENT_SIM_FLIGHTPLAN_ACTIVATED:
					Strcpy(flightPlanActivated,MAX_PATH,evt->szFileName);
				break;
			}
		}break;

		case SIMCONNECT_RECV_ID_EVENT: {
			SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

			switch(evt->uEventID) {
				case EVENT_SIM_1SEC:
				break;
				case EVENT_SIM_4SEC:
				break;
				case EVENT_SIM_6HZ:
				break;
				case EVENT_SIM_CRASHED:
					crashed=true;
				break;
				case EVENT_SIM_CRASHRESET:
					crashReset=true;
				break;
				case EVENT_SIM_FLIGHTPLAN_DEACTIVATED:
					flightPlanDeActivated=true;
				break;
				case EVENT_SIM_PAUSE:
					simPaused=(bool)evt->dwData;
				break;
				case EVENT_SIM_PAUSED:
					simPaused=true;
				break;
				case EVENT_SIM_UNPAUSED:
					simPaused=false;
				break;
				case EVENT_SIM_POSITION_CHANGED:
					positionChanged=true;
				break;
				case EVENT_SIM_SIM:
					simRunning=(bool)evt->dwData;
				break;
				case EVENT_SIM_START:
					simRunning=true;
				break;
				case EVENT_SIM_STOP:
					simRunning=false;
				break;
				case EVENT_SIM_SOUND:
					soundMaster=(bool)evt->dwData;
				break;
				case EVENT_SIM_VIEW:
					activeViewMode=evt->dwData;
				break;
				case EVENT_SIM_WEATHER_MODE_CHANGED:
					weatherModeChanged=true;
				break;
			}
		}break;

		case SIMCONNECT_RECV_ID_EVENT_FRAME: {
			SIMCONNECT_RECV_EVENT_FRAME  *evt = (SIMCONNECT_RECV_EVENT_FRAME *)pData;

			switch(evt->uEventID) {
				case EVENT_SIM_FRAME: {
					simFrameRate=evt->fFrameRate;
					simSpeed=evt->fSimSpeed;
					double curTick18=GetC(TICK18);
					if(curTick18>simTick18) {
						if(GetC(ELAPSED_SECONDS)>timeoutBeforeStartUpdate) {
							Update();
						}
					}
					simTick18=curTick18;
				}break;
				case EVENT_SIM_PAUSEFRAME:
					simPauseFrameRate=evt->fFrameRate;
					simPauseSpeed=evt->fSimSpeed;
				break;
			}
		}break;

		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA: {
			SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

			for(size_t i=0;i<requestSimObjectsCount;i++) {
				if(requestSimObjects[i].RequestID==pObjData->dwRequestID) {
					requestSimObjects[i].Data=&pObjData->dwData;
					requestSimObjects[i].Val=*((double *)requestSimObjects[i].Data);
					//PRINTINFO2("Got data from request: ReqID=%d %f",m_RequestSimObjects[i].RequestID,*((double *)m_RequestSimObjects[i].Data));
					//PRINTINFO2("State of data to set: Flag=%d Val=%f",m_RequestSimObjects[i].ValToSetFlag,m_RequestSimObjects[i].ValToSet);
					if(requestSimObjects[i].ValToSetFlag) {
						requestSimObjects[i].Data=&pObjData->dwData;
						double tmp=*((double *)requestSimObjects[i].Data);
						tmp=requestSimObjects[i].ValToSet;
						 SimConnectSetDataOnSimObject(simConnect,requestSimObjects[i].DefineID,requestSimObjects[i].ObjectID,0,0,sizeof(double),&tmp);
						requestSimObjects[i].ValToSetFlag=false;
						LOG.Write("Set data: DefID=%d %f",requestSimObjects[i].DefineID,requestSimObjects[i].ValToSet);
					}
				}
			}
		}break;

		case SIMCONNECT_RECV_ID_QUIT:
			quitSignalCatch=true;
		break;
	}
}

