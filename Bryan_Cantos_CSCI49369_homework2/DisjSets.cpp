/* 
** Modified by Bryan Cantos
** Class CSCI 49369
*/

#include "DisjSets.h"

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets( int numElements )
{
    array1 = new int[ numElements ];
    array2 = new int[ numElements ];
    for(int i = 0; i < numElements; i++){
        array1[i] = i;
        array2[i] = 1;
    }
}

/**
 * Deconstruct the disjoint sets object.
 */
DisjSets::~DisjSets()
{
    delete [] array1;
    delete [] array2;
}

/**
 * Union two disjoint sets.
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
void DisjSets::unionSets( int root1, int root2 )
{   
    int i = find( root1 );
    int j = find( root2 );
    if (i == j) return;
        
    if(array2[i] < array2[j])
    { 
        array1[i] = j; 
        array2[j] += array2[i]; 
    } 
    else 
    { 
        array1[j] = i; 
        array2[i] += array2[j]; 
    }
}


/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSets::find( int x )
{
    int root = x;
    while (root != array1[root])
        root = array1[root];
    while (x != root) {
        int newX = array1[x];
        array1[x] = root;
        x = newX;
    }
    return root;
}


/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
/*int DisjSets::find( int x )
{
    if( s[ x ] < 0 )
        return x;
    else
        return s[ x ] = find( s[ x ] );
}*/
