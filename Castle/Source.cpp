#include "file_IO.h"

int main()
{
	SetWindow();	//adjust game window settings
	castle ct; // define a castle 

	ct.Xstrt = CastleXStrt;
	ct.Ystrt = CastleYStrt;
	ct.W = CastleWidth;
	ct.L = CastleLength;
	//Intializing the number of active regular enemies and the number of killed.
	int RegSize = 0, SHsize = 0, NumKilled = 0;

	Tower* TowerHead = NULL;    //Intializing head of the towers list.

	Queue in_regFigthersHead ;   //Intializing the regular enemies queue.
	in_regFigthersHead.bounds.front = in_regFigthersHead.bounds.rear = NULL;
	
	Queue in_SHFighterHead ;    //Intializing the shielded enemy queue.
	in_SHFighterHead.bounds.front = in_SHFighterHead.bounds.rear = NULL;

	enemy* ac_regFigthersHead = NULL;  //Intializing the active regular enemies list.

	enemy* ac_SHFighterHead = NULL;   //Intializing the active shielded enemies list.

	enemy* DeadHead = NULL;   //Intializing the dead enemies list.

	double Constants[3];     //creating an array to store constants.

	//calling the load file function to extract data from the input file.
	LoadFile(Constants,TowerHead, in_regFigthersHead, in_SHFighterHead);
	TowerHead->TL=TowerLength;
	TowerHead->TW=TowerWidth;
	TowerHead->UnpavedArea = 60;
	for (Tower t : ct.towers)
		t = *TowerHead;
	//Intializing the time step counter to 1.
	int timestep = 1;

	//execute at least once.
	do
	{
		//Activate all regular enemies with an arrival time matching the timestep.
		Activate(in_regFigthersHead, ac_regFigthersHead, timestep, RegSize);

		//Activate all shielded enemies with an arrival time matching the timestep.
		Activate(in_SHFighterHead, ac_SHFighterHead, timestep, SHsize);


		//intializing a pointer to store the randomly selected enemy to be killed.
		enemy* K = NULL; int i = 0;

		//loop as long as we still have active regular enemies.
		//And we have selected not more than enemies per timestep.
		while (RegSize != 0 && i < 2) {
			//Search for a randomly selected enemy.
			K = SearchEnemy(ac_regFigthersHead, rand() % RegSize + 1);

			if (K != NULL) {
				DetachEnemy(K, ac_regFigthersHead); //detach the enemy from the active list.
				RegSize--;     //decrementing the regular enemy list's size by one.
				Kill(K, DeadHead); //killing the randomly selected regular enemy.
				NumKilled++;  //incrementing the number of killed enemies
			}

			K = NULL; i++;   //reseting values and updating the loop's counter.
		}

		K = NULL; i = 0;   //reseting values.
		while (SHsize != 0 && i < 2) {

			//Search for a randomly selected enemy.
			K = SearchEnemy(ac_SHFighterHead, rand() % SHsize + 1);

			if (K != NULL) {
				DetachEnemy(K, ac_SHFighterHead); //detach the enemy from the active list.
				SHsize--;    //decrementing the shielded enemy list's size by one.
				Kill(K, DeadHead);  //killing the randomly selected shielded enemy.
				NumKilled++;  //incrementing the number of killed enemies
			}

			K = NULL; i++;  //reseting values and updating the loop's counter.
		}
		enemy *itr = ac_SHFighterHead;
		enemy** enemies = new enemy*[SHsize+RegSize];
		for (int i = 0; i < SHsize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}
		itr = ac_regFigthersHead;
		for (int i = SHsize; i < SHsize+RegSize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}
		
		DrawCastle(ct, timestep);
		DrawEnemies(enemies, SHsize + RegSize);


		timestep++; //incrementing the timestep by one. 

		Sleep(1000);

	}while (!(ac_regFigthersHead == NULL&&ac_SHFighterHead == NULL
		      &&in_regFigthersHead.bounds.front == NULL
		      &&in_SHFighterHead.bounds.front == NULL));
	/* loop as long as we don't have any active regular enemies, nor shieled
	active enemies, nor inactive regular enemies, nor inactive shielded enemies*/

	//Printing the time taken for the simulation to finalize.
	cout <<endl<< " Time taken : " << timestep-1 << endl;

	//END OF SIMULATION.
	cout << "\n ALL enemies died , simulation terminated . \n" << " War ended !";
	cin.get();
}