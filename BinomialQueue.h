#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include "MyHashMap.h"
#include "dsexceptions.h"
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
  public:
    BinomialQueue( ) : theTrees( DEFAULT_TREES )
    {
        for( auto & root : theTrees )
          root = nullptr;
        currentSize = 0;
    }

    BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
      { 
        theTrees[ 0 ] = new BinomialNode{ item, nullptr, nullptr, nullptr }; 
      }

    BinomialQueue( const BinomialQueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    { 
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
    }

    BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    { 
    }

    ~BinomialQueue( )
      { makeEmpty( ); }

    
    /**
     * Deep copy.
     */
    BinomialQueue & operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    BinomialQueue & operator=( BinomialQueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }
    
    /**
     * Return true if empty; false otherwise.
     */
    bool isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        return theTrees[ findMinIndex( ) ]->element;
    }
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( const Comparable & x )
      { 
        BinomialQueue oneItem{ x }; 
        merge( oneItem );
      }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( Comparable && x )
      { 
        BinomialQueue oneItem{ std::move( x ) }; 
        merge( oneItem );
      }
    
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        Comparable x;
        hashPointer.remove( findMin() );
        deleteMin( x );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;

        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }

        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
        hashPointer.makeEmpty();
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
    void merge( BinomialQueue & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
            return;
          counter++;

        for(int i = 0; i < rhs.theTrees.size(); ++i){
          insertHash( rhs.theTrees[i] );
          counter+=2;
        }

        currentSize += rhs.currentSize;
        counter++;

        if( currentSize > capacity( ) )
        {
            int oldNumTrees = theTrees.size( );
            int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            counter+=3;
            theTrees.resize( newNumTrees );
            for( int i = oldNumTrees; i < newNumTrees; ++i ){
                theTrees[ i ] = nullptr;
                counter+=2;
              }
        }

        BinomialNode *carry = nullptr;
        counter++;
        for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {   
            counter++;
            BinomialNode *t1 = theTrees[ i ];
            counter++;
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;
            counter++;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;
            counter+=3;

            switch( whichCase )
            {
              case 0: /* No trees */
              case 1: /* Only this */
                break;
              case 2: /* Only rhs */
                theTrees[ i ] = t2;
                rhs.theTrees[ i ] = nullptr;
                counter+=2;
                break;
              case 4: /* Only carry */
                theTrees[ i ] = carry;
                carry = nullptr;
                counter+=2;
                break;
              case 3: /* this and rhs */
                carry = combineTrees( t1, t2 );
                theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
                counter+=2;
                break;
              case 5: /* this and carry */
                carry = combineTrees( t1, carry );
                theTrees[ i ] = nullptr;
                counter+=2;
                break;
              case 6: /* rhs and carry */
                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = nullptr;
                counter=+2;
                break;
              case 7: /* All three */
                theTrees[ i ] = carry;
                carry = combineTrees( t1, t2 );
                rhs.theTrees[ i ] = nullptr;
                counter+=3;
                break;
            }

              
        }

        for( auto & root : theTrees ){
          if( root != nullptr )
            root->parent = nullptr;
          counter+=3;
        }

        for( auto & root : rhs.theTrees )
        {
            root = nullptr;
            counter+=2;
          }
        rhs.currentSize = 0;
        counter++;
        
    }

    bool remove( const Comparable & item )
    {
        if ( !hashPointer.contains( item ) )
          return false; 


        int index = findIndex( hashPointer[ item ] );

        // Moves the selected item to the top of the tree
        BinomialNode *deletedTree = percolateUp( hashPointer[ item ] );
        
        

        BinomialNode *oldRoot = deletedTree;
        deletedTree = deletedTree->leftChild;
        oldRoot = nullptr;
        delete oldRoot;
        hashPointer.remove( item );

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( index );
        deletedQueue.currentSize = ( 1 << index ) - 1;

        for( int j = index - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }
        
        // Construct H'
        theTrees[ index ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );

        return true;
    }

    void testFind(Comparable item )
    {
      BinomialNode * node = find( item );
      if( node == nullptr)
        cout << "find( " << item << " ) " <<  " returns nullptr." << endl;
      else
        cout << "The string you entered is in the BinomialQueue and BinomialNode->element gives " << node->element << endl;
    }

    int totalCounter()
    {
      return counter;
    }


  private:
    struct BinomialNode
    {
        Comparable    element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        BinomialNode *parent;

        BinomialNode( const Comparable & e, BinomialNode *lt, BinomialNode *rt, BinomialNode *p )
          : element{ e }, leftChild{ lt }, nextSibling{ rt }, parent{ p } { }
        
        BinomialNode( Comparable && e, BinomialNode *lt, BinomialNode *rt, BinomialNode *p )
          : element{ std::move( e ) }, leftChild{ lt }, nextSibling{ rt }, parent{ p } { }
    };

    const static int DEFAULT_TREES = 1;

    vector<BinomialNode *> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue
    MyHashMap<Comparable, BinomialNode*> hashPointer{100};
    mutable int counter = 0;
    
    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findMinIndex( ) const
    {
        int i;
        int minIndex;

        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        for( minIndex = i; i < theTrees.size( ); ++i )
            
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->element < theTrees[ minIndex ]->element ){
                minIndex = i;
            }

        return minIndex;
    }

    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findIndex( BinomialNode * &t ) const
    {
        int index;
        BinomialNode *top = t;
        while( top->parent != nullptr )
          top = top->parent;

        for( int i = 0; i < theTrees.size(); ++i )
            if( theTrees[ i ] != nullptr)
              if( theTrees[ i ] == top )
                index = i;

        return index;
    }

    /**
     * Return the capacity.
     */
    int capacity( ) const
      { return ( 1 << theTrees.size( ) ) - 1; }

    /**
     * Return the result of merging equal-sized t1 and t2.
     */
    BinomialNode * combineTrees( BinomialNode *t1, BinomialNode *t2 )
    {
        if( t2->element < t1->element )
            return combineTrees( t2, t1 );
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        t2->parent = t1;
        return t1;
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    void makeEmpty( BinomialNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            t = nullptr;
            delete t;
            
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinomialNode * clone( BinomialNode * t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinomialNode{ t->element, clone( t->leftChild ), clone( t->nextSibling ), clone( t->parent ) };
    }

    /**
     * Internal method to insert node into the hash table
     */
    void insertHash( BinomialNode * & t )
    {
      if( t == nullptr )
        return;

      hashPointer[ t->element ] = t;
      insertHash( t->leftChild );
      insertHash( t->nextSibling );
    }

    /**
     * Internal method to find the node of a key
     */
    BinomialNode * find( const Comparable & item )
    {
      if ( hashPointer.contains( item ) )
          return hashPointer[ item ];
      else 
          return nullptr;
    }

    /**
     * Internal method to percolate a node to the top of a tree
     */
    BinomialNode * percolateUp( BinomialNode * &t )
    {
      if( t->parent == nullptr )
        return t;

      Comparable oldElement = t->element;      
      hashPointer[ t->element ] = t->parent;
      hashPointer[ t->parent->element ] = t;
      t->element = t->parent->element;
      t->parent->element = oldElement;


      return percolateUp( t->parent );
    }
};

#endif