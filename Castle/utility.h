#include <iostream>
using namespace std;

#include <windows.h>

//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

//Enemy types: Paver, Fighter, Shielded Fighter and the castle agent: JamesBond.
enum Etype {
	PVR,
	FITR,
	SHLD_FITR,
	JamesBond //refer to the next comment for description.
};

/*James Bond Description : He is a devoted castle agent, appears on the display in a
blue outfit, he is a camper so he doesn't move, he only snips pavers while in cover,
when the tower he is serving is desotyed, he disables himself, he is equipped with a 
high caliber weapon so he doesn't need to reload as he operates for a short period anyway, 
but unfortunately each shot that he makes jeopardizes his disguise, so after a certain
number of shots, he gets detected and instantaneously killed*/


//constants
#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3

#define EnemyShape		219  //ASCII code of enemy char shape 

struct enemy
{
	int ID;			//Each enemy has a unique ID (sequence number)
	REGION Region;	//Region of this enemy
	int Distance;	//Distance to the castle
	double Health;
	Etype Type;		//PVR, FITR, SHLD_FITR
	int ArrivalTime;
	double FirePower;
	int ReloadPeriod;
	double Priorty;
	bool Reloading;
	int DeathTime;
	int FirstShotTime;
	int Hold;
	int speed;
	enemy* next;      //pointer used for linked list construction
};


//Tower
struct Tower
{
	int TW; //Tower width
	int TL; //Tower Height
	double Health;
	int TowerKillingCapacity; //how many enemies the tower can deal with
	double TowerFirePower;    
	int UnpavedArea;  
	bool Destroyed;
	enemy* Agents = NULL;  //pointer a linked list of agents in each region.
};

struct castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;	//width
	int L;  //Height
	Tower towers[4];	//Castle has 4 towers
};


//Queue struct
struct Bounds
{
	enemy* front;
	enemy* rear;
};

struct Queue
{
	enemy Content;
	Bounds bounds;
};

//storing all the variables needed in stats gathering.
struct Statistics
{
	int Total_inactive;
	int Total_active;
	int Total_killed;
	int lastKilled;
	int FightDelay;
	int KillDelay;
	int Tower_intialHealth;
	int num_Agents;
};


//Functions Prototype

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the game specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

/*A function to partition the castle into regions (A,B,C,D)*/
void DrawRegions(const castle & C);

/*A function to draw the castle and the towers*/
void DrawCastle(const castle & C,int SimulationTime,Statistics &stats);

/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(const enemy& E, int Ypos=0);

/*A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing*/
void DrawEnemies(enemy* enemies[],int size);

/*Student use this function to print his/her message*/
void PrintMsg(char*msg);