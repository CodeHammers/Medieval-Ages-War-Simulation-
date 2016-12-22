#include <iostream>         //use cin, cout, endl
#include <fstream>          //use ifstream
#include <cstdlib>          //use rand
#include <time.h>           //use time for random generation
#include "EnemyAndTower.h"

/*A function to load the input file and extract data*/
void LoadFile(double* Con,castle &Castle ,Queue &regHead,Queue &SFH,Statistics &stats);

/*A function to write all the needed stats in the output file*/
void OutputSimStatus(Statistics &stats, castle &Castle, char whoWon,ofstream &out);

/*A function to print table tabs*/
void PrintTabs(ofstream &out);