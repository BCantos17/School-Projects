/** 
 * Created and modified by Bryan Cantos 2015
 * CSCI 335
 **/

#include <iostream>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

vector<string>				insertfile				( const string & name );
map<string, vector<string>> computeAdjacentWords	( const vector<string> & words );
bool						oneCharOff				( const string & word1, const string & word2 );
void						findAdjWords			(const map<string, vector<string>> & adjWords);

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	string name(argv[1]);						// Insert text file into a string
	vector<string> words = insertfile( name );	// Gets a vector of the all words from the text file

	// Begin count of computeAdjacentWords
	cout << "Testing time to computeAdjacentWords()" << endl;
	const auto begin = chrono::high_resolution_clock::now();

	// Makes a map of all adjacent words
	map<string, vector<string>> adjWords = computeAdjacentWords( words );

	const auto end = chrono::high_resolution_clock::now();
	cout << "Time to computeAdjacentWords is" << endl;
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;

	// Ask user for word to find any adjacent words in a map
	findAdjWords( adjWords );

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

// Computes a map in which the keys are words and values are vectors of words
// that differ in only one character from the corresponding key.
// Uses a quadratic algorithm, but speeds things up a little by
// maintaining an additional map that groups words by their length.
map<string,vector<string>> computeAdjacentWords( const vector<string> & words ) {
	map<string,vector<string>> adjWords;
	map<int,vector<string>> wordsByLength;

	// Group t words by their length
	for( auto & thisWord : words )
		wordsByLength[ thisWord.length( ) ].push_back( thisWord );

	// Work on each group separately
	for( auto & entry : wordsByLength ) {
		const vector<string> & groupsWords = entry.second;

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
void findAdjWords(const map<string, vector<string>> & adjWords) {
	string wordToFind;
	char again;

	cout << "Please enter a word to look for other words that is one character off." << endl;
	cin >> wordToFind;

	cout << "Testing time to find " << wordToFind << "." << endl;
	const auto begin = chrono::high_resolution_clock::now();

	auto itr = adjWords.find( wordToFind );

	if (itr == adjWords.end())
		cout << "Could not find word." << endl;

	else {
		cout << "Word found, now outputting all adjacent words." << endl;
		for(auto & itr2 : itr->second)
			cout << itr2 << " ";
		cout << "" << endl;
	}

	const auto end = chrono::high_resolution_clock::now();
	cout << "Time to look for " << wordToFind << " is" << endl;
	cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms." << endl;
}