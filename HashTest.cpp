#include <iostream>
#include <cstdlib>
#include <time.h>
#include "QuadraticProbing.h"
using namespace std;
int main(){
	HashTable<int> tester;
	double measurement = 0.05;
	int numofElements = 0;
	srand(time(NULL));
	while(numofElements < 1000){
		if(tester.insert(rand() % 10000 + 1)){ //Random number from 1 to 10000, just as a sort of measure
			numofElements++;
		}
		if( static_cast<double>(numofElements)/1009 > measurement){
			//cout << "At load factor: " << static_cast<double>(numofElements)/1009;
			//cout << " the number of searches was: " << tester.returnProbe() << endl;
			//measurement = measurement + 0.05;
		}
	}
	return 0;
}
