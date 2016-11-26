#include <iostream>
#include <fstream>
#include "utility.h"

using namespace std;

bool InsertEnemy(enemy*& enemyH,int ID, Etype TYP, int T, double H, double FP, int RP, REGION R)
{

	enemy* Enemy = new enemy;
	Enemy->ID = ID;
	Enemy->Type = TYP;
	Enemy->ArrivalTime = T;
	Enemy->Health = H;
	Enemy->FirePower = FP;
	Enemy->ReloadPeriod = RP;
	Enemy->Region = R;
	Enemy->next = NULL;

	if (enemyH == NULL) {
		enemyH = Enemy;
		return true;
	}
	else {
		enemy* iterator = enemyH;

		while (iterator->next != NULL) {
			iterator = iterator->next;
		}

		iterator->next = Enemy;
		return true;
	}
	return false;
}


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

