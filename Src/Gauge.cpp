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

#define GAUGE_HEADER_EX(default_size_mm,gauge_name,element_list,pmouse_rect,pgauge_callback,user_data,parameters,usage,gvn) \
	extern PELEMENT_HEADER element_list; \
	GAUGE_HEADER_FS1000(gvn,default_size_mm,gauge_name,&element_list,pmouse_rect,pgauge_callback,user_data,usage,0,0,0,0,0,0)

#define	MY_STATIC_STANDART(NAME,NAMELIST,RES_ID,NEXT_LIST,GAUGEHDR_VAR_NAME) \
	ELEMENT_STATIC_IMAGE NAME={ELEMENT_TYPE_STATIC_IMAGE,RES_ID,0,0,{0,0},{0,0},&GAUGEHDR_VAR_NAME,NULL,(PPELEMENT_HEADER)(NEXT_LIST),(PFAILURE_RECORD)(NULL),IMAGE_USE_TRANSPARENCY|IMAGE_USE_ERASE,0,0}; \
	PELEMENT_HEADER NAMELIST=&NAME.header;

SimConnect* simConnect=nullptr;

void FSAPI cbScriptEngine(PGAUGEHDR pgauge,SINT32 service_id,UINT32 extra_data) 
{
	switch(service_id) {
		case PANEL_SERVICE_PRE_INSTALL: {
			try {
				Char* GaugeParameter=pgauge->parameters;
				for(size_t i=strlen(GaugeParameter);i>0;i--) {
					if(GaugeParameter[i]==' ')  {
						GaugeParameter[i]='\0';
						break;
					}
				}  
				if(simConnect) {
					simConnect->SetPanelCustomParameter(GaugeParameter);
				}
			} catch(Exception& e) {
				LOG.Write(e.what());
				MessageBox(NULL,e.what(),"An exception has occured!",MB_OK|MB_ICONERROR|MB_TASKMODAL);
			}
		}break;
	}
}

void FSAPI fnInitGauge()
{
	try {
		if(!simConnect) {
			simConnect=new SimConnect();
			simConnect->Init(FindWindow("FS98MAIN",nullptr));
		}
	} catch(Exception& e) {
		LOG.Write(e.what());
		MessageBox(NULL,e.what(),"An exception has occured!",MB_OK|MB_ICONERROR|MB_TASKMODAL);
	}
}

void FSAPI fnDeinitGauge()
{
	try {
		if(simConnect) {
			simConnect->DeInit();
			Helpers::SafeDelete(simConnect);
		}
	} catch(Exception& e) {
		LOG.Write(e.what());
		MessageBox(NULL,e.what(),"An exception has occured!",MB_OK|MB_ICONERROR|MB_TASKMODAL);
	}
}

GAUGE_HEADER_EX(1,"main",lstScriptEngine,nullptr,cbScriptEngine,0,0,0,hdrScriptEngine); 
MY_STATIC_STANDART(ScriptEnginebg,lstScriptEngine,0,nullptr,hdrScriptEngine);

GAUGESIMPORT ImportTable =
{
	{ 0x0000000F, (PPANELS)NULL },
	{ 0x00000000, NULL }
};

GAUGESLINKAGE Linkage={
	0x00000013,
	fnInitGauge,
	fnDeinitGauge,
	0,0,
	FS9LINK_VERSION,
	{
		(&hdrScriptEngine),
		0
	}
};
