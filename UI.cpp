#include "UI.h"
#include <windows.h>
#include <fstream>				
#include <iostream>	
using namespace std;


Queue<Event*> UI::getEventList()
{
	return Events;
}

UI::UI()
{
	MRoversNumber = 0;
	PRoversNumber = 0;
	ERoversNumber = 0;
	SM = 0;
	SP = 0;
	SE = 0;
	N = 0;
	CM = 0;
	CP = 0;
	CE = 0;
	nEvents = 0;
}
void UI::WaitForSecond()
{
	Sleep(1000);
}
int UI::GetMRoversNumber()
{
	return MRoversNumber;

}
int UI::GetPRoversNumber()
{
	return PRoversNumber;
}
int UI::GetERoversNumber()
{
	return ERoversNumber;
}
int UI::GetSM()
{
	return SM;
}
int UI::GetSP()
{
	return SP;
}
int UI::GetSE()
{
	return SE;
}
int UI::GetN()
{
	return N;
}
int UI::GetCM()
{
	return CM;
}
int UI::GetCP()
{
	return CP;
}
int UI::GetCE()
{
	return CE;
}
int UI::GetnEvents()
{
	return nEvents;
}
void UI::ClearScreen()
{
	//cout << "Flushing the output stream." << flush;
   
}
void UI::WaitForEnter()
{
	cout << endl;

	cout << "Press Enter to Continue" << endl;
	char temp = 'x';
	do
	{
		cin.get(temp);
	} while (temp != '\n');
	

}
int UI::getMode()
{
	cout << "Please Choose Game Mode:" << endl;
	cout << "1.Interactive" << endl;
	cout << "2.Step-by-step" << endl;
	cout << "3.Silent" << endl;
	int mode;
	cin >> mode;
	while (!(mode == 3 || mode == 1 || mode == 2))
	{
		ClearScreen();
		cout << "Please Choose a valid Game Mode:" << endl;
		cout << "1.Interactive" << endl;
		cout << "2.Step-by-step" << endl;
		cout << "3.Silent" << endl;
		cin >> mode;
	}
	if (mode == 3)
	{
		ClearScreen();
		cout << "Silent Mode" << endl;
		cout << "Simulation Starts..." << endl;   // should break them into 3 functions to correct the timing( if u wish)
		cout << "Simulatin Ends, Output file created" << endl;
		return mode;
	}
	else
	{
		ClearScreen();
		return mode;
	}
}

void UI::UpdateInterface(int d,
						int nPolarWaiting, Queue<Mission*>& q5, int nEmergencyWaiting, PriorityQueue<Mission*>& q6, int nMountainousWaiting, Queue<Mission*>& MountainousWaiting,
						int inExe, PriorityQueue<Rover*>& inExRover,
						int avalP, PriorityQueue<Rover*>& q1, int avalE, PriorityQueue<Rover*>& q2, int avalM, PriorityQueue<Rover*>& Availabe_Mountainous,
						int incheckP, Queue<Rover*>& q3, int incheckE, Queue<Rover*>& q4, int incheckM, Queue<Rover*>& InCheckup_Mountainous,
						int nCompleted, Queue<Mission*>& Completed)
{
	cout << "CurrentDay: " << d << endl;
	Rover* e;
	Mission* m;
	int a;
	float p;
	char t;
	Queue<Mission*> tempPM;
	Queue<Mission*> tempMM;
	PriorityQueue<Mission*> tempEM;
	Queue<Rover*> temp;
	PriorityQueue<Rover*> tempPriorityRover;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout << nPolarWaiting + nEmergencyWaiting + nMountainousWaiting << " Waiting Missions: ";

	if (nEmergencyWaiting!=0)
	{
		cout << "[";
		while (!q6.isEmpty())
		{
			q6.dequeue(m);
			tempEM.enqueue(m,m->getPriority());
			a = m->GetID();
			cout << a << ",";
		}
		while (!tempEM.isEmpty())
		{
			tempEM.dequeue(m);
			q6.enqueue(m, m->getPriority());
		}
		cout << '\b';
		cout << "]" ;

	}
	if (nPolarWaiting != 0)
	{
		cout << "(";
		while (!q5.isEmpty())
		{
			q5.dequeue(m);
			tempPM.enqueue(m);
			a = m->GetID();
			cout << a << ",";
		}
		while (!tempPM.isEmpty())
		{
			tempPM.dequeue(m);
			q5.enqueue(m);
		}
		cout << '\b';
		cout << ")";
	}
	if (nMountainousWaiting != 0)
	{
		cout << "{";
		while (!MountainousWaiting.isEmpty())
		{
			MountainousWaiting.dequeue(m);
			tempMM.enqueue(m);
			a = m->GetID();
			cout << a << ",";
		}
		while (!tempMM.isEmpty())
		{
			tempMM.dequeue(m);
			MountainousWaiting.enqueue(m);
		}
		cout << '\b';
		cout << "}";
	}
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	int c1 = 0;
	int c2 = 0;
	int c5 = 0;
	cout << inExe << " In-Exexution Missions/Rovers: ";
	if (inExe != 0)
	{
		cout << "[";
		while (!inExRover.isEmpty())
		{
			inExRover.dequeue(e);
			tempPriorityRover.enqueue(e, e->getMiss()->GetTheEnDayswithTimetoTL());
			t = e->getMiss()->GetType();
			if (t == 'E')
			{
				cout << e->getMiss()->GetID() << "/" << e->getIDRover()<<",";
				// check evry type individaully
				c1++;
			}
		}
		cout << '\b';
		cout << "]";
		if (c1 == 0)
		{
			cout << '\b';
			cout << '\b';
		}
		if (c1!=inExe)
		cout << "(";
		while (!tempPriorityRover.isEmpty())
		{
			tempPriorityRover.dequeue(e);
			inExRover.enqueue(e, e->getMiss()->GetTheEnDayswithTimetoTL());
			t = e->getMiss()->GetType();
			if (t == 'P')
			{
				cout << e->getMiss()->GetID() << "/" << e->getIDRover() << ",";
				// check evry type individaully
				c2++;
			}
		}
		cout << '\b';
		//cout << '\b';
		if (c1 == inExe)
		{
			//cout << '\b';
		}
		else
		{
		//	cout << '\b';
			cout << ")";
		}

		////////////////////// 
		if (c1 + c2 != inExe)
		{
			cout << "{";
			while (!inExRover.isEmpty())
			{
				inExRover.dequeue(e);
				tempPriorityRover.enqueue(e, e->getMiss()->GetTheEnDayswithTimetoTL());
				t = e->getMiss()->GetType();
				if (t == 'M')
				{
					cout << e->getMiss()->GetID() << "/" << e->getIDRover() << ",";
					// check evry type individaully
					c5++;
				}
			}
			cout << '\b';
		
			cout << "}";
			
		}
		while (!tempPriorityRover.isEmpty())
		{
			tempPriorityRover.dequeue(e);
			inExRover.enqueue(e, e->getMiss()->GetTheEnDayswithTimetoTL());
		}
		// get its type to identify the brackets
	}


	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout <<  avalE + avalP + avalM << " Available Rovers: ";
	if (avalP != 0) 
	{
		
		cout << "[";
		while (!q1.isEmpty())
		{
			q1.dequeue(e);
			temp.enqueue(e);
			a = e->getIDRover();
			cout << a << ",";
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(e);
			q1.enqueue(e, e->getSpeed());
		}
		cout << '\b';
		cout << "]";
	}
	if (avalE != 0)
	{
		cout << "(";
		while (!q2.isEmpty())
		{
			q2.dequeue(e);
			temp.enqueue(e);
			a = e->getIDRover();
			cout << a << ",";
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(e);
			q2.enqueue(e,e->getSpeed());
		}
		cout << '\b';
		cout << ")";
	}
	if (avalM != 0)
	{
		cout << "{";
		while (!Availabe_Mountainous.isEmpty())
		{
			Availabe_Mountainous.dequeue(e);
			temp.enqueue(e);
			a = e->getIDRover();
			cout << a << ",";
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(e);
			Availabe_Mountainous.enqueue(e, e->getSpeed());
		}
		cout << '\b';
		cout << "}";
	}

	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------";
	cout << endl;
	cout << incheckP + incheckE + incheckM << " In-Checkup Rovers:";/////////////////// لسه مش مظبوطة

	if ( incheckE != 0)
	{
		cout << "[";
		while (!q3.isEmpty())
		{
			q3.dequeue(e);
			temp.enqueue(e);
			a = e->getIDRover();
			cout << a << ",";
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(e);
			q3.enqueue(e);
		}
		cout << '\b';
		cout << "]";
	}
	if (incheckP != 0)
	{
		cout << "(";
		while (!q4.isEmpty())
		{
			q4.dequeue(e);
			temp.enqueue(e);
			a = e->getIDRover();
			cout << a << ",";
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(e);
			q4.enqueue(e);
		}
		cout << '\b';
		cout << ")" ;
	}
	if (incheckM != 0)
	{
		cout << "{";
		while (!InCheckup_Mountainous.isEmpty())
		{
			InCheckup_Mountainous.dequeue(e);
			temp.enqueue(e);
			a = e->getIDRover();
			cout << a << ",";
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(e);
			InCheckup_Mountainous.enqueue(e);
		}
		cout << '\b';
		cout << "}";
	}
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout << nCompleted << " Completed Missions:";
	int c3 = 0;
	int c4 = 0;
	int c6 = 0;
	while (!Completed.isEmpty())
	{
		Completed.dequeue(m);
		tempPM.enqueue(m);
		t = m->GetType();
		if (t == 'E')
		{
			cout << "[";
			cout << m->GetID(); // << ",";
			c3++;
			//cout << '\b';
			cout << "]" << " ";
		}
		else if (t == 'M')
		{
			//cout << '\b';
			cout << "{";
			cout << m->GetID(); // << ",";
			c6++;
			//cout << '\b';
			cout << "}" << " ";
		}
		else if (t == 'P')
		{
			//cout << '\b';
			cout << "(";
			cout << m->GetID(); // << ",";
			c4++;
			//cout << '\b';
			cout << ")" << " ";
		}
		/*
		cout << "[";
		while (!Completed.isEmpty())
		{
			Completed.dequeue(m);
			tempPM.enqueue(m);
			t = m->GetType();
			if (t == 'E')
			{
				cout << m->GetID()<<",";
				//cout << m->GetEDS() << " tatatat";
				c3++;
			}
		}
		cout << '\b';
		cout << "]";
		if (c3 == 0)
		{
			cout << '\b';
			cout << ' ';
		//	cout << '\b';
		}
		cout << "(";
		while (!tempPM.isEmpty())
		{
			tempPM.dequeue(m);
			Completed.enqueue(m);
			t = m->GetType();
			if (t == 'P')
			{
				cout << m->GetID() << ",";
				c4++;
			}
		}
		cout << '\b';
		cout << ")";
		if (c4 == 0)
		{
			cout << '\b';
			cout << ' ';
			//cout << '\b';
			
		}
		cout << "{";
		while (!Completed.isEmpty())
		{
			Completed.dequeue(m);
			tempPM.enqueue(m);
			t = m->GetType();
			if (t == 'M')
			{
				cout << m->GetID() << ",";
				//cout << m->GetEDS() << " tatatat";
				c6++;
			}
		}
		cout << '\b';
		cout << "}";
		if (c6 == 0)
		{
			cout << '\b';
			cout << ' ';
			//	cout << '\b';
		}*/
	}
	while (!tempPM.isEmpty())
	{
		tempPM.dequeue(m);
		Completed.enqueue(m);
	}
	cout << endl;
}

void UI::OutputFile(Queue<Mission*> CompletedMis)
{
	int CompMisNum = 0;
	int RolerNum = 0;
	int PMis = 0, MMis = 0, EMis = 0;

	float Avg_Wait = 0.0;
	float Avg_Exec = 0.0;

	ofstream Output("OutputFile");
	Output.clear();
	Output << "CD ID FD WD ED" << endl;
	Mission* TempMis;
	while (CompletedMis.dequeue(TempMis))
	{
		CompMisNum++;
		if (TempMis->GetType() == 'E')
			EMis++;
		else if (TempMis->GetType() == 'P')
			PMis++;
		else if (TempMis->GetType() == 'M')
			MMis++;
		Avg_Exec += TempMis->GetEDS();
		Avg_Wait += TempMis->GetWDS();
		Output << TempMis->GetCD() << " " << TempMis->GetID() << " " << TempMis->GetFD() << " " << TempMis->GetWDS() << " " << TempMis->GetEDS() << endl;
	}
	Avg_Wait /= CompMisNum;
	Avg_Exec /= CompMisNum;


	Output << ".................................................." << endl;

	Output << ".................................................." << endl;
	Output << "Missions: " << CompMisNum << "    [E: " << EMis << ", P:" << PMis << ", M:" << MMis << "]" << endl;
	Output << "Rovers: " << ERoversNumber + PRoversNumber + MRoversNumber << "    [E: " << ERoversNumber << ", P:" << PRoversNumber << ", M:" << MRoversNumber << "]" << endl;
	Output << "Avg Wait = " << Avg_Wait << "%" << ", Avg Exec =" << Avg_Exec << "%" << endl;
	Output.close();
	/*
	int CompMisNum = 0;
	int RolerNum = 0;
	int PMis = 0, MMis = 0, EMis = 0;

	float Avg_Wait = 0.0;
	float Avg_Exec = 0.0;

	ofstream Output("OutputFile");
	Output.clear();
	Output << "CD ID FD WD ED" << endl;
	Mission* TempMis;
	while (CompletedMis.dequeue(TempMis))
	{
		TempMis->CalCD();
		CompMisNum++;
		if (TempMis->GetType() == 'E')
			EMis++;
		else if (TempMis->GetType() == 'P')
			PMis++;
		else if (TempMis->GetType() == 'M')
			MMis++;
		Avg_Exec += TempMis->GetEDS();
		Avg_Wait += TempMis->GetWDS();
		Output << TempMis->GetCD() << " " << TempMis->GetID() << " " << TempMis->GetFD() << " " << TempMis->GetWDS() << " " << TempMis->GetEDS() << endl;
	}
	Avg_Wait /= CompMisNum;
	Avg_Exec /= CompMisNum;
	Output << "Missions: " << CompMisNum << " [E: " << EMis << ", P:" << PMis << ", M:" << MMis << "]" << endl;
	Output << "Rovers: " << ERoversNumber + PRoversNumber + MRoversNumber << " [E: " << ERoversNumber << ", P:" << PRoversNumber << ", M:" << MRoversNumber << "]" << endl;
	Output << "Avg Wait = " << Avg_Wait << ", Avg Exec =" << Avg_Exec << endl;
	Output.close();
	*/
}

void UI::LoadFile()
{
	cout << "Please Enter File Name:";
	string fileName;
	cin >> fileName;
	ifstream InFile;
	InFile.open(fileName, ios::in);
	while (!(InFile.is_open()))
	{
		cout << "Can't Load the file, Enter File Name:";
		cin >> fileName;
		InFile.open(fileName, ios::in);
	}

	InFile >> MRoversNumber >> PRoversNumber >> ERoversNumber;
	InFile >> SM >> SP >> SE;
	InFile >> N >> CM >> CP >> CE;
	InFile >> nEvents;
	char f, typ;
	int ed, id, tloc, mdur, sig;
	for (int i = 0; i < nEvents; i++)
	{
		InFile >> f >> typ >> ed >> id >> tloc >> mdur >> sig;
		if (f == 'F')
		{
			Event* e = new Event(f, typ, ed, id, tloc, mdur, sig);
			Events.enqueue(e);
		}
	}
}
UI::~UI()
{

}