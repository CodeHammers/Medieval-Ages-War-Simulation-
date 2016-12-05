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
//The function calculates the priority which is the main criteria for 
//towers to choose between shielded active enemies 
//calculation is done through the formula  specified in the document  
double CalculatePriority(enemy * SHfighter,double Constants[3])
{
	return SHfighter->FirePower/SHfighter->Distance * Constants[0]
	+ Constants[1]/(SHfighter->ReloadPeriod + 1) + SHfighter->Health*Constants[2];
}
//updates the priorities at each time step 
//Perform any needed one 
void UpdatePriority(enemy* &SHhead,double Constants[3])
{
	enemy* tempHead;
	while(SHhead!=NULL){
		SHhead->Priorty=CalculatePriority(SHhead,Constants);
		insertByPriority(tempHead,SHhead);
		SHhead=SHhead->next;
	}
}
//The function inserts the enemy in the list while keeping
//the list sorted by priority 
void insertByPriority(enemy*  &SHhead, enemy* SHfighter)
{
	// Getting rid of the' head pointer change'  cases
	if(SHhead==NULL){
		SHhead=SHfighter;
	}
	if(SHhead->Priorty < SHfighter->Priorty){
		SHfighter->next=SHhead;
		SHhead=SHfighter;
	}
	enemy* current=SHhead->next;
	enemy* prev=SHhead;
	while(current!=NULL){
		if(current->Priorty < SHfighter->Priorty){
			SHfighter->next= current;
			prev->next=SHfighter;
			return;
		}
		prev=current;
		current=current->next;
	}
	//now current is null , prev is pointing  to the last element in the list
	//existing the loop mean this enemy has the least priority , therefore 
	//he should fall back the lines
	prev->next=SHfighter;
}
//The function picks first N enemies to shoot for all tower at once
//NO NEED TO CALL IT FOUR TIMES!!!!!!!!
void PickAndShoot(Tower* tower,enemy* &SHhead,enemy* &regHead, enemy* &DeadHead)
{
	enemy* SHiterator=SHhead;
	enemy* regIterator=regHead;
	for(int j=0;j<4;j++){
		int i=0;
		while(SHiterator!=NULL&&i< tower->TowerKillingCapacity){
			SHiterator->Health -=tower->TowerFirePower;
			//call checks if dead
			checkDead(SHiterator,SHhead,DeadHead);
			SHiterator=SHiterator->next;
			i++;
		}
		while(regIterator!=NULL&&i< tower->TowerKillingCapacity){
			regIterator->Health -=tower->TowerFirePower;
			//call checks if dead
			checkDead(regIterator,regHead,DeadHead);
			regIterator=regIterator->next;
			i++;
		}
		tower=tower->next;
	}
}

void checkDead(enemy* shotEnemy,enemy * &activeHead,enemy* &DeadHead)
{
	if(shotEnemy->Health<=0){
		//preparing to die , gathering statistics
		DetachEnemy(shotEnemy, activeHead);
		//Die,Dog!
		Kill(shotEnemy, DeadHead);
	}
}