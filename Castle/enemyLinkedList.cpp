#include "enemyLinkedList.h"

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
void PrintEnemy(enemy*head) {
	cout << "list is : ";
	while (head != NULL) {
		cout << head->ID << " ";
		cout << head->Type << " ";
		cout << head->ArrivalTime << " ";
		cout << head->Health << " ";
		cout << head->FirePower << " ";
		cout << head->ReloadPeriod<< " ";
		cout << head->Region << " ";
		head = head->next;
	}
	cout << endl;
}

void PrintTower(Tower*head) {
	cout << "list is : " << endl;
	while (head != NULL) {
		cout << head->Health << " ";
		cout << head->TowerKillingCapacity << " ";
		cout << head->TowerFirePower << " ";
		cout << head->UnpavedArea << " ";
		head = head->next;
		cout << endl;
	}
	cout << endl;
}