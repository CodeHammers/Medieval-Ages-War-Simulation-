#include "file-IO.h"

int main()
{
	Tower* TowerHead = NULL; 
	enemy* PaverHead = NULL; enemy* FigtherHead = NULL; enemy* SHFighterHead = NULL;
	double Constants[3];
	LoadFile(Constants,TowerHead,PaverHead, FigtherHead,SHFighterHead);

	//TEST------------------------------
	/*
	PrintEnemy(PaverHead);
	cout << endl;
	PrintEnemy(FigtherHead);
	cout << endl;
	PrintEnemy(SHFighterHead);
	cout << endl << endl;
	PrintTower(TowerHead);
	for (int i = 0; i < 3; i++) {
		cout << Constants[i] << " ";
	}
	*/
	while(true){
		
		Sleep(1000);
	}
	cout << endl;
	//END OF TEST ------------------------
	return 0;
	
}