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

extern ID32		gKeyPressed;
extern UINT32   gKeyData;
extern SimConnect* simConnect;

void PrintStr(String& str)
{
	//_cprintf_s(str.c_str());
	std::cout << str << std::endl;
}

#define REG_SND_FN(n) inline void snd##n(String& name)	\
{ \
	SoundEngine::SoundEngine* ptr=simConnect->soundEngine.get();	\
	if(ptr)	\
		ptr->n(name);		\
}

#define REG_SND_FN2(n,r,d) inline r snd##n(String& name)	\
{ \
	SoundEngine::SoundEngine* ptr=simConnect->soundEngine.get();	\
	if(ptr)	\
		return ptr->n(name); \
	return d; \
}

#define REG_SND_FN3(n,t,v) inline void snd##n(String& name,t v)	\
{ \
	SoundEngine::SoundEngine* ptr=simConnect->soundEngine.get();	\
	if(ptr)	\
		ptr->n(name,v); \
}

#define REG_SND_FN4(n) inline void snd##n()	\
{ \
	SoundEngine::SoundEngine* ptr=simConnect->soundEngine.get();	\
	if(ptr)	\
		ptr->n(); \
}

REG_SND_FN(Play)
REG_SND_FN(Stop)
REG_SND_FN(Mute)
REG_SND_FN(UnMute)
REG_SND_FN(Pause)
REG_SND_FN(UnPause)
REG_SND_FN(PlayIfNotPlaying)
REG_SND_FN2(IsPlaying,bool,0)
REG_SND_FN2(GetVolume,int,0)
REG_SND_FN3(SetVolume,int,v)
REG_SND_FN4(MuteAll)
REG_SND_FN4(UnMuteAll)
REG_SND_FN4(PauseAll)
REG_SND_FN4(UnPauseAll)
REG_SND_FN(StopIfPlaying)

inline double GetCToken(int& i)				
{ 
	return (double)simConnect->GetC((GAUGE_TOKEN)i);
}

inline double GetNamedVar(String& name)		
{ 
	return XMLNamedVar(name.c_str()).GetNumber(); 
}

inline void SetNamedVar(String& n,double& i)
{ 
	XMLNamedVar(n.c_str()).SetNumber(i); 
}

inline int GetNamedVarBoolReset(String& name)		
{ 
	int i=static_cast<int>(XMLNamedVar(name.c_str()).GetNumber());
	XMLNamedVar(name.c_str()).SetNumber(!i);
	return i;
}

inline int GetViewMode()                   
{ 
	return simConnect->activeViewMode;                  
}

inline void SetSimEvent(int& i,int& i2)     
{ 
	send_key_event(i,i2);
}

inline void	SaveVariable(String& nv,double& val)	
{ 
	simConnect->saveLoadEngine->SaveVar((Char *)nv.c_str(),val); 
}

inline double LoadVariable(String& nv)				
{ 
	return simConnect->saveLoadEngine->LoadVar((Char *)nv.c_str()); 
}

/*

//////////////////////////////////////////////////////////////////////////
// PID

inline void SetBankPID(double& p,double & i,double& d)
{
	APP.m_AutopilotEngine->bankProcess.SetPID(p,i,d);
}

inline void SetPitchPID(double& p,double & i,double& d)
{
	APP.m_AutopilotEngine->pitchProcess.SetPID(p,i,d);
}

inline void SetYawPID(double& p,double & i,double& d)
{
	APP.m_AutopilotEngine->yawProcess.SetPID(p,i,d);
}

inline void SetVerticalSpeedPID(double& p,double & i,double& d)
{
	APP.m_AutopilotEngine->verticalSpeedProcess.SetPID(p,i,d);
}

inline void SetAltholdPID(double& p,double & i,double& d)
{
	APP.m_AutopilotEngine->altholdProcess.SetPID(p,i,d);
}

//////////////////////////////////////////////////////////////////////////
// Power

inline void SetBankPower(int& i)
{
	APP.m_AutopilotEngine->bankProcess.Turn(static_cast<bool>(i));
}

inline void SetPitchPower(int& i)
{
	APP.m_AutopilotEngine->pitchProcess.Turn(static_cast<bool>(i));
}

inline void SetYawPower(int& i)
{
	APP.m_AutopilotEngine->yawProcess.Turn(static_cast<bool>(i));
}

inline void SetVerticalSpeedPower(int& i)
{
	APP.m_AutopilotEngine->verticalSpeedProcess.Turn(static_cast<bool>(i));
}

inline void SetAltholdPower(int& i)
{
	APP.m_AutopilotEngine->altholdProcess.Turn(static_cast<bool>(i));
}

//////////////////////////////////////////////////////////////////////////
// Control

inline void PitchPlane(double& in)
{
	APP.m_AutopilotEngine->pitchProcess.SetValue(in*-1);
}

inline void BankPlane(double& in)
{
	APP.m_AutopilotEngine->bankProcess.SetValue(in*-1);
}

inline void AltholdPlane(double& in,double& maxvs,double& minvs)
{
	APP.m_AutopilotEngine->altholdProcess.SetValue(in,maxvs,minvs);
}

//////////////////////////////////////////////////////////////////////////
// Limits

inline void SetPitchLimits(double& _pitchDifLimit,double& _pitchIntLimit,double& _elevatorValueLimit)
{
	APP.m_AutopilotEngine->pitchProcess.SetLimits(_pitchDifLimit,_pitchIntLimit,_elevatorValueLimit);
}

inline void SetBankLimits(double& _bankDifLimit,double& _bankIntLimit,double& _degreesLimit)
{
	APP.m_AutopilotEngine->bankProcess.SetLimits(_bankDifLimit,_bankIntLimit,_degreesLimit);
}

//////////////////////////////////////////////////////////////////////////
// Params

inline void SetPitchParams(double& _fixCoef1,double& _trimmStep)
{
	APP.m_AutopilotEngine->pitchProcess.SetParams(_fixCoef1,_trimmStep);
}

inline void SetBankParams(double& _fixCoef1,double& _fixCoef2)
{
	APP.m_AutopilotEngine->bankProcess.SetParams(_fixCoef1,_fixCoef2);
}

*/