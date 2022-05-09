#include "Mission.h"
#include<cmath>

Mission::Mission()
{
	ED=0,FD = 0, WDS = 0, EDS = 0, CD = 0, TL = 0, TimeToTL = 0, Sig = 0, ID = 0, Type = 'X', IsAssigned = 0;
	MDUR = 0;
	TLOC = 0;
	excuted = 0;

}
Mission::Mission(char type, int eventDay, int id, int tloc, int mdur, int sig)
{
	Type = type;
	ED = eventDay;
	ID = id;
	TLOC = tloc;
	MDUR = mdur;
	Sig = sig;
	excuted = 0;
	FD = 0, WDS = 0, EDS = 0, CD = 0, TL = 0, TimeToTL = 0, IsAssigned = 0;
}

void Mission::SetType(char c)
{
	Type = c;
}

void Mission::setroverID(int x)
{
	roverID = x;
}

void Mission::SetID(int id)
{
	ID = id;
}

void Mission::setexcuted(int excuteday)
{
	excuted = excuteday;
}

void Mission::SetFD(int fd)
{
	FD = fd;
}

void Mission::incWDS()
{
	WDS++;
}

void Mission::incEDS()
{
	EDS++;
}



void Mission::SetCD(int cd)
{
	CD = cd;
}

void Mission::SetTL(float tl)
{
	TL = tl;
}


void Mission::SetSig(int sig)
{
	Sig = sig;
}

void Mission::SetTimeToTL(float t)
{
	TimeToTL = t;
}

char Mission::GetType()
{
	return Type;
}

int  Mission::getroverID()
{
	return roverID;
}

int Mission::GetID()
{
	return ID;
}

int Mission::GetFD()
{
	return ED;
}

int Mission::GetWDS()
{
	return WDS;
}

int Mission::GetEDS()
{
	return EDS;
}

int Mission::GetCD()
{
	return CD;
}

float Mission::GetTL()
{
	return TL;
}

float Mission::GetTimeToTL()
{
	return TimeToTL;
}

int Mission::GetSig()
{
	return Sig;
}

int Mission::GetMDUR()
{
	return MDUR;
}

bool Mission::isAssigned()
{
	return IsAssigned;
}


void Mission::Assign(bool b)
{
	IsAssigned =b;
}

int Mission::GetTheEnDayswithTimetoTL()
{
	int x= excuted + MDUR + TimeToTL;
	return (-(x));
	//return 0;
}

void Mission::InWDS()
{
	WDS++;
}

int Mission::GetTLOC()
{
	return TLOC;
}

float Mission::getPriority()
{
	return -(ED+1/(Sig*(ED+1/MDUR+TLOC)));
}

void Mission::CalCD()
{
	CD = ED + WDS + EDS;
}
