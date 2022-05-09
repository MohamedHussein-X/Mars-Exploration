#pragma once
class Mission
{
private:
	char Type; // Mission TYpe (Polar (P) - Emergency (E)
	int ID; // Mission ID
	int FD, WDS, EDS, CD,  Sig;
	float TL, TimeToTL;
	int  ED, TLOC, MDUR;   
	int excuted;
	int roverID; // THE ID of the rover that is assigned to the mission
	// ED: the event day
	//TLOC is the mission’s target location(in kilometers from the base station).
	// MDUR is the number of days needed to fulfill the mission requirements at target location.

	//FD : Formulation Day for the mission
	//WDs : Waition Days befor assigment to rover taaaaaaaaaaaaaaaaaaahhhhhhhhhhhhhhhhhhhhhhaaaaaaaaaaaaaaaa
	//EDS : In-Excution days for the mission 
	//CD : The completion dat ( Day the mission fnished )
	//TL : Target location for the mission 
	//TimeToTL : Time needed to reach  target location and back 
	// Sig : Significance for the mission  
	bool IsAssigned; // Check Assigment Status
public:
	Mission(); // Constructor 
	Mission(char type , int eventDay , int ID, int tloc, int mdur , int sig );
	// Setters and Getters for data member 
	//--------------------------------------------------
	void SetType(char c);
	void SetID(int id);
	void setexcuted(int excuteday);
	void SetFD(int fd);
	void incWDS(); 
	void incEDS();
	void SetCD(int cd);
	void SetTL(float tl);
	void SetSig(int sig);
	void SetTimeToTL(float t);
	void Assign(bool b);
	void setroverID(int x);
	


	char GetType();
	int GetTLOC();
	int GetID();
	int GetFD();
	int GetWDS();
	int GetEDS();
	int GetCD();
	float GetTL();
	float GetTimeToTL();
	int getroverID();
	int GetSig();
	bool isAssigned();
	int GetMDUR();
	//--------------------------------------------------------


	//--------------------------------------------------------

	
	int GetTheEnDayswithTimetoTL(); // This return the whole in-Excution days including the in-Excution days pn the target and time to reach and back

	float getPriority();

	void InWDS(); // Incremint WDS
	
	void CalCD(); // Calculating CD;
};