#include <iostream>          //use cin, cout, endl
#include<iomanip>            //setw(), setfill(), alligment operators
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