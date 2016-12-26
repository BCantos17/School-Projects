#include <iostream>
#include <cstdlib>
#include <time.h>
#include "QuadraticProbing.h"
using namespace std;

void randomTestProbe();
void userTestProbe();

int main() {
	randomTestProbe();

	cout << "userTestProbe() is commented out, uncomment it test different load factors with different inserts" << endl;
	// User input insertion to make a static load factor for testing.
	//userTestProbe();
	return 0;
}

void randomTestProbe() {
	srand(time(NULL));
	double analysis = 0.05; 		// used to measure the load factors from .05 to 1 by increments of .05
	int size = nextPrime( 1000 ); 	// Size of the HashTable
	int totalItems = 0;				// Number of items in the hash table
	HashTable<int> table;

	for( int i = 0; i < size ; ++i) {
		// insert items
		if(table.insert( rand() % 10000 ) ) {
			totalItems++; // if successful, increment TotalItems
		}

		if( (double)totalItems  / size > analysis){
			cout <<"Number of insert items is " << totalItems << endl;
			cout << "The load factor is " << (double)totalItems  / size << ".";
			cout <<  " Number of probes to insert are " << table.probeCount() << endl;
			analysis += 0.05;
		}
	}

	// Random Searches
	int search;
	cout <<"Doing 10 random searches of table with a load factor of " << (double)totalItems  / size << endl;
	for( int i = 0; i < 10; i++ ) {
		search = rand() % 10000;
		table.contains( search );
		cout <<  "Searching for " << search << " Number of probes are " << table.probeCount() << endl;
	}
}

// Same as randomTestProbe except with a user defined number of insertion
void userTestProbe() {
	srand(time(NULL));
	double analysis = 0.05;
	int size = nextPrime( 1000 ); // Size of the HashTable
	int totalItems = 0;
	int inserts;
	HashTable<int> table;

	cout << "Enter number of insertion to be made" << endl;
	cin >> inserts;

	for( int i = 0; i < inserts ; ++i) {
		if(table.insert( rand() % 10000 ) ) {
			totalItems++;
		}

		if( (double)totalItems  / size > analysis){
			cout <<"Number of insert items is " << totalItems << endl;
			cout << "The load factor is " << (double)totalItems  / size << ".";
			cout <<  " Number of probes to insert are " << table.probeCount() << endl;
			analysis += 0.05;
		}
	}

	int search;
	cout <<"Doing 10 random searches of table with a load factor of " << (double)totalItems  / size << endl;
	for( int i = 0; i < 10; i++ ) {
		search = rand() % 10000;
		table.contains( search );
		cout <<  "Searching for " << search << " Number of probes are " << table.probeCount() << endl;
	}
}