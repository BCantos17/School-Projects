/* Bryan Cantos 2015
   CSCI 335 Assignment 2*/

#include <iostream>
#include "TreesFunctions.h"
#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "LazyAvlTree.h"

using namespace std;

int main(int argc, char **argv) {
	/*End program if there isn't 3 arugments*/
	if (argc != 3) {
    	cout << "Usage: " << argv[0] << " <filename> <tree-type>" << endl;
    	return 0;
  	}

	string fileName(argv[1]); //rebase210.txt
	string paramTree(argv[2]); //BST, AVL or Lazy AVL
	string sequenceKey;  //User inputs key to search for

	cout << "Input filename is " << fileName << endl;

/*******************************************************************
                      Code for BinarySearchTree
*******************************************************************/
	if (paramTree == "BST") {
    	cout << "I will run the BST code" << endl;
    	BinarySearchTree<SequenceMap> bst;
    	AddToBST(bst, fileName);
    	cout << "Added file to BST." << endl;
    	cout << "Please enter the recognition sequence." << endl;
    	cin >> sequenceKey;

    	if(bst.contains(sequenceKey)) {
    		cout << "Enzyme acronym in ";
    		bst.printNode(sequenceKey);
    	}
    	else
    		cout << "Recognition Sequence not in tree." << endl;

/*******************************************************************
                      Code for AVLTree
*******************************************************************/
  	}
  	else if (paramTree == "AVL") {
    	cout << "I will run the AVL code" << endl;
    	AvlTree<SequenceMap> avl;
    	AddToAVL(avl, fileName);
    	cout << "Added file to AVL." << endl;
    	cout << "Please enter the recognition sequence." << endl;
    	cin >> sequenceKey;
    	
		if(avl.contains(sequenceKey)) {
    		cout << "Enzyme acronym in ";
    		avl.printNode(sequenceKey);
    	}
    	else
    		cout << "Recognition Sequence not in tree." << endl;
  	}  

/*******************************************************************
                      Code for LazyAVLTree
*******************************************************************/
  	else if (paramTree == "LazyAVL") {
    	cout << "I will run the Lazy AVL code" << endl;
    	LazyAvlTree<SequenceMap> lazyAvl;
    	AddToLazyAVL(lazyAvl, fileName);
    	cout << "Added file to Lazy AVL." << endl;
    	cout << "Please enter the recognition sequence." << endl;
    	cin >> sequenceKey;

    	if(lazyAvl.contains(sequenceKey)) {
    		cout << "Enzyme acronym in ";
    		lazyAvl.printNode(sequenceKey);
    	}
    	else
    		cout << "Recognition Sequence not in tree." << endl;
  	} 
  	else
    	cout << "Uknown tree type " << paramTree << " (User should provide BST, AVL, or LazyAVL)" << endl;

	return 0;
}