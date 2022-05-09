#include "MarsStation.h"

MarsStation::MarsStation()
{
	Currentday = 0;
	ui = NULL;
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
	nEvents=0;
	avail_EM_Rover=0;
	avail_Po_Rover=0;
	avail_MO_Rover=0;
	P_inCHekUp=0;
	E_inCHekUp=0;
	M_inCHekUp = 0;
	nEvents = 0;
	nowaiting_Emergency = 0;
	nowaiting_Mountainous = 0;
	nowaiting_Polar = 0;
	inExecution_Rovers = 0;
	nCompleted = 0;
}

void MarsStation::Simulate()
{
	ui = new UI();
	ui->LoadFile();
	int Mode = ui->getMode();
	//cout << ERoversNumber << "dffdsfdsf" << endl;
	
		if (Mode == 1)
			Interactive();
		else if (Mode == 2)
			StepByStep();
		else if (Mode == 3)
			Silent();
	
	return;

}
void MarsStation::Interactive()
{
	AddToList();
	Currentday = 1;
	while (nCompleted != nEvents )  //// would be while not all the missions are done
	{
		//dequeueEvent(Currentday);


		// move rovers and missions 
		
		checkcompletedmissions();
		InccuChUpDuration();
		moveFromEventToWaiting();
		AssignWaitingMission();
		incrementEDS();
		incrementWDS();
		
		// update interface
		ui->WaitForEnter();
		ui->UpdateInterface(Currentday,
			nowaiting_Polar, waiting_Polar, nowaiting_Emergency, waiting_Emergency, nowaiting_Mountainous, waiting_Mountainous,
			inExecution_Rovers, In_Execution_Rover,
			avail_EM_Rover, Availabe_Emergency, avail_Po_Rover, Availabe_Polar, avail_MO_Rover, Availabe_Mountainous,
			P_inCHekUp, InCheckup_Emergency , E_inCHekUp, InCheckup_Polar, M_inCHekUp, InCheckup_Mountainous,
			nCompleted, Completed_Missions);
		Currentday++;
		
		
	}
	calculateCD();
	ui->OutputFile(Completed_Missions);
}
void MarsStation::AddToList()
{
	nEvents = ui->GetnEvents();
	EventList = ui->getEventList();
	CE = ui->GetCE();
	CM = ui->GetCM();
	CP = ui->GetCP();
	N = ui->GetN();
	SM = ui->GetSM();
	SP = ui->GetSP();
	SE = ui->GetSE();
	PRoversNumber = ui->GetPRoversNumber();
	MRoversNumber = ui->GetMRoversNumber();
	ERoversNumber = ui->GetERoversNumber();

	// fill  the available polar rovers

	for (int i = 1; i <= PRoversNumber; i++)
	{
		Rover* r = new Rover(i, 'P', SP, N, CP);
		Availabe_Polar.enqueue(r, SP);
		avail_Po_Rover++;
	}
	
	// fill  the available emerncy rovers

	for (int i = PRoversNumber + 1; i <= ERoversNumber + PRoversNumber; i++)
	{
		Rover* r = new Rover(i, 'E', SE, N, CE);
		Availabe_Emergency.enqueue(r,SE);
		avail_EM_Rover++;
	}
	for (int i = ERoversNumber + PRoversNumber + 1; i <= MRoversNumber + ERoversNumber + PRoversNumber; i++)
	{
		Rover* r = new Rover(i, 'M', SM, N, CM);
		Availabe_Mountainous.enqueue(r, SM);
		avail_MO_Rover++;
	}

}

void MarsStation::calculateCD()
{
	Mission* tempmission;
	Queue<Mission*> tempCompleted_Missions;
	while (!Completed_Missions.isEmpty())
	{
		Completed_Missions.dequeue(tempmission);
		tempmission->CalCD();
		tempCompleted_Missions.enqueue(tempmission);

	}
	while (!tempCompleted_Missions.isEmpty())
	{
		tempCompleted_Missions.dequeue(tempmission);
		
		Completed_Missions.enqueue(tempmission);

	}
}

void MarsStation::moveFromEventToWaiting()
{
	if (!EventList.isEmpty())
	{
		Event* temp;
		EventList.peekFront(temp);

		while (!EventList.isEmpty() && (temp->GetED() == Currentday))
		{
			EventList.dequeue(temp);
			char F = temp->GetF();
			char TYP = temp->GetTYP();
			int ED = temp->GetED();
			int	ID = temp->GetID();
			int TLOC = temp->GetTLOC();
			int MDUR = temp->GetMDUR();
			int SIG = temp->GetSIG();
			float p;
			if (TYP== 'E')
			{

				Mission* tempmission = new Mission(TYP, ED, ID, TLOC, MDUR, SIG);
				 p = tempmission->getPriority();
				waiting_Emergency.enqueue(tempmission, tempmission->getPriority());
				nowaiting_Emergency++;
			}
			if (TYP == 'M')
			{

				Mission* tempmission = new Mission(TYP, ED, ID, TLOC, MDUR, SIG);
				
				waiting_Mountainous.enqueue(tempmission);
				nowaiting_Mountainous++;
			}
			if (TYP == 'P')
			{

				Mission* tempmission = new Mission(TYP, ED, ID, TLOC, MDUR, SIG);
				waiting_Polar.enqueue(tempmission);
				nowaiting_Polar++;
			}
			EventList.peekFront(temp);
		}
	}
}


void MarsStation::AssignWaitingMission()
{
	if (Availabe_Emergency.isEmpty() && Availabe_Polar.isEmpty() && Availabe_Mountainous.isEmpty())
	{
		return;
	}
	else
	{
		// Emergency Assignment
		for (int i = 0; (i < nowaiting_Emergency )&&(!Availabe_Emergency.isEmpty() || !Availabe_Polar.isEmpty() || !Availabe_Mountainous.isEmpty()); i++)
		{
			Mission* tempmission;
			Rover* temprover;
			//float p;
			waiting_Emergency.peek(tempmission);
			if (!Availabe_Emergency.isEmpty())
			{
				waiting_Emergency.dequeue(tempmission);
				Availabe_Emergency.dequeue(temprover);
				//temprover->IncNofMiss();
				//temprover->IncNumMissDoneBCH();
				tempmission->setroverID(temprover->getIDRover());
				temprover->AssignMiss(tempmission);
				temprover->setmissionID(tempmission->GetID());
				tempmission-> setexcuted (Currentday);
			    In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());    // should get another vlaue to determine the prio for rovers
				avail_EM_Rover--;
				nowaiting_Emergency--;
				inExecution_Rovers++;
			}
			
			else if (!Availabe_Mountainous.isEmpty())
			{
				waiting_Emergency.dequeue(tempmission);
				Availabe_Mountainous.dequeue(temprover);
				//temprover->IncNofMiss();
				//temprover->IncNumMissDoneBCH();
				tempmission->setroverID(temprover->getIDRover());
				temprover->AssignMiss(tempmission);
				temprover->setmissionID(tempmission->GetID());
				tempmission->setexcuted(Currentday);
				In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());    // should get another vlaue to determine the prio for rovers
				avail_MO_Rover--;
				nowaiting_Emergency--;
				inExecution_Rovers++;
			}
			
			else if (!Availabe_Polar.isEmpty())
			{
				waiting_Emergency.dequeue(tempmission);
				Availabe_Polar.dequeue(temprover);
				//temprover->IncNofMiss();
				//temprover->IncNumMissDoneBCH();
				tempmission->setroverID(temprover->getIDRover());
				temprover->AssignMiss(tempmission);
				temprover->setmissionID(tempmission->GetID());
				tempmission->setexcuted(Currentday);
				In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());    // should get another vlaue to determine the prio for rovers
				avail_Po_Rover--;
				nowaiting_Emergency--;
				inExecution_Rovers++;
			}

		}

		// Polar Assignment
		for (int i = 0; i < nowaiting_Polar && !Availabe_Polar.isEmpty(); i++)
		{
			Mission* tempmission;
			Rover* temprover;
			//float p=0;
			waiting_Polar.dequeue(tempmission);
			Availabe_Polar.dequeue(temprover);
			//temprover->IncNofMiss();
			//temprover->IncNumMissDoneBCH();
			tempmission->setroverID(temprover->getIDRover());
			temprover->AssignMiss(tempmission);
			temprover->setmissionID(tempmission->GetID());
			tempmission->setexcuted(Currentday);
			In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());   // should get another vlaue to determine the prio for rovers
			avail_Po_Rover--;
			nowaiting_Polar--;
			inExecution_Rovers++;
			//Inexecution_missions.enqueueSort(tempmission);
		}

		// Mountainous Assignment 
		for (int i = 0; i < nowaiting_Mountainous && (!Availabe_Mountainous.isEmpty() || !Availabe_Emergency.isEmpty()); i++)
		{
			Mission* tempmission;
			Rover* temprover;
			//float p=0;
			if (!Availabe_Mountainous.isEmpty())
			{
				waiting_Mountainous.dequeue(tempmission);
				Availabe_Mountainous.dequeue(temprover);
				//temprover->IncNofMiss();
				//temprover->IncNumMissDoneBCH();
				tempmission->setroverID(temprover->getIDRover());
				temprover->AssignMiss(tempmission);
				temprover->setmissionID(tempmission->GetID());
				tempmission->setexcuted(Currentday);
				In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());   // should get another vlaue to determine the prio for rovers
				avail_MO_Rover--;
				nowaiting_Mountainous--;
				inExecution_Rovers++;
			}
			//Inexecution_missions.enqueueSort(tempmission);

			else if (!Availabe_Emergency.isEmpty())
			{
				waiting_Mountainous.dequeue(tempmission);
				Availabe_Emergency.dequeue(temprover);
				//temprover->IncNofMiss();
				//temprover->IncNumMissDoneBCH();
				tempmission->setroverID(temprover->getIDRover());
				temprover->AssignMiss(tempmission);
				temprover->setmissionID(tempmission->GetID());
				tempmission->setexcuted(Currentday);
				In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());   // should get another vlaue to determine the prio for rovers
				avail_EM_Rover--;
				nowaiting_Mountainous--;
				inExecution_Rovers++;
			}
		}
	}
}

void MarsStation::InccuChUpDuration()
{
	//Incremint days in the check up duraion
	Queue<Rover*> tempInCheckup_Emergency;
	Queue<Rover*> tempInCheckup_Polar;
	Queue<Rover*> tempInCheckup_Mountainous;

	while (!InCheckup_Emergency.isEmpty())
	{
		Rover* temprover;
		InCheckup_Emergency.dequeue(temprover);
		temprover->IncCuChupD();
		tempInCheckup_Emergency.enqueue(temprover);
	}

	while (!InCheckup_Mountainous.isEmpty())
	{
		Rover* temprover;
		InCheckup_Mountainous.dequeue(temprover);
		temprover->IncCuChupD();
		tempInCheckup_Mountainous.enqueue(temprover);
	}

	while (!InCheckup_Polar.isEmpty())
	{
		Rover* temprover;
		InCheckup_Polar.dequeue(temprover);
		temprover->IncCuChupD();
		tempInCheckup_Polar.enqueue(temprover);
	}
	while (!tempInCheckup_Polar.isEmpty())
	{
		Rover* temprover;
		tempInCheckup_Polar.dequeue(temprover);
		
		InCheckup_Polar.enqueue(temprover);
	}

	while (!tempInCheckup_Mountainous.isEmpty())
	{
		Rover* temprover;
		tempInCheckup_Mountainous.dequeue(temprover);
		
		InCheckup_Mountainous.enqueue(temprover);
	}

	while (!tempInCheckup_Emergency.isEmpty())
	{
		Rover* temprover;
		tempInCheckup_Emergency.dequeue(temprover);

		InCheckup_Emergency.enqueue(temprover);
	}

	Rover* temprover;

	InCheckup_Emergency.peekFront(temprover);
	while (!InCheckup_Emergency.isEmpty() &&!temprover->IsInCheckUp() )
	{
		InCheckup_Emergency.dequeue(temprover);
		Availabe_Emergency.enqueue(temprover, temprover->getSpeed());
		InCheckup_Emergency.peekFront(temprover);
		E_inCHekUp--;
		avail_EM_Rover++;
	}

	InCheckup_Polar.peekFront(temprover);
	while (!InCheckup_Polar.isEmpty() &&  !temprover->IsInCheckUp())
	{
		InCheckup_Polar.dequeue(temprover);
		Availabe_Polar.enqueue(temprover, temprover->getSpeed());
		InCheckup_Polar.peekFront(temprover);
		P_inCHekUp--;
		avail_Po_Rover++;
	}

	InCheckup_Mountainous.peekFront(temprover);
	while (!InCheckup_Mountainous.isEmpty() && !temprover->IsInCheckUp())
	{
		InCheckup_Mountainous.dequeue(temprover);
		Availabe_Mountainous.enqueue(temprover, temprover->getSpeed());
		InCheckup_Mountainous.peekFront(temprover);
		M_inCHekUp--;
		avail_MO_Rover++;
	}
}

void MarsStation::incrementEDS()
{
	Queue<Rover*> tempIn_Execution_Rover;
	Rover* temprover;
	//float p = 0;									// check chack chock check chack chock check chack chock 
	while (!In_Execution_Rover.isEmpty())
	{
		
		In_Execution_Rover.dequeue(temprover); // check chack chock check chack chock check chack chock 
		Mission* tempmission = temprover->getMiss();
		tempmission->incEDS();
		tempIn_Execution_Rover.enqueue(temprover);
	}

	while (!tempIn_Execution_Rover.isEmpty())
	{
		tempIn_Execution_Rover.dequeue(temprover);
		In_Execution_Rover.enqueue(temprover, temprover->getMiss()->GetTheEnDayswithTimetoTL());   // check chack chock check chack chock check chack chock 
	}
}

void MarsStation::incrementWDS()
{
	
	Queue<Mission*> tempwaiting_Emergency;
	Queue<Mission*> tempwaiting_Polar;
	Queue<Mission*> tempwaiting_Mountainous;

	Mission* tempmission;
	//float p = 0;                                  // check chack chock check chack chock check chack chock 
	while (!waiting_Emergency.isEmpty())
	{

		waiting_Emergency.dequeue(tempmission); // check chack chock check chack chock check chack chock 
		tempmission->incWDS();
		tempwaiting_Emergency.enqueue(tempmission);
	}

	while (!waiting_Mountainous.isEmpty())
	{

		waiting_Mountainous.dequeue(tempmission);
		tempmission->incWDS();
		tempwaiting_Mountainous.enqueue(tempmission);
	}

	while (!waiting_Polar.isEmpty())
	{

		waiting_Polar.dequeue(tempmission); 
		tempmission->incWDS();
		tempwaiting_Polar.enqueue(tempmission);
	}


	while (!tempwaiting_Polar.isEmpty())
	{
		tempwaiting_Polar.dequeue(tempmission);
		waiting_Polar.enqueue(tempmission);   
	}

	while (!tempwaiting_Mountainous.isEmpty())
	{
		tempwaiting_Mountainous.dequeue(tempmission);
		waiting_Mountainous.enqueue(tempmission);
	}

	while (!tempwaiting_Emergency.isEmpty())
	{
		tempwaiting_Emergency.dequeue(tempmission);
		waiting_Emergency.enqueue(tempmission, tempmission->getPriority());   // check chack chock check chack chock check chack chock 
	}
}

void MarsStation::checkcompletedmissions()
{
	if (!In_Execution_Rover.isEmpty())
	{
		Rover* temprover;
		In_Execution_Rover.peek(temprover);
		//float p = 0;                                     // check chack chock check chack chock check chack chock 
		Mission* tempmission = temprover->getMiss();

		while (!In_Execution_Rover.isEmpty() && tempmission->GetEDS() >= tempmission->GetTimeToTL() + tempmission->GetMDUR())
		{
			In_Execution_Rover.dequeue(temprover); // check chack chock check chack chock check chack chock 
			inExecution_Rovers--;
			Completed_Missions.enqueue(tempmission);
			nCompleted++;
			temprover->Discharge();
			//tempmission->SetEDS(tempmission->GetEDS());
			if (temprover->IsInCheckUp() && temprover->getTypeRover() == 'P')
			{
				InCheckup_Polar.enqueue(temprover);
				P_inCHekUp++;
			}
			else if (temprover->IsInCheckUp() && temprover->getTypeRover() == 'E')
			{
				InCheckup_Emergency.enqueue(temprover);
				E_inCHekUp++;
			}
			else if (temprover->IsInCheckUp() && temprover->getTypeRover() == 'M')
			{
				InCheckup_Mountainous.enqueue(temprover);
				M_inCHekUp++;
			}
			else if (!temprover->IsInCheckUp() && temprover->getTypeRover() == 'P')
			{
				Availabe_Polar.enqueue(temprover,temprover->getSpeed());
				avail_Po_Rover++;
			}
			else if (!temprover->IsInCheckUp() && temprover->getTypeRover() == 'E')
			{
				Availabe_Emergency.enqueue(temprover, temprover->getSpeed());
				avail_EM_Rover++;
			}
			else if (!temprover->IsInCheckUp() && temprover->getTypeRover() == 'M')
			{
				Availabe_Mountainous.enqueue(temprover, temprover->getSpeed());
				avail_MO_Rover++;
			}

			In_Execution_Rover.peek(temprover);
			tempmission = temprover->getMiss();
		}
	
	}
}

/*
void MarsStation::checkuprover()
{
	Queue<Rover*> tempAvailabe_Emergency;
	Queue<Rover*> tempAvailabe_Polar;

	while (!Availabe_Emergency.isEmpty())
	{
		Rover* temprover;
		Availabe_Emergency.dequeue(temprover);
		if (temprover->getNumberofMissionsBeforeCheckUp() == temprover->getNofMiss())
		{
			temprover;
			InCheckup_Emergency.enqueue(temprover);
		}
	}

	while (!Availabe_Polar.isEmpty())
	{

	}
}
*/




void MarsStation::StepByStep()
{
	AddToList();
	Currentday = 1;
	while (nCompleted != nEvents)  //// would be while not all the missions are done
	{
		//dequeueEvent(Currentday);


		// move rovers and missions 

		checkcompletedmissions();
		moveFromEventToWaiting();
		AssignWaitingMission();
		incrementEDS();
		incrementWDS();
		calculateCD();
		// update interface
		InccuChUpDuration();
		ui->UpdateInterface(Currentday,
			nowaiting_Polar, waiting_Polar, nowaiting_Emergency, waiting_Emergency, nowaiting_Mountainous, waiting_Mountainous,
			inExecution_Rovers, In_Execution_Rover,
			avail_EM_Rover, Availabe_Emergency, avail_Po_Rover, Availabe_Polar, avail_MO_Rover, Availabe_Mountainous,
			P_inCHekUp, InCheckup_Emergency, E_inCHekUp, InCheckup_Polar, M_inCHekUp, InCheckup_Mountainous,
			nCompleted, Completed_Missions);
		Currentday++;
		ui->WaitForSecond();
	}
	ui->OutputFile(Completed_Missions);
}
void MarsStation::Silent()
{
	AddToList();
	Currentday = 1;
	while (nCompleted != nEvents)  //// would be while not all the missions are done
	{
		//dequeueEvent(Currentday);


		// move rovers and missions 

		checkcompletedmissions();
		moveFromEventToWaiting();
		AssignWaitingMission();
		incrementEDS();
		incrementWDS();
		calculateCD();
		// update interface
		InccuChUpDuration();
		/*ui->UpdateInterface(Currentday,
			nowaiting_Polar, waiting_Polar, nowaiting_Emergency, waiting_Emergency,
			inExecution_Rovers, In_Execution_Rover,
			avail_EM_Rover, Availabe_Emergency, avail_Po_Rover, Availabe_Polar,
			P_inCHekUp, InCheckup_Polar, E_inCHekUp, InCheckup_Emergency,
			nCompleted, Completed_Missions);*/
		Currentday++;
		//ui->WaitForEnter();
	}
	ui->OutputFile(Completed_Missions);
	
}
MarsStation::~MarsStation()
{


}