#include "Event.h"
#include "UI.h"
#include "Generic_DS/Node.h"
#include "Generic_DS/PriorityQueue.h"
#include "Generic_DS/Queue.h"
#include "Rovers&Missions/Mission.h"
#include "Rovers&Missions/Rover.h"
#include <iostream>	
using namespace std;
Event::Event(char f, char t, int ed, int id, int tloc, int mdur, int sig)
{
	F = f;
	TYP = t;
	ED = ed;
	ID = id;
	TLOC = tloc;
	MDUR = mdur;
	SIG = sig;
}

int Event::GetID()
{
	return ID;
}
int Event::GetTLOC()
{
	return TLOC;
}
int Event::GetMDUR()
{
	return MDUR;
}
int Event::GetSIG()
{
	return SIG;
}
char Event::GetF()
{
	return F;
}
int Event::GetED()
{
	return ED;
}
char Event::GetTYP()
{
	return TYP;
}
void Event::Execute()
{
	//Mission* m = new Mission();
	//cout << ID;   it was for testing 

}
Event::~Event()
{
}