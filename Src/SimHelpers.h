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

#define		PI									3.1415926535897932384626433832795		//circle number

#define		TICKS_PER_SEC						18

#define		FS_LAT_FACTOR						111130.555557
#define		FS_LON_FACTOR						781874935307.40
#define		LAT_DIVIDER 						40007000.0
#define		LON_DIVIDER 						281474976710656.0
#define		FUEL_LEVEL_PCT						83886.08
#define		RADIANS_TO_DEGREE_FACTOR			(180.0/PI)
#define		METER_FEET_FACTOR					3.28084
#define		KILOMETER_NM_MILE_FACTOR			0.54
#define		POUND_KILOGRAM_FACTOR				0.453592
#define		METER_PER_SECOND_KNOT_FACTOR		1.944
#define		GALLON_LITRE_FACTOR					3.785
#define		INCH_HG_PSI_FACTOR					(.4912)
#define		LBS_KILOGRAMM_FACTOR				2.2046

//useful conversion macros
#define		FEET_TO_METER( val )				( ( val )/METER_FEET_FACTOR )
#define		METER_TO_FEET( val )				( ( val )*METER_FEET_FACTOR )

#define		NAUTIC_MILE_TO_METER( val )			( ( val )*(1000.0/KILOMETER_NM_MILE_FACTOR) )
#define		METER_TO_NAUTIC_MILE( val )			( ( val )*(KILOMETER_NM_MILE_FACTOR/1000.0) )

#define		POUND_TO_KILOGRAM( pound )			( ( pound ) *  POUND_KILOGRAM_FACTOR )
#define		KILOGRAM_TO_POUND( kilogram )		( ( kilogram ) /  POUND_KILOGRAM_FACTOR )

#define		POUND_TO_METRIC_TON( pound )		( POUND_KILOGRAM_FACTOR*(pound)/1000.0 )
#define		METRIC_TON_TO_POUND( ton )			( (( ton )* 1000.0)/POUND_KILOGRAM_FACTOR )

#define		METER_PER_SECOND_TO_KNOT( val )		( ( val )*METER_PER_SECOND_KNOT_FACTOR )
#define		KNOT_TO_METER_PER_SECOND( val )		( ( val )/METER_PER_SECOND_KNOT_FACTOR )

#define		LITRE_TO_GALLON( litre )			( (litre)/GALLON_LITRE_FACTOR )
#define		GALLON_TO_LITRE( gallon )			( (gallon)*GALLON_LITRE_FACTOR )

#define		PSI_TO_PSF(press)	(144.0*(press))
#define		PSF_TO_PSI(press)	((press)/144.0)

#define		INCH_HG_TO_PSI(press)	((press)*INCH_HG_PSI_FACTOR)
#define		PSI_TO_INCH_HG(press)	((press)/INCH_HG_PSI_FACTOR)

#define		INCH_HG_TO_PSF(press)	((press)*INCH_HG_PSI_FACTOR*144.0)
#define		PSF_TO_INCH_HG(press)	((press)/INCH_HG_PSI_FACTOR/144.0)
//temperature conversions
#define		FAHRENHEIT_TO_CELSIUS( fahrenheit )	( 5.0/9.0*((fahrenheit)-32.0) )
#define		CELSIUS_TO_FAHRENHEIT( celsius )	( 32.0+9.0/5.0*(celsius) )

#define		CELSIUS_TO_KELVIN( celsius )		( (celsius)+273.15 )
#define		KELVIN_TO_CELSIUS( kelvin )			( (kelvin)-273.15 )

#define		RANKINE_TO_KELVIN( rankine )		( 5.0/9.0*(rankine) )
#define		KELVIN_TO_RANKINE( kelvin )			( 9.0/5.0*(kelvin) )

#define		RANKINE_TO_FAHRENHEIT( rankine )	( (rankine)-459.67 )
#define		FAHRENHEIT_TO_RANKINE( fahrenheit )	( (fahrenheit)+459.67 )

#define		CELSIUS_TO_RANKINE( celsius )		( FAHRENHEIT_TO_RANKINE(CELSIUS_TO_FAHRENHEIT(celsius)) )
#define		RANKINE_TO_CELSIUS( rankine )		( FAHRENHEIT_TO_CELSIUS(RANKINE_TO_FAHRENHEIT(rankine)) )

// flightsimulator related conversion macros
#define		FS_LATITUDE_DEG( val )	 (( val )/FS_LAT_FACTOR)		//FS latitude conversion to degrees latitude (north positive,south negative)
#define		FS_LONGITUDE_DEG( val )	 ( ( val ) > 140737488355332) ? ( val )/FS_LON_FACTOR-360.0 : ( val )/FS_LON_FACTOR	//FS longitude conversion to degrees longitude (east positive,west negative)

#define		FS_VSPD_FT( val)		(METER_TO_FEET((val)/256.0)*60.0)//FS vertical speed in feet/min from 1/256 m/sec

#define		FS_GROUND_ALT_FT(val)	(METER_TO_FEET((val)/256.0))	//ground altittude in feet
#define		FS_PLANE_ALT_FT(val)	(METER_TO_FEET(val))			//plane altitude in feet
#define		FS_MACH(val)			(val*3.2/65536.0)
//trigonometric functions in degrees instead of radians
#define		DEG_SIN( val )	sin( ( val )/RADIANS_TO_DEGREE_FACTOR)					//sinus in degrees
#define		DEG_COS( val )	cos( ( val )/RADIANS_TO_DEGREE_FACTOR)					//cosine in degrees
#define		DEG_TAN( val )	tan( ( val )/RADIANS_TO_DEGREE_FACTOR)					//tangens in degrees
#define		DEG_ASIN( val )	RADIANS_TO_DEGREE_FACTOR * asin(( val ))				//arcsinus in degrees
#define		DEG_ACOS( val )	RADIANS_TO_DEGREE_FACTOR * acos(( val ))				//arccosine in degrees
#define		DEG_ATAN( val )	RADIANS_TO_DEGREE_FACTOR * atan(( val ))				//arctangens in degrees
#define		DEG_ATAN2( val1 ,val2 )	RADIANS_TO_DEGREE_FACTOR * atan2( val1,val2 )	//atan2 in degrees

#define		LBS_TO_KG(val)	POUND_TO_KILOGRAM((val))
#define		KG_TO_LBS(val)	KILOGRAM_TO_POUND((val))
