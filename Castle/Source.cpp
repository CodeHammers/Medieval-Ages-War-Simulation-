#include "file_IO.h"

int main()
{
	SetWindow();	//adjust game window settings
	castle ct;      // define a castle 
	Statistics stats;
	stats.FightDelay = 0, stats.KillDelay = 0, stats.Total_active = 0, stats.lastKilled = 0;
	stats.Total_inactive = 0, stats.Total_killed = 0, stats.Tower_intialHealth = 0;

	ofstream out;
	
	//out.clear();
	//PrintTabs(out);
	char won = ' '; bool CastleDestroyed = false;

	ct.Xstrt = CastleXStrt;
	ct.Ystrt = CastleYStrt;
	ct.W = CastleWidth;
	ct.L = CastleLength;

	//Intializing the number of active regular enemies and the number of killed.
	int RegSize = 0, SHsize = 0, NumKilled = 0;

	Queue in_regFigthersHead;   //Intializing the regular enemies queue.
	in_regFigthersHead.bounds.front = in_regFigthersHead.bounds.rear = NULL;

	Queue in_SHFighterHead;    //Intializing the shielded enemy queue.
	in_SHFighterHead.bounds.front = in_SHFighterHead.bounds.rear = NULL;

	enemy* ac_regFigthersHead = NULL;  //Intializing the active regular enemies list.

	enemy* ac_SHFighterHead = NULL;   //Intializing the active shielded enemies list.

	enemy* DeadHead = NULL;   //Intializing the dead enemies list.

	double Constants[3];     //creating an array to store constants.

	//calling the load file function to extract data from the input file.
	LoadFile(Constants, ct, in_regFigthersHead, in_SHFighterHead, stats);


	//Intializing the time step counter to 1.
	int timestep = 1, mode = 0;

	cout << "In what mode you want to run the simulation " << endl;
	cout << "Enter 0 for interactive mode" << endl;
	cout << "Enter 1 for step-by-step mode" << endl;
	cout << "Enter 2 for silent mode" << endl;
	cin >> mode;
	//ct.towers[1].Health = 0;
	out.open("output.txt", ios::app);
	//execute at least once.
	do
	{
		//Activate all regular enemies with an arrival time matching the timestep.
		Activate(in_regFigthersHead, ac_regFigthersHead, timestep, RegSize);

		//Activate all shielded enemies with an arrival time matching the timestep.
		Activate(in_SHFighterHead, ac_SHFighterHead, timestep, SHsize);

		stats.Total_active = SHsize + RegSize;

		CheckReloadingEnemies(ac_regFigthersHead, ac_SHFighterHead);

		enemy** enemies = new enemy*[SHsize + RegSize];

		enemy *itr = ac_SHFighterHead;
		for (int i = 0; i < SHsize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}

		itr = ac_regFigthersHead;
		for (int i = SHsize; i < RegSize + SHsize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}

		if (mode != 2) {
			DrawCastle(ct, timestep, stats);
			DrawEnemies(enemies, stats.Total_active);
		}
		DeadHead = NULL;

		//Enemies Shoot the castle
		EnemyShoot(ac_regFigthersHead, ac_SHFighterHead, in_regFigthersHead, in_SHFighterHead, ct);

		//Castle Shoots Enemies
		TowerShoot(ac_SHFighterHead, Constants, ac_regFigthersHead,
			DeadHead, timestep, ct.towers, RegSize, SHsize, stats);

		//pavers pave if possible  
		Pave(ac_regFigthersHead, ct);

		//Enemies move
		MoveEnemies(ac_regFigthersHead, ac_SHFighterHead, ct);

		CollectStatistics(DeadHead, stats, out);

		WhoWon(ct, won, CastleDestroyed);

		stats.lastKilled = 0;

		timestep++; //incrementing the timestep by one. 
		if (mode == 0)
			Sleep(1000);
		else if(mode == 1)
			cin.get();

	} while (!((ac_regFigthersHead == NULL&&ac_SHFighterHead == NULL
		&&in_regFigthersHead.bounds.front == NULL
		&&in_SHFighterHead.bounds.front == NULL) || CastleDestroyed));
	/* loop as long as we don't have any active regular enemies, nor shieled
	active enemies, nor inactive regular enemies, nor inactive shielded enemies*/

	//just for testing
	//OutputSimStatus(stats,ct, won,out);
	out.close();
	cin.get();
	//Printing the time taken for the simulation to finalize.
	cout << endl << " Time taken : " << timestep - 1 << endl;

	//END OF SIMULATION.
	cout << "\n ALL enemies died , simulation terminated . \n" << " War ended !";
	cin.get();
}