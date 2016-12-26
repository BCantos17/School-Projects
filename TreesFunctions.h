/* Bryan Cantos 2015
 * CSCI 335 Assignment 2*/

#include <fstream>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "LazyAvlTree.h"
#include "SequenceMap.h"

void AddToBST(BinarySearchTree<SequenceMap> & tree, const string & fileName);
void SearchBST(BinarySearchTree<SequenceMap> & tree, const string & queryFileName);
void RemoveBSTElements(BinarySearchTree<SequenceMap> & tree, const string & queryFileName);

void AddToAVL(AvlTree<SequenceMap> & tree, const string & fileName);
void SearchAVL(AvlTree<SequenceMap> & tree, const string & queryFileName);
void RemoveAVLElements(AvlTree<SequenceMap> & tree, const string & queryFileName);

void AddToLazyAVL(LazyAvlTree<SequenceMap> & tree, const string & fileName);
void SearchLazyAVL(LazyAvlTree<SequenceMap> & tree, const string & queryFileName);
void RemoveLazyAVLElements(LazyAvlTree<SequenceMap> & tree, const string & queryFileName);

/*
 * Parses the rebase.txt file into a BinarySearchTree
 */
void AddToBST(BinarySearchTree<SequenceMap> & tree, const string & fileName) {
	ifstream file(fileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	string dummyLine, line, dna, sequence1, sequence2;
	bool firstLine = true;
	SequenceMap map;

	/*Reads through the first 10 lines*/
	for(int i = 0; i < 10; i++)
		getline(file, dummyLine);

	/*Reads through each line and inserts enzyme and sequence into tree*/
	while(getline(file, line)) {

		/*Reads the first enzyme and sequence and inserts into tree*/
	    if(firstLine) {
	    	dna = line.substr(0, 4);
	    	sequence1 = line.substr(5, 7);
	    	map.Replace(sequence1, dna);
	    	tree.insert(map);
	    	firstLine = false;
	    }

	    /*Reads the rest of the text and insert into tree*/
		getline(file, dna, '/');
		getline(file, sequence1, '/');
		getline(file, sequence2, '/');
		map.Replace(sequence1, dna);
		tree.insert(map);
		if(sequence2.length() > 0) {
			map.Replace(sequence2, dna);
			tree.insert(map);
		}
	}
	file.close();
}

/*
 * Searches Tree using Contains
 */
void SearchBST(BinarySearchTree<SequenceMap> & tree, const string & queryFileName) {
	ifstream file(queryFileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	int success = 0;
	string sequence;

	/*Reads each line one by one into sequence*/
	while(file >> sequence){
		if(tree.contains(sequence))
			success++;
	}

	cout << "Number	of successful queries = " << success << endl;
	file.close();
}

/*
 * Remove every other element in sequence.txt
 */
void RemoveBSTElements(BinarySearchTree<SequenceMap> & tree, const string & queryFileName) {
	ifstream file(queryFileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	int success = 0;
	string sequence;

	/*Reads each line one by one into sequence*/
	while(file >> sequence){
		tree.remove(sequence);
		file >> sequence;
	}

	file.close();
}

/*
 * Parses the rebase.txt file into an AvlTree
 */
void AddToAVL(AvlTree<SequenceMap> & tree, const string & fileName) {
	ifstream file(fileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	string dummyLine, line, dna, sequence1, sequence2;
	bool firstLine = true;
	SequenceMap map;

	/*Reads through the first 10 lines*/
	for(int i = 0; i < 10; i++)
		getline(file, dummyLine);

	/*Reads through each line and inserts enzyme and sequence into tree*/
	while(getline(file, line)) {

		/*Reads the first enzyme and sequence and inserts into tree*/
	    if(firstLine) {
	    	dna = line.substr(0, 4);
	    	sequence1 = line.substr(5, 7);
	    	map.Replace(sequence1, dna);
	    	tree.insert(map);
	    	firstLine = false;
	    }

	    /*Reads the rest of the text and insert into tree*/
		getline(file, dna, '/');
		getline(file, sequence1, '/');
		getline(file, sequence2, '/');
		map.Replace(sequence1, dna);
		tree.insert(map);
		if(sequence2.length() > 0) {
			map.Replace(sequence2, dna);
			tree.insert(map);
		}
	}
	file.close();
}

/*
 * Searches Tree using Contains
 */
void SearchAVL(AvlTree<SequenceMap> & tree, const string & queryFileName) {
	ifstream file(queryFileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	int success = 0;
	string sequence;

	/*Reads each line one by one into sequence*/
	while(file >> sequence){
		if(tree.contains(sequence))
			success++;
	}

	cout << "Number	of successful queries = " << success << endl;
	file.close();
}

/*
 * Remove every other element in sequence.txt
 */
void RemoveAVLElements(AvlTree<SequenceMap> & tree, const string & queryFileName) {
	ifstream file(queryFileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	string sequence;

	/*Reads each line one by one into sequence*/
	while(file >> sequence){
		tree.remove(sequence);
		file >> sequence;
		
	}
	file.close();
}

/*
 * Parses the rebase.txt file into a LazyAVLTree
 */

void AddToLazyAVL(LazyAvlTree<SequenceMap> & tree, const string & fileName) {
	ifstream file(fileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	string dummyLine, line, dna, sequence1, sequence2;
	bool firstLine = true;
	SequenceMap map;

	/*Reads through the first 10 lines*/
	for(int i = 0; i < 10; i++)
		getline(file, dummyLine);

	/*Reads through each line and inserts enzyme and sequence into tree*/
	while(getline(file, line)) {

		/*Reads the first enzyme and sequence and inserts into tree*/
	    if(firstLine) {
	    	dna = line.substr(0, 4);
	    	sequence1 = line.substr(5, 7);
	    	map.Replace(sequence1, dna);
	    	tree.insert(map);
	    	firstLine = false;
	    }

	    /*Reads the rest of the text and insert into tree*/
		getline(file, dna, '/');
		getline(file, sequence1, '/');
		getline(file, sequence2, '/');
		map.Replace(sequence1, dna);
		tree.insert(map);
		if(sequence2.length() > 0) {
			map.Replace(sequence2, dna);
			tree.insert(map);
		}
	}
	file.close();
}

/*
 * Searches Tree using Contains
 */
void SearchLazyAVL(LazyAvlTree<SequenceMap> & tree, const string & queryFileName) {
	ifstream file(queryFileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	int success = 0;
	string sequence;

	/*Reads each line one by one into sequence*/
	while(file >> sequence){
		if(tree.contains(sequence))
			success++;
	}

	cout << "Number	of successful queries = " << success << endl;
	file.close();
}

/*
 * Remove every other element in sequence.txt
 */
void RemoveLazyAVLElements(LazyAvlTree<SequenceMap> & tree, const string & queryFileName) {
	ifstream file(queryFileName);
	if(file.fail()) {
		cout << "Failed to open file." << endl;
		exit(1);
	}

	string sequence;

	/*Reads each line one by one into sequence*/
	while(file >> sequence){
		tree.remove(sequence);
		file >> sequence;
	}
	file.close();
}