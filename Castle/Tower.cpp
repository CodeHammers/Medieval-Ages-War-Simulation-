#include "EnemyAndTower.h"

//inserting a tower node in a list.
bool InsertTower(Tower* &towerH, double TH, int TKC , double FP)
{

	Tower* tower = new Tower;  //Allocating memory for the tower node.

	//filling tower data into the node.
	tower->Health = TH;
	tower->TowerKillingCapacity = TKC;
	tower->TowerFirePower = FP;
	tower->UnpavedArea = 30;
	tower->next = NULL;

	if (towerH == NULL) {  //handling insertion at head.
		towerH = tower;
		return true;
	}
	else {

		Tower* iterator = towerH;

		while (iterator->next != NULL) {
			iterator = iterator->next;
		}

		iterator->next = tower;
		return true;
	}

	return false;
}		