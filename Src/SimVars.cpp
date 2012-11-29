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

bool XMLDimUnits::enumsInitialized = false;

ENUM XMLDimUnits::boolean			= 0;
ENUM XMLDimUnits::celsius			= 0;
ENUM XMLDimUnits::degrees			= 0;
ENUM XMLDimUnits::feet           	= 0;
ENUM XMLDimUnits::feetPerSecond		= 0;
ENUM XMLDimUnits::kg					= 0;
ENUM XMLDimUnits::kgPerSecond		= 0;
ENUM XMLDimUnits::km					= 0;
ENUM XMLDimUnits::kmPerHour			= 0;
ENUM XMLDimUnits::knots				= 0;
ENUM XMLDimUnits::meters				= 0;
ENUM XMLDimUnits::meterPerSecond		= 0;	
ENUM XMLDimUnits::number				= 0;
ENUM XMLDimUnits::percent			= 0;
ENUM XMLDimUnits::radians			= 0;
ENUM XMLDimUnits::fahrenheit			= 0;

void XMLDimUnits::Init()
{
	if( enumsInitialized ) 
		return;

	boolean			= get_units_enum( "bool"                );
	celsius			= get_units_enum( "celsius"             );
	degrees			= get_units_enum( "degrees"             );
	feet           	= get_units_enum( "feet"                ); 
	feetPerSecond		= get_units_enum( "feet per second"     ); 
	kg				= get_units_enum( "kilogram"            );
	kgPerSecond		= get_units_enum( "kilogram per second" );
	km				= get_units_enum( "kilometer"           );
	kmPerHour			= get_units_enum( "kilometer per hour"  );
	knots				= get_units_enum( "knots"               );
	meters			= get_units_enum( "meters"              );
	meterPerSecond	= get_units_enum( "meters per second"   );
	number			= get_units_enum( "number"              );
	percent			= get_units_enum( "percent"             );
	radians			= get_units_enum( "radian"              );
	fahrenheit		= get_units_enum( "fahrenheit"          );

	enumsInitialized = true;
}

XMLNamedVar::XMLNamedVar(const char* name, bool unregister_after_use) : unregisterAfterUse( unregister_after_use )
{
	if((varID=check_named_variable(name))==-1) 
		varID=register_named_variable(name);

	XMLDimUnits::Init();
}

XMLNamedVar::~XMLNamedVar(void)
{
	if(unregisterAfterUse&&varID!=-1) 
		unregister_var_by_name((PSTRINGZ)get_name_of_named_variable(varID));
}

SimVar::SimVar(GAUGE_TOKEN id) : varID(id)
{ 
	XMLDimUnits::Init(); 

	token.id=(GAUGE_TOKEN)varID;
	initialize_var(&token);
}

