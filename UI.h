#pragma once
#include <windows.h>
#include <fstream>				
#include <iostream>	
#include "Event.h"
#include "Generic_DS/Queue.h"
using namespace std;

class UI
{
private:
	int MRoversNumber, PRoversNumber, ERoversNumber;
	int SM, SP, SE; // speed of rovers
	int N, CM, CP, CE;
	// N: is the number of missions the rover completes before performing a checkup
	// CM : is the checkup duration in days for mountainous rovers
	//CP : is the checkup duration in days for polar rovers
   // CE : is the checkup duration in days for emergency rovers
	int nEvents;
	Queue<Event*> Events;
public:
	UI();
	
	Queue<Event*> getEventList(); // should return the event list and would be called in mars station at the program setup
	
	
	int GetnEvents();
	int GetCE();
	int GetCM();
	int GetCP();
	int GetN();
	int GetSM();
	int GetSP();
	int GetSE();
	int GetPRoversNumber();
	int GetMRoversNumber();
	int GetERoversNumber();
	void OutputFile(Queue<Mission*> CompletedMis);
	void ClearScreen();
	void WaitForEnter();
	void WaitForSecond();
	void UpdateInterface(int d,
						int nPolarWaiting, Queue<Mission*>& q5, int nEmergencyWaiting, PriorityQueue<Mission*>& q6, int nMountainousWaiting, Queue<Mission*>& MountainousWaiting,
						int inExe, PriorityQueue<Rover*>& inExRover,
						int avalP, PriorityQueue<Rover*> &q1,  int avalE, PriorityQueue<Rover*> &q2, int avalM, PriorityQueue<Rover*>& Availabe_Mountainous,
						int incheckP, Queue<Rover*>& q3, int incheckE, Queue<Rover*>& q4, int incheckM, Queue<Rover*>& InCheckup_Mountainous,
						int nCompleted, Queue<Mission*>& Completed);
	int getMode();

	void LoadFile();
	~UI();
};



