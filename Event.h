#pragma once
#include "Generic_DS/Node.h"
#include "Generic_DS/PriorityQueue.h"
#include "Generic_DS/Queue.h"
#include "Rovers&Missions/Mission.h"
#include "Rovers&Missions/Rover.h"
class Event
{
private:
	char F, TYP;
	int ED, ID, TLOC, MDUR, SIG;
public:
	Event(char f, char t, int ed, int id, int tloc, int mdur, int sig);
	void Execute();
	char GetF();
	int GetED();
	int GetID();
	int GetTLOC();
	int GetMDUR();
	int GetSIG();
	char GetTYP();
	~Event();

	

};

