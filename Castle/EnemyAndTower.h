#include <iostream>          //use cin, cout, endl
#include <iomanip>           //setw(), setfill(), alligment operators
#include <fstream>
#include "utility.h"
using namespace std;

/*A function to enqueue an enemy in the queue*/
void Enqueue(Queue &queue, enemy* &data,Statistics &stats);

/*A function to check if the queue is empty or not*/
bool IsEmpty(Queue &queue);

/*A function to kill an enemy, move it from active to dead */
void Kill(enemy* killed, enemy* &DeadH);

/*A function to search for a randomly selected enemy*/
enemy* SearchEnemy(enemy* ActiveHead, int index);

/*A function to activate all enemies with arrival time matching the timestep*/
void Activate(Queue &inactiveH, enemy* &activeH, int timestep,int& counter,Statistics &stats);

/*A function to print all region detials*/
void printEnemyByRegion(enemy* active1, enemy* active2, enemy* dead,int act,int D);

/*A function used by the prev. func. to print all node's data*/
void printRegion(enemy * list, int region);

/*A function to detach a node from a list without deleting the node*/
void DetachEnemy(enemy* ToBeDeleted, enemy* &ActiveH);

/*A function to update the enemy priorities   */ 
void UpdatePriority(enemy* &SHhead,double Constants[3]);

/*A function to calculate priority according to the formula specified in the document*/
double CalculatePriority(enemy * SHfighter,double Constants[3]);

/*A function to re-sort the list according to new priority values*/
void insertByPriority(enemy*  &SHhead, enemy* SHfighter);

/*A function to pick N enemies for each tower and shoots them*/
void PickAndShoot(Tower towers[4],enemy* &SHhead,enemy* &regHead, 
				  enemy* &DeadHead,int timeStep,int &RegSize, int &SHsize,Statistics &stats);

/*A function that checks for dead enemies and extract stats*/
void checkDead(enemy* shotEnemy, enemy * &activeHead, enemy* &DeadHead,int timeStep,int &size,Statistics& stats);

/*A function that calculate the damage done by certain enemy to a tower*/
void EnemyToTowerDamage(enemy* RegFigthers, enemy* SHfighters, double* Arr);

/*A function to realocate enemies in case of a tower destruction*/
void RelocateEnemies(enemy*&ActiveF, enemy*&ActiveSF, Queue&inACF, Queue&inACSFH,
	                 int Nregion, castle &Castle,int oldRegion);

/*A function to check whether is destoryed or not*/
void CheckDestruction(castle &Castle, double* Arr, enemy*&ActiveF,
	                  enemy* &ActiveSF, Queue &inACF, Queue &inACSFH);

/*A function to call all operations needed for the enemy to shoot a tower*/
void EnemyShoot(enemy*&AF, enemy*&ASF, Queue&inF, Queue&inSF, castle&Castle);

/*A function to output the data of the killed enemies before deleting them*/
void OutputKilled(int FD, int KD, int FT, int KTS, int S, ofstream &out);

/*A function to extract stats from dead enemies before deleting them*/
void CollectStatistics(enemy* DeadHead, Statistics &stats, ofstream &out);

/*A fcuntion that checks wether the reloading period of a reloading enemy ended or not*/
void CheckReloadingEnemies(enemy* &ACF, enemy* &ACSF);

/*A function to enable pavers to pave*/
void Pave(enemy* &ActiveH, castle &Castle);

/*A function to the whether an enemy's movement range is paved or not*/
bool IsPaved(enemy* Enemy, castle &Castle);

/*A function to move enemies according to their variant speeds*/
void MoveEnemies(enemy* &ActiveH, enemy* &ActiveShH, castle &Castle);

/*A function that completes all operations associated with shooting the tower*/
void TowerShoot(enemy* &SHhead,double Constants[3],enemy* &regHead
				, enemy* &DeadHead,int timeStep,Tower towers[4],
	            int &RegSize,int &SHsize,Statistics &stats,castle &ct);

/*A function to update the unpaved area in a tower*/
void getUnPavedAreaResult(Tower &t, enemy *e );

/*A function to determine who won the simulation*/
void WhoWon(castle &ct, char& flag, bool& CastleDestroyed);

/*A function to make castle agnets shoot pavers only before gettting detected*/
void JamesBondShoots(enemy* &regFighters, enemy* &Deadhead, castle &ct, Statistics &stats, int timestep, int &Regsize);

/*A function to check when the castle agents get detected and killed*/
void BondDied(enemy* Bond, enemy* &Deadhead, Statistics &stats, castle &ct);

/*A function to inserts a node in the end of a linked list*/
void InsertEnd(enemy* &head, enemy*&data,Statistics &stats);