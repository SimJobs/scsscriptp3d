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

class XMLDimUnits 
{
public:
	static void Init();

	static ENUM m_Boolean		;
	static ENUM m_Celsius		;
	static ENUM m_Degrees		;
	static ENUM m_Feet          ;
	static ENUM m_FeetPerSecond	;
	static ENUM m_Kg			;
	static ENUM m_KgPerSecond	;
	static ENUM m_Km			;
	static ENUM m_KmPerHour		;
	static ENUM m_Knots			;
	static ENUM m_Meters		;
	static ENUM m_MeterPerSecond;
	static ENUM m_Number		;
	static ENUM m_Percent		;
	static ENUM m_Radians		;
	static ENUM m_Fahrenheit	;

protected:
	static bool m_bEnumsInitialised;
};

class XMLNamedVar
{
public:
	XMLNamedVar(const char *name, bool unregister_after_use=false);
	~XMLNamedVar(void);

	bool   GetBoolean		() { return (unsigned)get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Number          ) != 0; };
	double GetCelsius		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Celsius         );      };
	double GetDegrees		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Degrees         );      };
	double GetFeetPerSec	() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_FeetPerSecond	);      };
	double GetKm			() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Km              );      };
	double GetKmPerHour		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_KmPerHour		);      };
	double GetKnots			() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Knots           );      };
	double GetMeters		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Meters          );      };
	double GetMeterPerSec	() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_MeterPerSecond	);      };
	double GetNumber		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Number          );      };
	double GetPercent		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Percent         );      };
	double GetRadians		() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Radians			);      };
	double GetFahrenheit	() { return (double)  get_named_variable_typed_value( m_VarID, XMLDimUnits::m_Fahrenheit		);      };

	void SetBoolean			(bool     value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Number				); };
	void SetCelsius			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Celsius			); };
	void SetDegrees			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Degrees			); };
	void SetFeetPerSec		(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_FeetPerSecond		); };
	void SetKg				(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Kg					); };
	void SetKgPerSec		(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_KgPerSecond		); };
	void SetKm				(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Km					); };
	void SetKmPerHour		(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_KmPerHour			); };
	void SetMeterPerSec		(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_MeterPerSecond		); };
	void SetKnots			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_KmPerHour			); };
	void SetMeters			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Knots				); };
	void SetNumber			(int      value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Number				); };
	void SetNumber			(unsigned value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Number				); };
	void SetNumber			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Number				); };
	void SetPercent			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Percent			); };
	void SetRadians			(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Radians			); };
	void SetFahrenheit		(double   value) { set_named_variable_typed_value( m_VarID, (FLOAT64)value, XMLDimUnits::m_Fahrenheit			); };

protected:
	ID   m_VarID;
	bool m_bUnregisterAfterUse;
};

class SimVar
{
public:
	SimVar(GAUGE_TOKEN id);

	inline double GetN()	{ lookup_var(&m_Token); return m_Token.var_value.n;	}
	inline ENUM   GetE()	{ lookup_var(&m_Token); return m_Token.var_value.e;	}
	inline FLAGS  GetF()	{ lookup_var(&m_Token); return m_Token.var_value.f;	}
	inline VAR32  GetD()	{ lookup_var(&m_Token); return m_Token.var_value.d;	}
	inline BOOL   GetB()	{ lookup_var(&m_Token); return m_Token.var_value.b;	}
	inline VAR32  GetO()	{ lookup_var(&m_Token); return m_Token.var_value.o;	}
	inline PVOID  GetP()	{ lookup_var(&m_Token); return m_Token.var_value.p;	}

	bool   GetBoolean		() { return (unsigned)GetN() != 0; };
	double GetDegrees		() { return (double)  GetN();      };
	double GetFeet			() { return (double)  GetN();      };
	double GetFeetPerSec	() { return (double)  GetN();      };
	double GetKg			() { return (double)  GetN();      };
	double GetKgPerSec		() { return (double)  GetN();      };
	double GetKm			() { return (double)  GetN();      };
	double GetKmPerHour		() { return (double)  GetN();      };
	double GetKnots			() { return (double)  GetN();      };
	double GetMeters		() { return (double)  GetN();      };
	double GetMeterPerSec	() { return (double)  GetN();      };
	double GetNumber		() { return (double)  GetN();      };
	double GetRadians		() { return (double)  GetN();      };
	double GetPercent		() { return (double)  GetN();      };
	double GetCelsius		() { return (double)  GetN();      };
	double GetFahrenheit	() { return (double)  CELSIUS_TO_FAHRENHEIT(GetCelsius());      };

	double Get(ENUM e) { 
		if(e==XMLDimUnits::m_Boolean		) return GetBoolean();
		if(e==XMLDimUnits::m_Celsius		) return GetCelsius();		
		if(e==XMLDimUnits::m_Degrees		) return GetDegrees();		
		if(e==XMLDimUnits::m_Feet			) return GetFeet();			
		if(e==XMLDimUnits::m_FeetPerSecond	) return GetFeetPerSec();	
		if(e==XMLDimUnits::m_Kg			) return GetKg();			
		if(e==XMLDimUnits::m_KgPerSecond	) return GetKgPerSec();		
		if(e==XMLDimUnits::m_Km			) return GetKm();			
		if(e==XMLDimUnits::m_KmPerHour		) return GetKmPerHour();		
		if(e==XMLDimUnits::m_Knots			) return GetKnots();			
		if(e==XMLDimUnits::m_Meters		) return GetMeters();		
		if(e==XMLDimUnits::m_MeterPerSecond) return GetMeterPerSec();	
		if(e==XMLDimUnits::m_Number		) return GetNumber();		
		if(e==XMLDimUnits::m_Percent		) return GetPercent();		
		if(e==XMLDimUnits::m_Radians		) return GetRadians();		
		if(e==XMLDimUnits::m_Fahrenheit	) return GetFahrenheit();		
		return 0;
	};

protected:
	GAUGE_TOKEN m_VarID;
	MODULE_VAR	m_Token;
};

class SimVars
{
private:
	bool						m_StdTokensInited;
	std::auto_ptr<SimVar>		m_StdTokens[C_GAUGE_TOKEN];
	
public:
	SimVars() {
		m_StdTokensInited=false;
		InitVars();
	}

	void InitVars() {
		if(m_StdTokensInited)
			return;

		for(int i=MODULE_VAR_NONE+1;i<C_GAUGE_TOKEN;i++) {
			m_StdTokens[i]=std::auto_ptr<SimVar>(new SimVar((GAUGE_TOKEN)i));
		}

		m_StdTokensInited=true;
	}

	inline double GetC(GAUGE_TOKEN var,ENUM e=XMLDimUnits::m_Number)			{ return m_StdTokens[var]->Get(e);		}
	inline FLAGS  GetCF(GAUGE_TOKEN var)										{ return m_StdTokens[var]->GetF();		}
	inline PVOID  GetCP(GAUGE_TOKEN var)										{ return m_StdTokens[var]->GetP();		}
};

