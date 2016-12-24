#include "file_IO.h"
#include <Windows.h>
#include <Mmsystem.h>

int main()
{
	PlaySound(TEXT("C:\\Test.wav"), NULL, SND_FILENAME);

	SetWindow();	   //Adjusting game window settings.
	castle ct;         //Define a castle. 
	Statistics stats;  //Define a statistics hub to store all stats.
	//Intializing stats variables.
	stats.FightDelay = 0, stats.KillDelay = 0, stats.Total_active = 0, stats.lastKilled = 0;
	stats.Total_inactive = 0, stats.Total_killed = 0, stats.Tower_intialHealth = 0, stats.num_Agents = 0;

	ofstream out;   //creating an output stream to produce the output file.
	
	out.open("output.txt", ios::out);  //opening the output file for writing.

	PrintTabs(out);   //printing tabs of the table in the output file.

	char won = ' ';    //store a character to denote who won the war.
	bool CastleDestroyed = false;  //to check if the whole castle has been desotryed.
	enemy** enemies = NULL;  //pointer to a dynamically allocated array of pointers 
	                         //enemies used in the utility for drawing enemies.
	
	//setting constants of the castle.
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

	/*implementing the mode feature.
	interactive mode : runs automatically and displays output.
	step-by-step mode : wait for user input to continue running.
	silent mode : runs behind the doors, produces an output file only*/
	cout << "In what mode you want to run the simulation " << endl;
	cout << "Enter 0 for interactive mode"  << endl;
	cout << "Enter 1 for step-by-step mode" << endl;
	cout << "Enter 2 for silent mode" << endl;
	cin >> mode;
	
	//execute at least once.
	do
	{
		//Activate all regular enemies with an arrival time matching the timestep.
		Activate(in_regFigthersHead, ac_regFigthersHead, timestep, RegSize,stats);

		//Activate all shielded enemies with an arrival time matching the timestep.
		Activate(in_SHFighterHead, ac_SHFighterHead, timestep, SHsize,stats);

		//updating the value of total number of active enemies after each activiation.
		stats.Total_active = SHsize + RegSize;
		
		//check for reloading enemies, activiate then when their reloading prd ends.
		CheckReloadingEnemies(ac_regFigthersHead, ac_SHFighterHead);

		//dynamically allocating and array of pointers with the size of the total alive and agents.
		enemies = new enemy*[stats.Total_active + stats.num_Agents];
		
		//filling the array with pointers to all shielded enemies.
		enemy *itr = ac_SHFighterHead;
		for (int i = 0; i < SHsize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}
		
		//filling the rest of the array with pointers to all regular enemies.
		itr = ac_regFigthersHead;
		for (int i = SHsize; i < RegSize + SHsize; i++) {
			enemies[i] = itr;
			itr = itr->next;
		}
		
		//filling the array with pointers to all castle agents.
		int k = RegSize + SHsize;
		for (int i = 0; i < 4; i++) {
			itr = ct.towers[i].Agents;
			while (itr!= NULL) {
				enemies[k] = itr;
				k++;
				itr = itr->next;
			}
		}

		if (mode == 1)
			cin.get(); //wait for user input.

		//if the simulation runs within the silent mode, DON'T display data.
		if (mode != 2) {
			DrawCastle(ct, timestep, stats);
			DrawEnemies(enemies, stats.Total_active+stats.num_Agents);
		}

		//reseting the dead head to NULL after each timestep, same with the num of killed.
		DeadHead = NULL; stats.lastKilled = 0;

		/*Active non-reloading enemies start shooting the towers, enemy to tower damage
		is calculated and the tower health is reduced accordingly, also checks for tower
		destruction, relocate enemies to adjacent regions if needed*/
		EnemyShoot(ac_regFigthersHead, ac_SHFighterHead, in_regFigthersHead, in_SHFighterHead, ct);

		/*The towers shoots N enemies in its region at most based on their pirority, checks
		for dead enemies, moves them to the dead list, update enemies priorities when needed*/
		TowerShoot(ac_SHFighterHead, Constants, ac_regFigthersHead,
			       DeadHead, timestep, ct.towers, RegSize, SHsize, stats,ct);

		//updating the number of active enemies after the tower shoots, in case of death of an active enemy.
		stats.Total_active = SHsize + RegSize;

		//non-reloading pavers pave.  
		Pave(ac_regFigthersHead, ct);

		//Enemies move according to their speed if the ahead movement range is paved.
		MoveEnemies(ac_regFigthersHead, ac_SHFighterHead, ct);

		//processes the deah list, extract all the needed data, output it to the ouput file
		//then frees the memory by deleting all killed enemies every timestep.
		CollectStatistics(DeadHead, stats, out);

		//checks if the castle was destoryed or not.
		WhoWon(ct, won, CastleDestroyed);

		timestep++; //incrementing the timestep by one. 


		if (mode == 0)
			Sleep(1000);    //pause a sec. to be able to follow dispaly changes.

	} while (!((ac_regFigthersHead == NULL&&ac_SHFighterHead == NULL
		&&in_regFigthersHead.bounds.front == NULL
		&&in_SHFighterHead.bounds.front == NULL) || CastleDestroyed));
	/*loop until either all enemies died or the castle has been destoryed*/

	//Drawing the castle and enemies on more time to reflect last timestep's changes.
	DrawCastle(ct, timestep, stats);
	DrawEnemies(enemies, stats.Total_active+stats.num_Agents);

	//Output the simulation status to the output file.
	OutputSimStatus(stats,ct, won,out);

	//Printing the time taken for the simulation to finalize.
	out << endl << " Time taken : " << timestep - 1 << " time steps" << endl;

	out.close();   //closing the output file.
	
	//END OF SIMULATION.

	cin.get();
}