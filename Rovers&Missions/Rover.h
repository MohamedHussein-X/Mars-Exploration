
#pragma once
#include <iostream>
#include "Mission.h"
using namespace std;

class Rover
{
private:
	
	int ChUpD; // Check Up Duration 
	float Speed; // Speed Rover 
	int NofMissBChUp; //   Number of missions allowed  before checkup  


	int ID; //  Rover ID 
	char type; // Rover type
	int CuChupD; // Current day in the check up duraion
	bool IsChUp; // Check up status 
	bool IsAssig; // Assigment status 
	int NofMiss; // Number of missions done by the rover
	int CuD; // Current Day 
	//int MID; // Mission Assigned ID
	int NumMissDoneBCH; // Number of mission done before check up
	Mission *Mis;//Pointer to the assigned Mission 
	int missionID;

public:
	Rover(int i = 0, char t = 'x', int d = 0, float s = 0, bool Ch = false, bool Ass = false, int NM = 0, int Cd = 0, int M = 0, int NBCh = 0);
	Rover(int i, char t, int s,  int nM, int c);
	// Setteres 

	void SetRoverType(char c); 
	void SetRoverID(int id);
	void SetChUpD(int D);
	void SetRoverSpeed(float speed);
	void setcurrentday(int x);
	void setmissionID(int x);
	//void setNofMiss(int x);
	// Getters 

	int getNofMiss();
	int getIDRover();
	char getTypeRover();
	int getChUpD(); 
	float getSpeed();
	int getNumberofMissionsBeforeCheckUp();
	int getcurrentday();
	int getmissionID();
	Mission* getMiss();

	
	
	void IncCuD(); // Incremit  current day 
	void IncNofMiss(); // Incremint NoofMission 
	void IncNumMissDoneBCH(); // Incremit Missions for CheckUp
	void IncCuChupD(); //Incremint days in the check up duraion
	

	
	void AssignMiss(Mission*  mis); // Assigment Mission , With pointer 
	void Discharge(); // Discharge the rover and make it free 

	bool IsInCheckUp(); // CheckUp Status
	bool IsAssigned(); // Assigment Status
	~Rover();

};