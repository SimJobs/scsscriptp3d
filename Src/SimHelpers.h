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

class MeasureHelpers
{
public:
	static const double Pi;
	static const double TicksPerSecond;
	static const double FsLatFactor;
	static const double FsLonFactor;
	static const double LatDivider;
	static const double LonDivider;
	static const double FuelLevelPercent;
	static const double RadiansDegreeFactor;
	static const double MeterFeetFactor;
	static const double KilometerNmMileFactor;
	static const double PoundKilogramFactor;
	static const double MeterPerSecondKnotFactor;
	static const double GallonLitreFactor;
	static const double InchHgPsiFactor;
	static const double LbsKilogramFactor;
	static const double PsiPsfFactor;

	static double FeetToMeter(double val)					{ return val/MeterFeetFactor; }
	static double MeterToFeet(double val)					{ return val*MeterFeetFactor; }

	static double NauticMileToMeter(double val)				{ return val*(1000.0/KilometerNmMileFactor); } 
	static double MeterToNauticMile(double val)				{ return val*(KilometerNmMileFactor/1000.0); }

	static double PoundToKilogram(double pound)				{ return pound*PoundKilogramFactor; }
	static double KilogramToPound(double kilogram)			{ return kilogram/PoundKilogramFactor; }

	static double PoundToMetricTon(double pound)			{ return PoundKilogramFactor*pound/1000.0; } 
	static double MetricTonToPound(double ton)				{ return (ton*1000.0)/PoundKilogramFactor; }

	static double MeterPerSecondToKnot(double val)			{ return val*MeterPerSecondKnotFactor; }
	static double KnotToMeterPerSecond(double val)			{ return val/MeterPerSecondKnotFactor; }

	static double LitreToGallon(double litre)				{ return litre/GallonLitreFactor; }
	static double GallonToLitre(double gallon)				{ return gallon*GallonLitreFactor; }

	static double PsiToPsf(double press)					{ return PsiPsfFactor*press; }
	static double PsfToPsi(double press)					{ return press/PsiPsfFactor; }

	static double InchHgToPsi(double press)					{ return press*InchHgPsiFactor; }
	static double PsiToInchHg(double press)					{ return press/InchHgPsiFactor; }

	static double InchHgToPsf(double press)					{ return press*InchHgPsiFactor*PsiPsfFactor; }
	static double PsfToInchHg(double press)					{ return press/InchHgPsiFactor/PsiPsfFactor; }

	static double FahrenheitToCelsius(double fahrenheit)	{ return 5.0/9.0*(fahrenheit-32.0); }
	static double CelsiusToFahrenheit(double celsius)		{ return 32.0+9.0/5.0*celsius; }

	static double CelsiusToKelvin(double celsius)			{ return celsius+273.15; }
	static double KelvinToCelsius(double kelvin)			{ return kelvin-273.15; }

	static double RankineToKelvin(double rankine)			{ return 5.0/9.0*rankine; }
	static double KelvinToRankine(double kelvin)			{ return 9.0/5.0*kelvin; }

	static double RankineToFahrenheit(double rankine)		{ return rankine-459.67; }
	static double FahrenheitToRankine(double fahrenheit)	{ return fahrenheit+459.67; }

	static double CelsiusToRankine(double celsius)			{ return FahrenheitToRankine(CelsiusToFahrenheit(celsius)); } 
	static double RankineToCelsius(double rankine)			{ return FahrenheitToCelsius(RankineToFahrenheit(rankine)); }

	static double FsLatitudeDegrees(double val)				{ return val/FsLatFactor; }	//FS latitude conversion to degrees latitude (north positive,south negative)
	static double FsLongitudeDegrees(double val)			{ return (val>140737488355332)?val/FsLonFactor-360.0:val/FsLonFactor; }	//FS longitude conversion to degrees longitude (east positive,west negative)

	static double FsVerticalSpeedFeet(double val)			{ return MeterToFeet(val/256.0)*60.0; } //FS vertical speed in feet/min from 1/256 m/sec

	static double FsGroundAltFeet(double val)				{ return MeterToFeet(val/256.0); } //ground altittude in feet
	static double FsPlaneAltFeet(double val)				{ return MeterToFeet(val); } //plane altitude in feet
	static double FsMach(double val)						{ return val*3.2/65536.0; }

	static double DegreesSin(double val)					{ return sin(val/RadiansDegreeFactor); }			//sinus in degrees
	static double DegreesCos(double val)					{ return cos(val/RadiansDegreeFactor); }			//cosine in degrees
	static double DegreesTan(double val)					{ return tan(val/RadiansDegreeFactor); }			//tangens in degrees
	static double DegreesAsin(double val)					{ return RadiansDegreeFactor*asin(val); }			//arcsinus in degrees
	static double DegreesAcos(double val)					{ return RadiansDegreeFactor*acos(val); }			//arccosine in degrees
	static double DegreesAtan(double val)					{ return RadiansDegreeFactor*atan(val); }			//arctangens in degrees
	static double DegreesAtan2(double val1,double val2)		{ return RadiansDegreeFactor*atan2(val1,val2); }	//atan2 in degrees

	static double LbsToKg(double val)						{ return PoundToKilogram(val); }
	static double KgToLbs(double val)						{ return KilogramToPound(val); }
};

const double MeasureHelpers::Pi							= 3.1415926535897932384626433832795;
const double MeasureHelpers::TicksPerSecond				= 18;
const double MeasureHelpers::FsLatFactor				= 111130.555557;
const double MeasureHelpers::FsLonFactor				= 781874935307.40;
const double MeasureHelpers::LatDivider					= 40007000.0;
const double MeasureHelpers::LonDivider					= 281474976710656.0;
const double MeasureHelpers::FuelLevelPercent			= 83886.08;
const double MeasureHelpers::RadiansDegreeFactor		= 180.0/Pi;
const double MeasureHelpers::MeterFeetFactor			= 3.28084;
const double MeasureHelpers::KilometerNmMileFactor		= 0.54;
const double MeasureHelpers::PoundKilogramFactor		= 0.453592;
const double MeasureHelpers::MeterPerSecondKnotFactor	= 1.944;
const double MeasureHelpers::GallonLitreFactor			= 3.785;
const double MeasureHelpers::InchHgPsiFactor			= 0.4912;
const double MeasureHelpers::LbsKilogramFactor			= 2.2046;
const double MeasureHelpers::PsiPsfFactor				= 144.0;


