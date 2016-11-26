include <iostream>
using namespace std;


#include "utility.h"
/*
//This is a demo program to test utlity function given in utlity.h/.cpp
int main()
{
	SetWindow();	//adjust game window settings

	castle ct; // define a castle 


	ct.Xstrt = CastleXStrt;
	ct.Ystrt = CastleYStrt;
	ct.W = CastleWidth;
	ct.L = CastleLength;
	//intialize health of the towers
	ct.towers[0].Health=200;
	ct.towers[1].Health=200;
	ct.towers[2].Health=200;
	ct.towers[3].Health=200;

	//Declare some enemies and fill their data
	//In the game, enemies should be loaded from an input file
	enemy e1;
	e1.ID=0;	e1.Region=A_REG;	e1.Distance=37;		e1.Health=5; e1.Type=FITR;

	enemy e2;
	e2.ID=1;	e2.Region=D_REG;	e2.Distance=17;		e2.Health=7; e2.Type=PVR;

	enemy e3;
	e3.ID=2;	e3.Region=B_REG;	e3.Distance=30;		e3.Health=8; e3.Type=SHLD_FITR;

	enemy e4;
	e4.ID=3;	e4.Region=A_REG;	e4.Distance=11;		e4.Health=9; e4.Type=SHLD_FITR;

	enemy e5;
	e5.ID=3;	e5.Region=C_REG;	e5.Distance=19;		e5.Health=9; e5.Type=SHLD_FITR;

	enemy e6;
	e6.ID=3;	e6.Region=C_REG;	e6.Distance=30;		e6.Health=9; e6.Type=FITR;

	enemy* enemies[6];
	enemies[0]=&e1;
	enemies[1]=&e2;
	enemies[2]=&e3;
	enemies[3]=&e4;
	enemies[4]=&e5;
	enemies[5]=&e6;

	int Ecnt=6;	//enemy count
	int TimeStep = 1;

	///Now time to Draw
	//[1],[2],[3] Clear the screen, Draw the castle, Draw the regions
	DrawCastle(ct,TimeStep);

	//[4] Draw enemies
	DrawEnemies(enemies,Ecnt);
	
	
	//[5] Print message/statistics	
	PrintMsg("Total current eneimes  A = 2\tB = 1\tC = 2\tD = 1 \n");
	PrintMsg("Last time step kill    A = 0\tB = 0\tC = 0\tD = 0 \n");
	PrintMsg("Total killed by        A = 0\tB = 0\tC = 0\tD = 0 \n");
	PrintMsg("Unpaved distance      A = 30\tB = 30\tC = 30\tD = 30 \n");

	PrintMsg("\nPress ENTER to start motion demo");
	cin.get();

	///Now a demo to move enemies 7 steps
	for(int i=0; i< 7; i++)
	{
		for(int i=0; i<Ecnt; i++) 
		{
			enemies[i]->Distance --; //decrease distance of all enemies
		}
		DrawCastle(ct,++TimeStep);
		DrawEnemies(enemies,Ecnt);

		Sleep(1000);	//Delay 1 sec to notice the animation

		//[5] Print message/statistics	
		PrintMsg("Total current eneimes  A = 2\tB = 1\tC = 2\tD = 1 \n");
		PrintMsg("Last time step kill    A = 0\tB = 0\tC = 0\tD = 0 \n");
		PrintMsg("Total killed by        A = 0\tB = 0\tC = 0\tD = 0 \n");
		PrintMsg("Unpaved distance      A = 30\tB = 30\tC = 30\tD = 30 \n");

		
	}
	
	return 0;
}
*/