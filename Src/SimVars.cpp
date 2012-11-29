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

bool XMLDimUnits::m_bEnumsInitialised = false;

ENUM XMLDimUnits::m_Boolean			= 0;
ENUM XMLDimUnits::m_Celsius			= 0;
ENUM XMLDimUnits::m_Degrees			= 0;
ENUM XMLDimUnits::m_Feet           	= 0;
ENUM XMLDimUnits::m_FeetPerSecond		= 0;
ENUM XMLDimUnits::m_Kg					= 0;
ENUM XMLDimUnits::m_KgPerSecond		= 0;
ENUM XMLDimUnits::m_Km					= 0;
ENUM XMLDimUnits::m_KmPerHour			= 0;
ENUM XMLDimUnits::m_Knots				= 0;
ENUM XMLDimUnits::m_Meters				= 0;
ENUM XMLDimUnits::m_MeterPerSecond		= 0;	
ENUM XMLDimUnits::m_Number				= 0;
ENUM XMLDimUnits::m_Percent			= 0;
ENUM XMLDimUnits::m_Radians			= 0;
ENUM XMLDimUnits::m_Fahrenheit			= 0;

void XMLDimUnits::Init()
{
	if( m_bEnumsInitialised ) 
		return;

	m_Boolean			= get_units_enum( "bool"                );
	m_Celsius			= get_units_enum( "celsius"             );
	m_Degrees			= get_units_enum( "degrees"             );
	m_Feet           	= get_units_enum( "feet"                ); 
	m_FeetPerSecond		= get_units_enum( "feet per second"     ); 
	m_Kg				= get_units_enum( "kilogram"            );
	m_KgPerSecond		= get_units_enum( "kilogram per second" );
	m_Km				= get_units_enum( "kilometer"           );
	m_KmPerHour			= get_units_enum( "kilometer per hour"  );
	m_Knots				= get_units_enum( "knots"               );
	m_Meters			= get_units_enum( "meters"              );
	m_MeterPerSecond	= get_units_enum( "meters per second"   );
	m_Number			= get_units_enum( "number"              );
	m_Percent			= get_units_enum( "percent"             );
	m_Radians			= get_units_enum( "radian"              );
	m_Fahrenheit		= get_units_enum( "fahrenheit"          );

	m_bEnumsInitialised = true;
}

XMLNamedVar::XMLNamedVar(const char* name, bool unregister_after_use) : m_bUnregisterAfterUse( unregister_after_use )
{
	if((m_VarID=check_named_variable(name))==-1) 
		m_VarID=register_named_variable(name);

	XMLDimUnits::Init();
}

XMLNamedVar::~XMLNamedVar(void)
{
	if(m_bUnregisterAfterUse&&m_VarID!=-1) 
		unregister_var_by_name((PSTRINGZ)get_name_of_named_variable(m_VarID));
}

SimVar::SimVar(GAUGE_TOKEN id) : m_VarID(id)
{ 
	XMLDimUnits::Init(); 

	m_Token.id=(GAUGE_TOKEN)m_VarID;
	initialize_var(&m_Token);
}

