#include "file_IO.h"

void LoadFile(double* Con,castle &Castle ,Queue &regHead,Queue &SFH,Statistics &stats)
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
		Data->Distance = 60;
		Data->FirstShotTime=-1;
		Data->Hold = 0;
		Data->DeathTime = 0;
		Data->Reloading = false;
		Data->Priorty = 0.0;
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


void PrintTabs(ofstream &out)
{
	out.open("output.txt", ios::app);
	cout << "KTS     S     FD     KD     FT" << endl;
	out.close();
}


//void OutputKilled(int FD, int KD, int FT,int KTS, int S)
//{
//	ofstream out("output.txt", ios::app);
//	out << left << setw(5) << setfill(' ') << KTS << " ";
//	out << left << setw(5) << setfill(' ') << S   << " ";
//	out << left << setw(5) << setfill(' ') << FD  << " ";
//	out << left << setw(5) << setfill(' ') << KD  << " ";
//	out << left << setw(5) << setfill(' ') << FT  << " ";
//	out << endl;
//}


void OutputSimStatus(Statistics &stats,castle &Castle, char whoWon,ofstream &out)
{
	out.open("output.txt", ios::app);

	out << "T1_Total_Damage      T2_Total_Damage      T3_Total_Damage      T4_Total_Damage" << endl;
	out << "   " << stats.Tower_intialHealth - Castle.towers[0].Health;
	out << "   " << stats.Tower_intialHealth - Castle.towers[1].Health;
	out << "   " << stats.Tower_intialHealth - Castle.towers[2].Health;
	out << "   " << stats.Tower_intialHealth - Castle.towers[3].Health;
	out << endl << endl;

	out << "R1_Distance      R2_Distance      R3_Distance      R4_Distance" << endl;
	out << "  " << Castle.towers[0].UnpavedArea;
	out << "  " << Castle.towers[1].UnpavedArea;
	out << "  " << Castle.towers[2].UnpavedArea;
	out << "  " << Castle.towers[3].UnpavedArea;
	cout << endl << endl;

	if (whoWon == 'C') {
		out << " GAME IS A WIN" << endl;
		out << "Total Number of Enemies : " << stats.Total_killed << endl;
		out << "Avarage Figth Delay : " << (double)stats.FightDelay / (double)stats.Total_killed << endl;
		out << "Avarage Kill Delay : " << (double)stats.KillDelay / (double)stats.Total_killed << endl;
	}
	else {
		cout <<" GAME IS A LOSS" << endl;
		out << "Number of Killed Enemies : " << stats.Total_killed << endl;
		out << "Number of Alive Enemies : " << stats.Total_active + stats.Total_inactive << endl;
		out << "Avarage Figth Delay : " << (double)stats.FightDelay / (double)stats.Total_killed << endl;
		out << "Avarage Kill Delay : " << (double)stats.KillDelay / (double)stats.Total_killed << endl;
	}
	out << "END OF SIMULATION" << endl;
	out.close();
}