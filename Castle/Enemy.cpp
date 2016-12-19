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
	enemy* prev = NULL; enemy* temp = NULL; int count = 0, i = 0;

	/*looping to find all enemies with an arrival time equal to the current 
	  time step, and activate them */
	while (current != NULL) {

		if (current->ArrivalTime != timestep) {
			if (current->ArrivalTime > timestep)  //cause it's sorted.
				break;   //we don't need to continue looping
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
			//arr[i]=&
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

void EnemyToTowerDamage(enemy* RegFigthers, enemy* SHfighters,double* Arr)
{
	double damage = 0.0;
	while (RegFigthers != NULL) {
		if (RegFigthers->Type != PVR && !RegFigthers->Reloading) {
			damage = (1.0 / RegFigthers->Distance)*(RegFigthers->FirePower);

			if (RegFigthers->Region == 65)
				Arr[0] += damage;
			else if (RegFigthers->Region == 66)
				Arr[1] += damage;
			else if (RegFigthers->Region == 67)
				Arr[2] += damage;
			else
				Arr[3] += damage;

			RegFigthers->Reloading = true;
			RegFigthers->Hold = RegFigthers->ReloadPeriod;
		}
		else 
			RegFigthers = RegFigthers->next;
	}

	while (SHfighters != NULL) {
		if (!SHfighters->Reloading) {
			damage = (2.0 / SHfighters->Distance)*(SHfighters->FirePower);

			if (SHfighters->Region == 65)
				Arr[0] += damage;
			else if (SHfighters->Region == 66)
				Arr[1] += damage;
			else if (SHfighters->Region == 67)
				Arr[2] += damage;
			else
				Arr[3] += damage;

			SHfighters->Reloading = true;
			SHfighters->Hold = SHfighters->ReloadPeriod;
			SHfighters = SHfighters->next;
		}
		else
			SHfighters = SHfighters->next;
	}
}

void RelocateEnemies(enemy*&ActiveF, enemy*&ActiveSF, Queue&inACF, Queue&inACSFH,
	                 int Nregion, castle &Castle)
{
	enemy* AF = ActiveF, *ASF = ActiveSF;
	enemy* inF = inACF.bounds.front, *inSF = inACSFH.bounds.front;

	while (inF != NULL) {
		inF->Region = (REGION)(65+Nregion);
		inF = inF->next;
	}

	while (inSF != NULL) {
		inSF->Region = (REGION)(65 + Nregion);
		inSF = inSF->next;
	}
	
	while (AF != NULL) {
		AF->Region = (REGION)(65 + Nregion);
		if (AF->Distance < Castle.towers[Nregion].UnpavedArea)
			AF->Distance = Castle.towers[Nregion].UnpavedArea;
		AF = AF->next;
	}

	while (ASF != NULL) {
		ASF->Region = (REGION)(65 + Nregion);
		if (ASF->Distance < Castle.towers[Nregion].UnpavedArea)
			ASF->Distance = Castle.towers[Nregion].UnpavedArea;
		ASF = ASF->next;
	}
}

void CheckDestruction(castle &Castle, double* Arr, enemy*&ActiveF, 
	                  enemy* &ActiveSF, Queue &inACF, Queue &inACSFH)
{
	for (int i = 0; i<4; i++) {
		Castle.towers[i].Health -= Arr[i];
		if (Castle.towers[i].Health <= 0) {
			Castle.towers[i].Destroyed = true;
			Castle.towers[i].Health = 0;

			int newRegion = (i + 1) % 4;
			for (int i = 0; i < 3; i++) {
				if (Castle.towers[newRegion].Destroyed)
					newRegion++;
				else
					break;
			}

			RelocateEnemies(ActiveF, ActiveSF, inACF, inACSFH, newRegion,Castle);
		}
	}
}


void EnemyShoot(enemy*&AF, enemy*&ASF, Queue&inF, Queue&inSF, castle&Castle)
{
	// Two possible solutions
	//  1 :  double * Arr= new double[4]();
	//  2 : make sure the arr is intialized to zero
	// used the 2nd solution to avoid changing parameter
	double Arr[4];
	Arr[0]=0;Arr[1]=0;Arr[2]=0;Arr[3]=0;
	EnemyToTowerDamage(AF, ASF,Arr);
	CheckDestruction(Castle, Arr, AF, ASF, inF, inSF);
}

void OutputKilled(int FD, int KD, int FT, int KTS, int S,ofstream &out)
{
	out << left << setw(5) << setfill(' ') << KTS << " ";
	out << left << setw(5) << setfill(' ') << S << " ";
	out << left << setw(5) << setfill(' ') << FD << " ";
	out << left << setw(5) << setfill(' ') << KD << " ";
	out << left << setw(5) << setfill(' ') << FT << " ";
	out << endl;
}


void CollectStatistics(enemy* DeadHead,Statistics &stats,ofstream &out)
{
	int FD, KD, FT; enemy* ToBeDeleted = NULL;
	while (DeadHead != NULL) {
		FD = DeadHead->FirstShotTime - DeadHead->ArrivalTime;
		KD = DeadHead->DeathTime - DeadHead->FirstShotTime;
		FT = DeadHead->DeathTime - DeadHead->ArrivalTime;
		stats.FightDelay += FD;
		stats.KillDelay += KD;
		OutputKilled(FD, KD, FT,DeadHead->DeathTime,DeadHead->ID,out);
		ToBeDeleted = DeadHead;
		DeadHead = DeadHead->next;
		delete ToBeDeleted;
	}
}

//should be called simultaneoulsy with the activate function.
void CheckReloadingEnemies(enemy* &ACF, enemy* &ACSF)
{
	enemy* it_ACF = ACF, *it_ACSF = ACSF;

	while (it_ACF != NULL) {
		if (it_ACF->Reloading) {
			if (it_ACF->Hold == 0)
				it_ACF->Reloading = false;
			else
				it_ACF->Hold--;
		}
		it_ACF = it_ACF->next;
	}

	while (it_ACSF != NULL) {
		if (it_ACSF->Reloading) {
			if (it_ACSF->Hold == 0)
				it_ACSF->Reloading = false;
			else
				it_ACSF->Hold--;
		}
		it_ACSF = it_ACSF->next;
	}
}


void Pave(enemy* &ActiveH, castle &Castle)
{
	enemy* ptr = ActiveH;

	while (ptr != NULL)
	{
		if (ptr->Type == PVR && !ptr->Reloading)
		{
			int UnPavedResult = 0;

			if (ptr->Region == 65) {
				getUnPavedAreaResult(Castle.towers[0],ptr);
			}

			else if (ptr->Region == 66) {
				getUnPavedAreaResult(Castle.towers[1],ptr);
			}

			else if (ptr->Region == 67) {
				getUnPavedAreaResult(Castle.towers[2],ptr);
			}

			else{
				getUnPavedAreaResult(Castle.towers[3],ptr);
			}

			ptr->Hold = ptr->ReloadPeriod;
			ptr->Reloading = true;
		}

		if (ptr->Distance>2)
			ptr->Distance-=3;

		ptr = ptr->next;
	}
}

void getUnPavedAreaResult(Tower t, enemy* e)
{
	int UnPavedResult=  e->Distance - e->FirePower;

	if(UnPavedResult<=0)
		t.UnpavedArea=0;
	else
		if(t.UnpavedArea>UnPavedResult)
			t.UnpavedArea -= UnPavedResult;
}

bool IsPaved(enemy* Enemy, castle &Castle)
{
	if (Enemy->Region == 65) {
		if (Enemy->Distance - Castle.towers[0].UnpavedArea > 0)
			return true;
	}

	if (Enemy->Region == 66) {
		if (Enemy->Distance - Castle.towers[1].UnpavedArea > 0)
			return true;
	}

	if (Enemy->Region == 67) {
		if (Enemy->Distance - Castle.towers[2].UnpavedArea > 0)
			return true;
	}

	if (Enemy->Region == 68) {
		if (Enemy->Distance - Castle.towers[3].UnpavedArea > 0)
			return true;
	}

	return false;
}


void MoveEnemies(enemy* &ActiveH, enemy* &ActiveShH, castle &Castle)
{
	enemy*ptr = ActiveH;
	enemy*ptr2 = ActiveShH;

	while (ptr != NULL)
	{
		if (ptr->Type != PVR && ptr->Distance>2)
			if (IsPaved(ptr, Castle))
				ptr->Distance-=2;
		ptr = ptr->next;
	}

	while (ptr2 != NULL)
	{
		if (ptr2->Distance > 2)
			if (IsPaved(ptr2, Castle))
				ptr2->Distance--;
		ptr2 = ptr2->next;
	}
}