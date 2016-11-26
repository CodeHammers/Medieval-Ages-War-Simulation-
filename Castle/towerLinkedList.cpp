#include "towerLinkedList.h"

bool InsertTower(Tower* &towerH, double TH, int TKC , double FP)
{

	Tower* tower = new Tower;
	tower->Health = TH;
	tower->TowerKillingCapacity = TKC;
	tower->TowerFirePower = FP;
	tower->UnpavedArea = 30;
	tower->next = NULL;

	if (towerH == NULL) {
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