#include "EnemyAndTower.h"

void Kill(enemy* killed, enemy* &DeadH)
{
	if (DeadH == NULL) {  //handling the case of an empty list "insertion at head"
		DeadH = killed;
		return;
	}
	else {
		enemy* prev = NULL; enemy* current = DeadH;
		int count = 0;

		while (current != NULL) {
			if (current->Health < killed->Health) { //sorting in ascedning order.
				prev = current; 
				current = current->next;
				count++;
			}
			else {
				if (count == 0) {         //insertion in the beginning.
					killed->next = DeadH;
					DeadH = killed;
					return;
				}
				else {
					prev->next = killed;   //insertion in the middle.
					killed->next = current;
					return;
				}
			}
		}
		prev->next = killed;   //insertion in the end.
		killed->next = NULL;
		return;
	}
}


enemy* SearchEnemy(enemy* ActiveHead, int index)
{
	int i = 1; 
	if (ActiveHead == NULL)   //Handling the case of an empty active list.
		return NULL;
	else {
		enemy* iterator = ActiveHead;
		while (iterator != NULL) {
			if (i == index)         //If we have found the random enemy, return it.
				return iterator;
			else 
				iterator = iterator->next;
			i++;
		}
	}
	return NULL;  //if not found return NULL "just for safety"
}


/*
For each region, print
1. Total number of active enemies and information of each one of them.
2. Total number of killed enemies and information of each one of them.
The killed enemies have to be printed ordered by enemy health.
*/

void printEnemyByRegion(enemy* active1, enemy* active2, enemy* dead,int act,int D) 
{
	cout <<endl<< "Total number of Active enemies = " << act << endl;
	cout << "\nListing Active enemies\n";
	cout << "______________________________________________";
	//ASCII code manipulation.
	for (int i = 65; i<65 + 4; i++) {
		cout << "\nRegion " << (char)('A' + i - 65) << "\n";
		cout << "S     TY     T     H     Pow    Prd    R" << endl;
		printRegion(active1, i);
	}
	cout <<endl<< "Total number of dead enemies = " << D << endl;
	cout << "\nListing dead enemies\n";
	cout << "______________________________________________";
	for (int i = 65; i<65 + 4; i++) {
		cout << "\nRegion " << (char)('A' + i - 65) << "\n";
		cout << "S     TY     T     H     Pow    Prd    R" << endl;
		printRegion(dead, i);
	}
}


void printRegion(enemy * list, int region)
{
	while (list != NULL) {        //handling the case of an empty list.
		if (list->Region == region) {
			cout << left << setw(5) << setfill(' ') << list->ID << " ";
			cout << left << setw(5) << setfill(' ') << list->Type << "  ";
			cout << left << setw(5) << setfill(' ') << list->ArrivalTime << " ";
			cout << left << setw(5) << setfill(' ') << list->Health << " ";
			cout << left << setw(5) << setfill(' ') << list->FirePower << "  ";
			cout << left << setw(5) << setfill(' ') << list->ReloadPeriod << "  ";
			cout << left << setw(5) << setfill(' ') << list->Region << " ";
			cout << endl;
		}
		list = list->next;
	}
}


void MoveFromTo(enemy* &origin, enemy* &destination)
{
	origin->next = NULL;          //detaching the node form its original list 

    //inserting the node at the end of the desetination list
	if (destination == NULL) {   //handling the case of an empty list.
		destination = origin;
		return ;
	}
	else {
		enemy* iterator = destination;

		while (iterator->next != NULL)
			iterator = iterator->next;

		iterator->next = origin;
	}
}


void Activate(Queue &inactiveH, enemy* &activeH, int timestep,int&counter)
{
	enemy* current = inactiveH.bounds.front;
	enemy* prev = NULL; enemy* temp = NULL; int count = 0;

	/*looping to find all enemies with an arrival time equal to the current 
	  time step, and activate them */
	while (current != NULL) {

		if (current->ArrivalTime != timestep) {
			if (current->ArrivalTime > timestep)  //cause it's sorted.
				break;   //we don't to continue looping
			else {
				prev = current;
				current = current->next;
				count++;
			}
		}
		else {
			if (count == 0)   //handling the case of the first node.
				inactiveH.bounds.front = current->next;
			else if (current == inactiveH.bounds.rear) {  //handling the case of
				prev->next = NULL;                        //the last node.
				inactiveH.bounds.rear = prev;
			}
			else
				prev->next = current->next;              //Any other node.

			temp = current->next;
			MoveFromTo(current, activeH);   //Activation enemies.
			counter++;
			current = temp;   //updating current.
		}	
	}
}


void DetachEnemy(enemy* ToBeDeleted, enemy* &ActiveH)
{
	if (ActiveH == NULL)       //handling the case of an empty list.
		return;
	else {
		enemy* prev = NULL;
		enemy* current = ActiveH;
		int count = 0;

		//loop as long as we haven't encountred the node to be detached 
		//and we haven't reached the end of the list.
		while (current != ToBeDeleted && current != NULL) {
			prev = current; 
			current = current->next;
			count++;
		}

		if (count == 0)    //if the node to be detachd is at the beginning.
			ActiveH = current->next;
		else
			prev->next = current->next;  //Any other position.
	}
	ToBeDeleted->next = NULL;
}