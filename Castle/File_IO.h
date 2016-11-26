#include <iostream>         //use cin, cout, endl
#include <fstream>          //use ifstream
#include <cstdlib>          //use rand
#include <time.h>           //use time for random generation
#include "EnemyAndTower.h"

/*A function to load the input file and extract data*/
void LoadFile(double* Con,Tower*&THead ,Queue &regHead,Queue &SFH);