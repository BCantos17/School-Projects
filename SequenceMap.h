// Bryan Cantos 2015
// CSCI 335 Assignment 2

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SequenceMap{
public:
	SequenceMap    (); 												/*Construtor*/
	SequenceMap    (const string & aKey); 							/*One parameter constructor*/
	SequenceMap    (const string & aKey, const string & anElement); /*Two parameter constructor*/
	bool operator< (const SequenceMap & rightSide) const; 			/*Less than operator*/
	bool operator==(const SequenceMap & rightSide) const;			/*Equal to operator*/
	void Merge     (const SequenceMap & other); 					/*Merge Function*/
	void Replace   (const string & aKey, const string & anElement); /*Replace function*/

private:
	string key; 			 /*The recognition sequence of the DNA*/
	vector<string> elements; /*All possible enzyme acronym that corresponds to the recognition sequence*/ 
	friend ostream& operator<<(ostream& output, const SequenceMap & rightSide); /*Overloads the ostream functuin*/
};

#include "SequenceMap.cpp"
#endif 