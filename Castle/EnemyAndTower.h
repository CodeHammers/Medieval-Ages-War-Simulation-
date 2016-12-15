#include <iostream>          //use cin, cout, endl
#include <iomanip>           //setw(), setfill(), alligment operators
#include <fstream>
#include "utility.h"
using namespace std;

/*A function to insert a tower node into the towers list*/
bool InsertTower(Tower* &towerH, double TH, int TKC , double FP);

/*A function to enqueue an enemy in the queue*/
void Enqueue(Queue &queue, enemy* &data);

/*A function to check if the queue is empty or not*/
bool IsEmpty(Queue &queue);

/*A function to kill an enemy, move it from active to dead */
void Kill(enemy* killed, enemy* &DeadH);

/*A function to search for a randomly selected enemy*/
enemy* SearchEnemy(enemy* ActiveHead, int index);

/*A function to activate all enemies with arrival time matching the timestep*/
void Activate(Queue &inactiveH, enemy* &activeH, int timestep,int& counter);

/*A function to print all region detials*/
void printEnemyByRegion(enemy* active1, enemy* active2, enemy* dead,int act,int D);

/*A function used by the prev. func. to print all node's data*/
void printRegion(enemy * list, int region);

/*A function to detach a node from a list without deleting the node*/
void DetachEnemy(enemy* ToBeDeleted, enemy* &ActiveH);

/*A function to update the enemy priorities   */ 
void UpdatePriority(enemy* &SHhead,double Constants[3]);

/*A function to calculate priority according to the formula specified in the document   */
double CalculatePriority(enemy * SHfighter,double Constants[3]);

/* A function to re-sort the list according to new priority values */
void insertByPriority(enemy*  &SHhead, enemy* SHfighter);

/*picks N enemies for each tower and shoots them */
void PickAndShoot(Tower towers[4],enemy* &SHhead,enemy* &regHead, 
				  enemy* &DeadHead,int timeStep,int &RegSize, int &SHsize);

/* moves shotEnemy to dead list (if health <= zero) + gathering statistics */
void checkDead(enemy* shotEnemy, enemy * &activeHead, enemy* &DeadHead,int timeStep,int &size);

void EnemyToTowerDamage(enemy* RegFigthers, enemy* SHfighters, double* Arr);

void RelocateEnemies(enemy*&ActiveF, enemy*&ActiveSF, Queue&inACF, Queue&inACSFH,
	int Nregion, castle &Castle);

void CheckDestruction(castle &Castle, double* Arr, enemy*&ActiveF,
	enemy* &ActiveSF, Queue &inACF, Queue &inACSFH);

void EnemyShoot(enemy*&AF, enemy*&ASF, Queue&inF, Queue&inSF, castle&Castle);

void OutputKilled(int FD, int KD, int FT, int KTS, int S, ofstream &out);

void CollectStatistics(enemy* DeadHead, Statistics &stats, ofstream &out);

void CheckReloadingEnemies(enemy* &ACF, enemy* &ACSF);

void Pave(enemy* &ActiveH, castle &Castle);

bool IsPaved(enemy* Enemy, castle &Castle);

void MoveEnemies(enemy* &ActiveH, enemy* &ActiveShH, castle &Castle);

void TowerShoot(enemy* &SHhead,double Constants[3],enemy* &regHead
				, enemy* &DeadHead,int timeStep,Tower towers[4],int &RegSize,int &SHsize);

void getUnPavedAreaResult(Tower t, enemy *e );