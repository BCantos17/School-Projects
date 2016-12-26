// Bryan Cantos -- Assignment 1 CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Ioannis Stamos.
// Modfified by Bryan Cantos

/** Listing 1-1.
    @file setunterface.h */
#ifndef TEACH_CSCI235_BAGADT_BAGINTERFACE_H_
#define TEACH_CSCI235_BAGADT_BAGINTERFACE_H_

#include <vector>
#include <cstddef>
using namespace std;

template<class ItemType>
class setinterface
{
public:
   /** Gets the current number of entries in this set.
    @return The integer number of entries currently in the set. */
   virtual int GetCurrentSize() const = 0;
   
   /** Sees whether this set is empty.
    @return True if the set is empty, or false if not. */
   virtual bool IsEmpty() const = 0;
   
   /** Adds a new entry to this set.
    @post  If successful, newEntry is stored in the set and
       the count of items in the set has increased by 1.
    @param new_entry  The object to be added as a new entry.
    @return  True if addition was successful, or false if not. */
   virtual bool Add(const ItemType& new_entry) = 0;
   
   /** Removes one occurrence of a given entry from this set,
       if possible.
    @post  If successful, anEntry has been removed from the set
       and the count of items in the set has decreased by 1.
    @param an_entry  The entry to be removed.
    @return  True if removal was successful, or false if not. */
   virtual bool Remove(const ItemType& an_entry) = 0;
   
   /** Removes all entries from this set.
    @post  Set contains no items, and the count of items is 0. */
   virtual void Clear() = 0;
   
   /** Tests whether this set contains a given entry.
    @param an_entry  The entry to locate.
    @return  True if set contains anEntry, or false otherwise. */
   virtual bool Contains(const ItemType& an_entry) const = 0;
   
   /** Empties and then fills a given vector with all entries that
       are in this set.
    @return  A vector containing all the entries in the set. */
   virtual vector<ItemType> ToVector() const = 0;
}; // end setinterface
#endif  // TEACH_CSCI235_SETADT_SETINTERFACE_H_
