#pragma once
#include "UI.h"
#include "Generic_DS/Node.h"
#include "Generic_DS/PriorityQueue.h"
#include "Generic_DS/Queue.h"
#include "Rovers&Missions/Mission.h"
#include "Rovers&Missions/Rover.h"
class MarsStation
{
private:
	int Currentday;
	int MRoversNumber, PRoversNumber, ERoversNumber;
	int SM, SP, SE; // speed of rovers
	int N, CM, CP, CE;
	
	// N: is the number of missions the rover completes before performing a checkup
	// CM : is the checkup duration in days for mountainous rovers
	//CP : is the checkup duration in days for polar rovers
   // CE : is the checkup duration in days for emergency rovers

	//counts section 

	int nEvents;    // events
	int avail_EM_Rover; //polars
	int avail_Po_Rover;
	int avail_MO_Rover;
	int P_inCHekUp;
	int E_inCHekUp;
	int M_inCHekUp;
	int inExecution_Rovers;
	
	int nowaiting_Emergency;  // missions	
	int nowaiting_Polar; 
	int nowaiting_Mountainous;
	int nCompleted;

	UI* ui;

	Queue<Event*> EventList;
	PriorityQueue<Rover*> Availabe_Emergency;
	PriorityQueue<Rover*> Availabe_Polar;
	PriorityQueue<Rover*> Availabe_Mountainous;
	
	PriorityQueue<Rover*> In_Execution_Rover; 
	//PriorityQueue<Mission*> Inexecution_missions;// no need for it
	Queue<Rover*> InCheckup_Emergency;
	Queue<Rover*> InCheckup_Polar;
	Queue<Rover*> InCheckup_Mountainous;
	PriorityQueue<Mission*> waiting_Emergency;
	Queue<Mission*> waiting_Polar;
	Queue<Mission*> waiting_Mountainous;
	Queue<Mission*> Completed_Missions;

public: 
void Interactive();
void AddToList();
void StepByStep();
void Silent();
void incrementEDS();
void calculateCD();
void incrementWDS();
void moveFromEventToWaiting();
void AssignWaitingMission();
void checkcompletedmissions();

//void checkuprover();
void InccuChUpDuration();
MarsStation();
void Simulate();
~MarsStation();
};

