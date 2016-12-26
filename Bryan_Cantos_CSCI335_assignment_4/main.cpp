#include <iostream>
#include <string>
#include "MyHashMap.h"
#include "BinomialQueue.h"
#include <fstream>
using namespace std;

BinomialQueue<string> insertfile( const string & name );
void getCounter					( BinomialQueue<string> & bq );
void testDeleteMin				( BinomialQueue<string> & bq );
void testFind					( BinomialQueue<string> & bq );
void testRemove					( BinomialQueue<string> & bq );

main() {

	BinomialQueue<string> bq = insertfile( "words.txt" );

	getCounter( bq );
	testDeleteMin( bq );
	testFind( bq );
	testRemove( bq );

	return 0;
}

// Inserts all he words from words.txt file into a vector
BinomialQueue<string> insertfile( const string & name ) {
	ifstream file(name);
	if(file.fail()) {
		cout << "Could not open file." << endl;
		exit(1);
	}

	BinomialQueue<string> words;
	string oneWord;

	while(file >> oneWord)
		words.insert( oneWord );
 	
	return words;
}

void getCounter( BinomialQueue<string> & bq ) {
	cout << "Printing out the total number of assignments and comparisons done during insert." << endl;
	cout << bq.totalCounter() << endl;
}

void testDeleteMin( BinomialQueue<string> & bq ) {
	cout << "Testing deleteMin() and finding the minimum values after each deleteMin()." << endl;
	for(int i = 0; i < 10; ++i){
		cout << bq.findMin() << endl;
		bq.deleteMin();
	}
	cout << bq.findMin() << endl;
}

void testFind( BinomialQueue<string> & bq ) {
	cout << "Testing the private function find( key )" << endl;
	string input;
	cout << "Please enter a string you would like to find in the BinomialQueue" << endl;
	cin >> input;
	bq.testFind( input );
}

void testRemove( BinomialQueue<string> & bq ) {
	cout << "Testing remove( key )" << endl;

	for( int i = 0; i < 5; ++i ) {
		cout << "Please enter a string you wish to remove." << endl;
		string input;
		cin >> input;
		cout << "remove( " << input << " )" << " returns " << bq.remove( input ) << "." << endl;
		cout << "Testing find()." << endl;
		bq.testFind( input );
	}
}