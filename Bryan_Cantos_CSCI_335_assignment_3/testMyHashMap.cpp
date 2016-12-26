/** 
 * Created and modified by Bryan Cantos 2015
 * CSCI 335
 **/

#include <iostream>
#include <cstdlib>
#include "MyHashMap.h"
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

vector<string> 						insertfile				( const string & name );
MyHashMap<string, vector<string>>	computeAdjacentWords	( const vector<string> & words, const int size );
bool								oneCharOff				( const string & word1, const string & word2 );
void								findAdjWords			( const MyHashMap<string, vector<string>> & adjWords );
void 								display 				( const MyHashMap<string, vector<string>> & adjWords);

int main( int argc, char **argv ) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <filename>" << "<size of hash table>" << endl;
		return 1;
	}


	string name(argv[1]);						// Insert text file into a string
	int size = atoi(argv[2]);					// Converts the input argument into int
	vector<string> words = insertfile( name );	// Gets a vector of the all words from the text file

	// Begin count of computeAdjacentWords
	cout << "Testing time to computeAdjacentWords()" << endl;
	const auto begin = chrono::high_resolution_clock::now();

	// Makes a map of all adjacent words
	MyHashMap<string, vector<string>> adjWords = computeAdjacentWords( words, size );

	const auto end = chrono::high_resolution_clock::now();
	cout << "Time to computeAdjacentWords is" << endl;
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;

	// Ask user for word to find any adjacent words in a map
	findAdjWords( adjWords );

	/*************** Display function for personal use *******************************/
	//display( adjWords );

	cout << "display() is inside int main(), uncomment it to use." << endl;

	return 0;
}

// Inserts all he words from words.txt file into a vector
vector<string> insertfile( const string & name ) {
	ifstream file(name);
	if(file.fail()) {
		cout << "Could not open file." << endl;
		exit(1);
	}

	vector<string> words;
	string oneWord;

	while(file >> oneWord)
		words.push_back( oneWord );
 	
	return words;
}

MyHashMap<string,vector<string>> computeAdjacentWords( const vector<string> & words, const int size ) {
	MyHashMap<string, vector<string>> adjWords( size );
	MyHashMap<int, vector<string>> wordsByLength(100000);

	// Group t words by their length
	for( auto & thisWord : words )
		wordsByLength[ thisWord.length( ) ].push_back( thisWord );

	// Work on each group separately
	for( auto entry = wordsByLength.begin(); entry != wordsByLength.end(); ++entry ) {
		const vector<string> & groupsWords = entry->mapped;

		for( int i = 0; i < groupsWords.size( ); ++i )
			for( int j = i + 1; j < groupsWords.size( ); ++j )
				if( oneCharOff( groupsWords[ i ], groupsWords[ j ] ) ) {
					adjWords[ groupsWords[ i ] ].push_back( groupsWords[ j ] );
					adjWords[ groupsWords[ j ] ].push_back( groupsWords[ i ] );
				}
	}

	return adjWords;
}

// Returns true if word1 and word2 are the same length
// and differ in only one character.
bool oneCharOff( const string & word1, const string & word2 ) {
	if( word1.length( ) != word2.length( ) )
		return false;

	int diffs = 0;

	for( int i = 0; i < word1.length( ); ++i )
		if( word1[ i ] != word2[ i ] )
			if( ++diffs > 1 )
				return false;

	return diffs == 1;
}

 // Prompts user to input a word to find in the map.
 // If found, output all adjacent words
void findAdjWords(const MyHashMap<string, vector<string>> & adjWords) {
	string wordToFind;
	char again;

	cout << "Please enter a word to look for other words that is one character off." << endl;
	cin >> wordToFind;

	cout << "Testing time to find " << wordToFind << "." << endl;
	const auto begin = chrono::high_resolution_clock::now();

	if( adjWords.contains( wordToFind ) ) {
		// Gets a vector of the user inputted key
		auto vectorOfWords = adjWords.find( wordToFind );
		
		cout << "Word found, now outputting all adjacent words." << endl;
		cout << wordToFind << " ";
		for(auto & itr : vectorOfWords)
			cout << itr << " ";
		cout << "" << endl;
	}

	else
		cout << "Could not find word." << endl;
	
	const auto end = chrono::high_resolution_clock::now();
	cout << "Time to look for " << wordToFind << " is" << endl;
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;
}

// Displays all the contents in the HashMap in order from beginning to end
void display( const MyHashMap<string, vector<string>> & adjWords)
{
	for( auto itr = adjWords.begin(); itr != adjWords.end(); ++itr ) {
		if( itr->mapped.size() != 0 ){
			cout << itr->element << " ";
			for( auto & itr2 : itr->mapped )
				cout << itr2 << " ";
		}
		if( itr->mapped.size() != 0 )
			cout << "\n";
	}
}