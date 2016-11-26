#include "file_IO.h"

void LoadFile(double* Con,Tower*&THead ,Queue &regHead,Queue &SFH)
{
	int Index, T, ArrivalTime, ReloadPeriod, TowerHit;
	double Health, FirePower, TowerHealth, TowerFireP; char R;
	Etype Type; REGION Region;

	//opening the input file and checking for unexpected reading errors.
	ifstream input("simulation input.txt", ios::in);
	if (!input.is_open()) {
		cout << "Error : input file is not found " << endl;
		return;
	}

	//Loading the tower data.
	input >> TowerHealth >> TowerHit >> TowerFireP;
	for (int i = 0; i < 4; i++) {
		if (!InsertTower(THead, TowerHealth, TowerHit, TowerFireP)) {
			cout << "Error while inserting a tower node, check insert tower function " << endl;
			return;
		}
	}

	//loading the constants used in calculations and storing them in an array.
	for (int i = 0; i < 3; i++) {
		input >> Con[i];
	}

	//Stop when -1 is encountred "denotes end of file".
	input >> Index; 
	while (Index != -1) {

		input>>T >> ArrivalTime >> Health >> FirePower >> ReloadPeriod >> R;
		
		Type = static_cast<Etype>(T);     //converting int to enemy enum type.
		Region = static_cast<REGION>(R);  //converting char to region enum type, stores ASCII. 

		enemy* Data = new enemy;  //Allocating memory for a new enemy node.
		//Filling data into the enemy node.
		Data->ID = Index;
		Data->ArrivalTime = ArrivalTime;
		Data->Health = Health;
		Data->FirePower = FirePower;
		Data->ReloadPeriod = ReloadPeriod;
		Data->Type = Type;
		Data->Region = Region;

		/*The next few lines resemble the insertion logic, depending on the
		the type specified in the input file, we insert pavers and regular
		fighters in a queue, and we insert shielded fighters in a seprate queue*/

		//Put all shield fighters in one queue
		if (Type == SHLD_FITR) 
			Enqueue(SFH, Data);
			
		//Put all other regular fighters in a seperate queue
		else
			Enqueue(regHead, Data);
		
		input >> Index;
	}
	input.close();
}