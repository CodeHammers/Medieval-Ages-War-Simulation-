#include "InputLogic.h"
void LoadFile()
{
	//first line of input
	int Thealth;
	int TfirePower;
	int N;
	//second line of input
	float  C1,C2,C3;
	//many lines (one line for each enemy)
	int seqNum;
	int type;
	int arrivalTime;
	int Ehealth;
	int EfirePower;
	int reloadPeroid;
	char region;
	
    //Opens for reading the file ... the file should  be either specified before
    //hand or taken as an input char array(string)
	ifstream input_file( "D:/A karim/others/highlights.txt" );
	//Reading Tower data from file
	input_file>>Thealth>>N>>TfirePower;
	//Reading constants for equation of priority from file
	input_file>>C1>>C2>>C3;
	//Reading enemy data from file
	while(true){
		input_file>>seqNum;
		if(seqNum==-1)
			break;
		input_file>>type>>arrivalTime>>Ehealth>>EfirePower>>reloadPeroid>>reloadPeroid;
		// populate data into structs and lists
	}
}