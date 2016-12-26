/* Bryan Cantos 2015
 * CSCI 335 Assignment 2*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "TreesFunctions.h"
#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "LazyAvlTree.h"

using namespace std;

int main(int argc, char **argv) {

  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <filename> <queryfilename> <tree-type>" << endl;
    return 0;
  }

  BinarySearchTree<SequenceMap> bst;
  AvlTree<SequenceMap> avl;
  LazyAvlTree<SequenceMap> lazyAvl;
  string fileName = argv[1];     // rebase210.txt
  string queryFileName = argv[2];// sequences.txt
  string paramTree = argv[3];    // BST, AVL, LazyAVL
/*******************************************************************
                      Code for BinarySearchTree
*******************************************************************/
  if (paramTree == "BST") {
    cout << "I will run the BST code " << endl;
    cout << "Adding " << fileName << " to BinarySearchTree" << endl;

    AddToBST(bst, fileName); // Add File to BinarySearchTree
    int bstInsertCount = bst.insertCount();
    int bstTotalNodes = bst.totalNodes();
    double bstAverageDepth = bst.averageDepth();

    cout << "BST calls to insert = " << bstInsertCount << endl;
    cout << "BST total nodes = " << bstTotalNodes << endl;
    cout << "BST average depth = " << bstAverageDepth << endl;
    cout << "BST average depth to ratio log base 2 n = " << bstAverageDepth << 
            "/" << log2(bstTotalNodes) << endl;

    cout << "Searching Binary Tree using " << queryFileName << endl;
    SearchBST(bst, queryFileName); // Use sequences.txt to search the BinarySearchTree
    cout << "BST calls to contains = " << bst.containsCount() << endl;

    RemoveBSTElements(bst, queryFileName); // Use sequence.txt to remove from BinarySearchTree
    cout << "Number of successful removes = " << bst.removeSuccessCount() << endl;
    cout << "BST calls to remove = " << bst.removeCount() << endl;

    /*Repeating totalNodes(), averageDepth, ratio and contains*/

    bst.resetCounter();
    bstTotalNodes = bst.totalNodes();
    bstAverageDepth = bst.averageDepth();
    cout << "BST total nodes = " << bstTotalNodes << endl;
    cout << "BST average depth = " << bstAverageDepth << endl;
    cout << "BST average depth to ratio log base 2 n = " << bstAverageDepth << 
            "/" << log2(bstTotalNodes) << endl;

    cout << "Searching Binary Tree using " << queryFileName << endl;
    SearchBST(bst, queryFileName);
    cout << "BST calls to contains = " << bst.containsCount() << endl;
  }

/*******************************************************************
                      Code for AVLTree
*******************************************************************/

  else if(paramTree == "AVL") {
    cout << "I will run the AVL code " << endl;
    cout << "Adding " << fileName << " to AvlTree" << endl;

    AddToAVL(avl, fileName); // Add to AVL Tree using rebase210.txt
    int avlInsertCount = avl.insertCount();
    int avlTotalNodes = avl.totalNodes();
    double avlAverageDepth = avl.averageDepth();

    cout << "AVL calls to insert = " << avlInsertCount << endl;
    cout << "AVL total nodes = " << avlTotalNodes << endl;
    cout << "AVL average depth = " << avlAverageDepth << endl;
    cout << "AVL average depth to ratio log base 2 n = " << avlAverageDepth << 
            "/" << log2(avlTotalNodes) << endl;

    cout << "Searching AVL Tree using " << queryFileName << endl;
    SearchAVL(avl, queryFileName); // use sequence.txt to search AVL tree
    cout << "AVL calls to contains = " << avl.containsCount() << endl;

    RemoveAVLElements(avl, queryFileName);
    cout << "Number of successful removes = " << avl.removeSuccessCount() << endl;
    cout << "AVL calls to remove = " << avl.removeCount() << endl;

    /*Repeating totalNodes(), averageDepth, ratio and contains*/

    avlTotalNodes = avl.totalNodes();
    avlAverageDepth = avl.averageDepth();

    cout << "AVL total nodes = " << avlTotalNodes << endl;
    cout << "AVL average depth = " << avlAverageDepth << endl;
    cout << "AVL average depth to ratio log base 2 n = " << avlAverageDepth << 
            "/" << log2(avlTotalNodes) << endl;
            
    cout << "Searching AVL Tree using " << queryFileName << endl;
    SearchAVL(avl, queryFileName);
    cout << "AVL calls to contains = " << avl.containsCount() << endl;

  }
  
/*******************************************************************
                      Code for LazyAVLTree
*******************************************************************/
  else if(paramTree == "LazyAVL") {

    cout << "I will run the LazyAVL code " << endl;
    cout << "Adding " << fileName << " to LazyAvlTree" << endl;

    AddToLazyAVL(lazyAvl, fileName);
    int lazyAvlInsertCount = lazyAvl.insertCount();
    int lazyAvlTotalNodes = lazyAvl.totalNodes();
    double lazyAvlAverageDepth = lazyAvl.averageDepth();

    cout << "LazyAVL calls to insert = " << lazyAvlInsertCount << endl;
    cout << "LazyAVL total nodes = " << lazyAvlTotalNodes << endl;
    cout << "LazyAVL average depth = " << lazyAvlAverageDepth << endl;
    cout << "LazyAVL average depth to ratio log base 2 n = " << lazyAvlAverageDepth << 
            "/" << log2(lazyAvlTotalNodes) << endl;

    cout << "Searching Lazy AVL Tree using " << queryFileName << endl;
    SearchLazyAVL(lazyAvl, queryFileName);
    cout << "Lazy AVL calls to contains = " << lazyAvl.containsCount() << endl;

    RemoveLazyAVLElements(lazyAvl, queryFileName);
    cout << "Number of successful removes = " << lazyAvl.removeSuccessCount() << endl;
    cout << "Lazy AVL calls to remove = " << lazyAvl.removeCount() << endl;

    /*Repeating totalNodes(), averageDepth, ratio and contains*/

    lazyAvl.resetCounter();
    lazyAvlTotalNodes = lazyAvl.totalNodes();
    lazyAvlAverageDepth = lazyAvl.averageDepth();

    cout << "Lazy AVL total nodes = " << lazyAvlTotalNodes << endl;
    cout << "Lazy AVL average depth = " << lazyAvlAverageDepth << endl;
    cout << "Lazy AVL average depth to ratio log base 2 n = " << lazyAvlAverageDepth << 
            "/" << log2(lazyAvlTotalNodes) << endl;
            
    cout << "Searching Lazy AVL Tree using " << queryFileName << endl;
    SearchLazyAVL(lazyAvl, queryFileName);
    cout << "Lazy AVL calls to contains = " << lazyAvl.containsCount() << endl;
  }

  /*********************************
  User did not put correct arguments
  **********************************/
  else {
    cout << "Uknown tree type " << paramTree << " (User should provide BST, AVL, or LazyAVL)" << endl;
  }

  return 0;
}