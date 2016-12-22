#include "file_IO.h"

void LoadFile(double* Con,castle &Castle ,Queue &regHead,Queue &SFH,Statistics &stats)
{
	int Index, T, ArrivalTime, ReloadPeriod, TowerHit, EnemySpeed;
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
		Castle.towers[i].Health = TowerHealth;
		Castle.towers[i].TowerKillingCapacity = TowerHit;
		Castle.towers[i].TowerFirePower = TowerFireP;
		Castle.towers[i].TL = TowerLength;
		Castle.towers[i].TW = TowerWidth;
		Castle.towers[i].UnpavedArea = 30;
		Castle.towers[i].Destroyed = false;
	}
	stats.Tower_intialHealth = TowerHealth;

	//loading the constants used in calculations and storing them in an array.
	for (int i = 0; i < 3; i++) {
		input >> Con[i];
	}

	//Stop when -1 is encountred "denotes end of file".
	input >> Index; 
	while (Index != -1) {

		input>>T >> ArrivalTime >> Health >> FirePower >> ReloadPeriod>>EnemySpeed>> R;
		
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
		Data->Distance = 60;
		Data->FirstShotTime=-1;
		Data->Hold = 0;
		Data->DeathTime = 0;
		Data->Reloading = false;
		Data->Priorty = 0.0;
		Data->speed = EnemySpeed;

		/*The next few lines resemble the insertion logic, depending on the
		the type specified in the input file, we insert pavers and regular
		fighters in a queue, and we insert shielded fighters in a seprate queue*/

		//Put all shield fighters in one queue
		if (Type == SHLD_FITR) 
			Enqueue(SFH, Data,stats);
			
		//Put all other regular fighters in a seperate queue
		else
			Enqueue(regHead, Data,stats);
		
		input >> Index;
	}
	input.close();
}

//Prints the needed tabs in the output file.
void PrintTabs(ofstream &out)
{
	out << "KTS      S        FD       KD       FT" << endl;
}

//outputing status in the output file.
void OutputSimStatus(Statistics &stats,castle &Castle, char whoWon,ofstream &out)
{
	out << endl << endl;

	out << "T1_Total_Damage :" << stats.Tower_intialHealth - Castle.towers[0].Health << endl;
	out << "T2_Total_Damage :" << stats.Tower_intialHealth - Castle.towers[1].Health << endl;
	out << "T3_Total_Damage :" << stats.Tower_intialHealth - Castle.towers[2].Health << endl;
	out << "T4_Total_Damage :" << stats.Tower_intialHealth - Castle.towers[3].Health << endl;
	out << endl;

	out << "R1_Distance :" << Castle.towers[0].UnpavedArea << endl;
	out << "R2_Distance :" << Castle.towers[1].UnpavedArea << endl;
	out << "R3_Distance :" << Castle.towers[2].UnpavedArea << endl;
	out << "R4_Distance :" << Castle.towers[3].UnpavedArea << endl;
	out << endl;

	if (whoWon == 'C') {
		out << " GAME IS A WIN" << endl << endl;
		out << "Total Number of Enemies : " << stats.Total_killed << endl;
		out << "Avarage Figth Delay : " << (double)stats.FightDelay / (double)stats.Total_killed << endl;
		out << "Avarage Kill Delay : " << (double)stats.KillDelay / (double)stats.Total_killed << endl;
	}
	else {
		out << " GAME IS A LOSS" << endl << endl;
		out << "Number of Killed Enemies : " << stats.Total_killed << endl;
		out << "Number of Alive Enemies : " << stats.Total_active + stats.Total_inactive << endl;
		out << "Avarage Figth Delay : " << (double)stats.FightDelay / (double)stats.Total_killed << endl;
		out << "Avarage Kill Delay : " << (double)stats.KillDelay / (double)stats.Total_killed << endl;
	}
	out <<endl<< "END OF SIMULATION" << endl;
}