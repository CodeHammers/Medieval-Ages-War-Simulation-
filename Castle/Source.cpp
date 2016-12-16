#include "file_IO.h"

int main()
{
	SetWindow();	//adjust game window settings
	castle ct;      // define a castle 
	Statistics stats; 
	ofstream out("output.txt", ios::out);

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
	LoadFile(Constants, ct, in_regFigthersHead, in_SHFighterHead);



	//Intializing the time step counter to 1.
	int timestep = 1;

	//execute at least once.
	do
	{
		//Activate all regular enemies with an arrival time matching the timestep.
		Activate(in_regFigthersHead, ac_regFigthersHead, timestep, RegSize);

		//Activate all shielded enemies with an arrival time matching the timestep.
		Activate(in_SHFighterHead, ac_SHFighterHead, timestep, SHsize);

		CheckReloadingEnemies(ac_regFigthersHead, ac_SHFighterHead);

		enemy** enemies = new enemy*[SHsize + RegSize];

		enemy *itr = ac_SHFighterHead;
		for (int i = 0; i < SHsize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}

		itr = ac_regFigthersHead;
		for (int i = SHsize ; i < RegSize+SHsize ; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}

		DrawCastle(ct, timestep);
		DrawEnemies(enemies, SHsize + RegSize);

		DeadHead = NULL;

		//Enemies Shoot the castle
		EnemyShoot(ac_regFigthersHead, ac_SHFighterHead, in_regFigthersHead, in_SHFighterHead, ct);

		//Castle Shoots Enemies
		TowerShoot(ac_SHFighterHead, Constants,ac_regFigthersHead,
			DeadHead,timestep,ct.towers,RegSize,SHsize);

		//pavers pave if possible  
		Pave(ac_regFigthersHead,ct);

		//Enemies move
		MoveEnemies(ac_regFigthersHead,ac_SHFighterHead,ct);

		CollectStatistics(DeadHead, stats, out);

		timestep++; //incrementing the timestep by one. 

		Sleep(1000);

	} while (!(ac_regFigthersHead == NULL&&ac_SHFighterHead == NULL
		&&in_regFigthersHead.bounds.front == NULL
		&&in_SHFighterHead.bounds.front == NULL));
	/* loop as long as we don't have any active regular enemies, nor shieled
	active enemies, nor inactive regular enemies, nor inactive shielded enemies*/

	//just for testing
	OutputSimStatus(stats, ct, 'c');
	//Printing the time taken for the simulation to finalize.
	cout << endl << " Time taken : " << timestep - 1 << endl;

	//END OF SIMULATION.
	cout << "\n ALL enemies died , simulation terminated . \n" << " War ended !";
	cin.get();
}