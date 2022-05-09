//Rover.cpp

#include "Rover.h"

Rover::Rover(int i, char t, int d, float s, bool Ch, bool Ass, int NM, int Cd, int M, int NBCh)
{
	ID = i;
	type = t;
	ChUpD = d;
	Speed = s;
	IsChUp = Ch;
	IsAssig = Ass;
	NofMiss = NM; 
	CuD = Cd;
	Mis = NULL;
	NofMissBChUp = NBCh;
	NumMissDoneBCH = 0;
	CuChupD=0;
	missionID = 0;
}
Rover::Rover(int i, char t,int s, int nM, int c)
{
	ID = i;
	type = t;
	Speed = s;
	NofMissBChUp = nM;
	ChUpD = c;
	missionID = 0;
	IsChUp = false;
	IsAssig = false;
	CuD = 0;
	Mis = NULL;
	NofMiss = 0;
	NumMissDoneBCH = 0;
	CuChupD = 0;
}
void Rover::SetRoverType(char c)
{
	type = c;
}


Mission* Rover::getMiss()
{
	return Mis;
}


int Rover::getmissionID()
{
	return missionID;
}

void Rover::setmissionID(int x)
{
	IsAssig = 1;
	missionID = x;
}

void Rover::SetRoverID(int id)
{
	ID = id;
}

void Rover::SetChUpD(int D)
{
	NofMissBChUp = D;
}

/*
void Rover::setNofMiss(int x)
{
	NofMiss = x;
}
*/
void Rover::SetRoverSpeed(float speed)
{
	Speed = speed;
}

int Rover::getIDRover()
{
	return ID;
}

char Rover::getTypeRover()
{
	return type;
}

int Rover::getNofMiss()
{
	return NofMiss;
}

int Rover::getChUpD()
{
	return ChUpD;
}

float Rover::getSpeed()
{
	return Speed;
}

bool Rover::IsInCheckUp()
{
	return IsChUp;
}

bool Rover::IsAssigned()
{
	if (Mis != NULL)
		return 1;
	return 0;
}

int Rover::getNumberofMissionsBeforeCheckUp()
{
	return NofMissBChUp;
}

int Rover::getcurrentday()
{
	return CuD;
}

void Rover::setcurrentday(int x)
{
	CuD = x;
}

void Rover::AssignMiss(Mission* mis)
{
	Mis = mis;
	IsAssig = 1;
	Mis->SetTimeToTL(2* Mis->GetTLOC() / getSpeed() / 25);
	Mis->Assign(1);
	IncNumMissDoneBCH();
	IncNofMiss();
}

void Rover::Discharge()
{
	Mis = nullptr;
	IsAssig = 0;
}

void Rover::IncNofMiss()
{
	NofMiss++;
}

void Rover::IncNumMissDoneBCH()
{
	if (NumMissDoneBCH != NofMissBChUp - 1 && IsChUp == 0)
		NumMissDoneBCH++;
	else
	{
		NumMissDoneBCH = 0;
		IsChUp = 1;
	}
}

void Rover::IncCuD()
{
	CuD++;
}

void Rover::IncCuChupD()
{
	if (IsChUp == 1 && CuChupD < ChUpD)
		CuChupD++;
	else if (CuChupD == ChUpD)
	{
		IsChUp = 0;
		CuChupD = 0;
	}
    
}

Rover::~Rover()
{

}