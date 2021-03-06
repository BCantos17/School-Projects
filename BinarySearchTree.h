/* Modified by Bryan Cantos 2015
 * CSCI 335 Assignment 2*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// void printNode( x )    --> Print node
// int insertCount( )     --> Return insertCounter
// int removeCount( )     --> Return removeCounter
// int containsCount( )   --> Return containsCounter
// int totalNodes( )      --> Return total number of nodes
// double averageDepth( ) --> Return the average depth of the tree
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }, insertCounter{ 0 }, removeCounter{ 0 }, 
                    removeSuccess { 0 }, containsCounter { 0 }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }, insertCounter{ 0 }, removeCounter{ 0 }, 
                    removeSuccess { 0 }, containsCounter { 0 }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }, insertCounter{ 0 }, removeCounter{ 0 }, 
                    removeSuccess { 0 }, containsCounter { 0 }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Print the node being search for.
     */
    void printNode( const Comparable & x, ostream & out = cout ) const
    {
        printNode( x, root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    bool remove( const Comparable & x )
    {
        remove( x, root );
    }

    /**
    *  Return insertCounter
    */
    int insertCount()
    {
        return insertCounter;
    }

    /**
    *  Return removeCounter
    */
    int removeCount()
    {
        containsCounter = 0;
        return removeCounter;
    }

    /**
    *  Return containsCounter
    */
    int containsCount()
    {
        return containsCounter;
    }

    /**
    *  Finds the total number of nodes in the tree
    */
    int totalNodes()
    {
        return totalNodes(root);
    }

    /**
    *  Finds the average depth of the tree
    */
    double averageDepth() const
    {
        int numOfNodes = totalNodes(root);
        int depthCounter = 0;
        return sumDepth(root, depthCounter) / numOfNodes;
    }

    /**
    *  Returns number of success removes
    */
    int removeSuccessCount()
    {
        return removeSuccess;
    }

    /**
    *  Reset Counters
    */
    int resetCounter()
    {
        insertCounter = 0;
        removeCounter = 0;
        removeSuccess = 0;
        containsCounter = 0;
    }

  private:
    
    mutable int insertCounter   = 0;
    mutable int removeCounter   = 0;
    mutable int removeSuccess = 0;
    mutable int containsCounter = 0;

    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        insertCounter++;
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );

        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);  // Merge
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        insertCounter++;

        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )

            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);  // Merge;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    bool remove( const Comparable & x, BinaryNode * & t )
    {
        removeCounter++;

        if( t == nullptr )
            return false;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            removeSuccess++;
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            return true;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        containsCounter++;

        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else //if( t->element == x )
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to print a node.
     */
    void printNode( const Comparable & x, BinaryNode *t, ostream & out ) const
    {
        if( t == nullptr )
            out << "Recognition Sequence not in tree.";
        else if( x < t->element )
            printNode( x, t->left, out );
        else if( t->element < x )
            printNode( x, t->right, out );
        else
            out << t->element;    // Match
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }

    /**
     * Internal method to find total number of nodes
     */
    int totalNodes( BinaryNode *t ) const
    {
        if (t == nullptr)
            return 0;
        else
            return 1 + totalNodes(t->left) + totalNodes(t->right);
    }

    /**
     * Internal method to get the sum of total depth of tree
     */
    double sumDepth( BinaryNode *t, int depthCounter ) const
    {
        if (t == nullptr)
            return 0;
        else
            return depthCounter + sumDepth( t->left, depthCounter + 1 ) 
                                + sumDepth( t->right, depthCounter + 1 );
    }
};

#endif