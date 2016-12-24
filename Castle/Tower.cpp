#include "EnemyAndTower.h"

/*The function calculates the priority which is the main criteria for 
towers to choose between shielded active enemies 
calculation is done through the formula  specified in the document*/ 
double CalculatePriority(enemy *SHfighter,double Constants[3])
{
	//uses the equation specified in the project description to calc. priority.
	return SHfighter->FirePower/SHfighter->Distance * Constants[0]
	+ Constants[1]/(SHfighter->ReloadPeriod + 1) + SHfighter->Health*Constants[2];
}

//updates the priorities at each time step. 
//Perform any needed one. 
void UpdatePriority(enemy* &SHhead,double Constants[3])
{
	enemy* tempHead=NULL;
	while(SHhead!=NULL){
		SHhead->Priorty=CalculatePriority(SHhead,Constants);
		enemy* temp= SHhead->next;
		insertByPriority(tempHead,SHhead);
		SHhead=temp;
	}
	SHhead=tempHead;
}


//The function inserts the enemy in the list while keeping
//the list sorted by priority 
void insertByPriority(enemy*  &SHhead, enemy* SHfighter)
{
	// Getting rid of the' head pointer change'  cases
	if(SHhead==NULL){
		SHhead=SHfighter;
		SHfighter->next=NULL;
		return;
	}
	if(SHhead->Priorty < SHfighter->Priorty){
		SHfighter->next=SHhead;
		SHhead=SHfighter;
		return;
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
	//he should fall back behind
	prev->next=SHfighter;
	SHfighter->next=NULL;
}


//The function picks first N enemies to shoot for all tower at once
//NO NEED TO CALL IT FOUR TIMES!!!!!!!!
void PickAndShoot(Tower towers[4],enemy* &SHhead,enemy* &regHead, 
				  enemy* &DeadHead,int timeStep,int &RegSize, int &SHsize,Statistics &stats)
{
	enemy* SHiterator=SHhead;
	enemy* regIterator=regHead;
	enemy* shotEnemy=NULL;

	for(int k=0;k<4;k++){
		//resetting values.
		int i = 0; SHiterator = SHhead, regIterator = regHead;

		//loop until the list is empty, or the tower can't shoot anymore, only if the tower isn't destoryed.
		while(SHiterator!=NULL && i< towers[k].TowerKillingCapacity && !towers[i].Destroyed){
			if(SHiterator->Region==65+k){
				if(SHiterator->FirstShotTime==-1)   //-1 denotes, hasn't been shot before.
					SHiterator->FirstShotTime=timeStep;

				SHiterator->Health -=towers[k].TowerFirePower;  //do damage.

				//calls checks if dead.
				shotEnemy=SHiterator; 
				SHiterator = SHiterator->next;
				checkDead(shotEnemy,SHhead,DeadHead,timeStep,SHsize,stats);
				i++; 
			}
			else 
				SHiterator = SHiterator->next;
		}

		//loop until the list is empty, or the tower can't shoot anymore, only if the tower isn't destoryed.
		while(regIterator!=NULL && i< towers[k].TowerKillingCapacity && !towers[i].Destroyed){
			if(regIterator->Region==65+k){
				if(regIterator->FirstShotTime==-1)
					regIterator->FirstShotTime=timeStep; //-1 denotes, hasn't been shot before.

				regIterator->Health -=towers[k].TowerFirePower;

				//calls checks if dead.
				shotEnemy=regIterator; 
				regIterator = regIterator->next;
				checkDead(shotEnemy,regHead,DeadHead,timeStep,RegSize,stats);
				i++;
			}
			else
				regIterator = regIterator->next;
		}
	}
}

void checkDead(enemy* shotEnemy,enemy * &activeHead,enemy* &DeadHead,int timeStep,int &size,Statistics &stats)
{
	if(shotEnemy->Health<=0){
		size--;
		stats.Total_killed++; stats.lastKilled++;
		//preparing to die , gathering statistics.
		shotEnemy->DeathTime=timeStep;
		shotEnemy->Health = 0;
		DetachEnemy(shotEnemy, activeHead);  //detaches the enemy for active list.
		Kill(shotEnemy, DeadHead); //inserts the enemy in the killed list.
	}
}

//Checks for JamesBond detection.
void BondDied(enemy* Bond,enemy* &Deadhead,Statistics &stats,castle &ct)
{
	if (Bond->Health <= 0) {
		stats.num_Agents--;     //we don't need other stats for agent101.
		Bond->Health = 0;
		DetachEnemy(Bond, ct.towers[Bond->Region - 65].Agents);
		Kill(Bond, Deadhead);
	}
}


/*each tower have a pointer that points to the head of a linked list of agents,
the function picks pavers whom are in the same region as JamesBond and shoots them only once
each timestep, each JamesBond is allowed to make only one shot every timestep to avoid
quick detection and stay under cover as much as he could, every shot costs JamesBond to
lose 2 health points, JamesBond's health resembles the time he can stay undercover*/
void JamesBondShoots(enemy* &regFighters,enemy* &Deadhead, castle &ct,Statistics &stats,int timestep,int &Regsize)
{
	enemy* reg = regFighters, *JamesBond = NULL; int R = 65;
	for (int i = 0; i < 4; i++) {
			JamesBond = ct.towers[i].Agents; //the pointer changes every iteration to point to another list.

			while (reg != NULL && JamesBond != NULL) {
				if (reg->Type == PVR && reg->Region == R) {
					if (reg->FirstShotTime == -1)
						reg->FirstShotTime = timestep;

					reg->Health -= JamesBond->FirePower; //shoot paver.
					JamesBond->Health -= 2;  //reduce time undercover.

					enemy* ShotEnemy = reg;
					enemy* DeadBond = JamesBond;

					JamesBond = JamesBond->next; //James shot, move to another James.
					reg = reg->next;   //A paver has been shot, move to another paver.

					//check for dead JamesBond or dead pavers.
					checkDead(ShotEnemy, regFighters, Deadhead, timestep, Regsize, stats);
					BondDied(DeadBond, Deadhead, stats, ct);
				}
				else
					reg = reg->next;  //if the pavers isn't in James's region, check another one.
			}
		R++;
	}
}

//Collective function that calls other minor functions for simplicity when calling in main.
void TowerShoot(enemy* &SHhead,double Constants[3],enemy* &regHead, enemy* &DeadHead
				,int timeStep,Tower towers[4],int &RegSize,int &SHsize,Statistics &stats,castle &ct){
	
	UpdatePriority(SHhead,Constants);
	PickAndShoot(towers,SHhead,regHead,DeadHead,timeStep,RegSize,SHsize,stats);
	JamesBondShoots(regHead,DeadHead,ct,stats,timeStep,RegSize);
}

//checks whether the castle was destoryed or not.
void WhoWon(castle &ct,char& flag,bool& CastleDestroyed)
{
	int counter = 0; 
	for (int i = 0; i < 4; i++) {
		if (ct.towers[i].Destroyed)
			counter++;
	}
	if (counter == 4) {
		CastleDestroyed = true;
		flag = 'E';
	}
	else {
		flag = 'C';
	}
}

//Insert a castle agent into a linked list.
void InsertEnd(enemy* &head, enemy*&data, Statistics &stats)
{
	data->ArrivalTime = 0;  //Castle agents are active all the time, always on the look out.
	data->next = NULL;

	if (head == NULL)
		head = data;
	else {
		enemy* iterator = head;
		while (iterator->next != NULL)
			iterator = iterator->next;
		iterator->next = data;
	}
	stats.num_Agents++;  //variable to keep track of the agents number.
}