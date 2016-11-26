#include <iostream>
#include <fstream>
#include "utility.h"

using namespace std;
void LoadFile(double* Con , Tower*&THead , enemy*&PH , enemy*&FH, enemy*& SFH)
{

	int Index, T, ArrivalTime, ReloadPeriod, TowerHit;
	double Health, FirePower, TowerHealth, TowerFireP; char R;
	Etype Type; REGION Region;
	ifstream input("simulation input.txt", ios::in);
	if (!input.is_open()) {
		cout << "Error : input file is not found " << endl;
		return;
	}

	input >> TowerHealth >> TowerHit >> TowerFireP;
	for (int i = 0; i < 4; i++) {
		if (!InsertTower(THead, TowerHealth, TowerHit, TowerFireP)) {
			cout << "Error while inserting a tower node, check insert tower function " << endl;
			return;
		}
	}

	for (int i = 0; i < 3; i++) {
		input >> Con[i];
	}

	input >> Index; 
	while (Index != -1) {

		input>>T >> ArrivalTime >> Health >> FirePower >> ReloadPeriod >> R;
		Type = static_cast<Etype>(T);
		Region = static_cast<REGION>(R);
		
		if (Type == PVR) {
			if (!InsertEnemy(PH, Index, Type, ArrivalTime, Health, FirePower, ReloadPeriod, Region)) {
				cout << "Error while inserting an Paver node, check insert enemy function " << endl;
				return;
			}
		}

		else if (Type == FITR) {
			if (!InsertEnemy(FH, Index, Type, ArrivalTime, Health, FirePower, ReloadPeriod, Region)) {
				cout << "Error while inserting a Fighter node, check insert enemy function " << endl;
				return;
			}
		}

		else if (Type == SHLD_FITR) {
			if (!InsertEnemy(SFH, Index, Type, ArrivalTime, Health, FirePower, ReloadPeriod, Region)) {
				cout << "Error while inserting a Shielded Fighter node, check insert enemy function " << endl;
				return;
			}
		}

		input >> Index;
	}
	input.close();
}