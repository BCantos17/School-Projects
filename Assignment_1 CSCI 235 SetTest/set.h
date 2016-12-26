// Bryan Cantos -- Assignment 1 CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Ioannis Stamos.
// Modfified by Bryan Cantos

/** ADT set: Array-based implementation.
 @file set.h */


#ifndef TEACH_CSCI235_BAGADT_BAG_H_
#define TEACH_CSCI235_BAGADT_BAG_H_

#include "setinterface.h"
#include <vector>

template<class ItemType>
class set : public setinterface<ItemType>
{
 public:
  set();
  set(const ItemType &an_item); // contrusctor thats constructs for a signal item.
  int GetCurrentSize() const;
  bool IsEmpty() const;
  bool Add(const ItemType& new_entry);
  bool Remove(const ItemType& an_entry);
  void Clear();
  bool Contains(const ItemType& an_entry) const;
  int GetFrequencyOf(const ItemType& an_entry) const;
  vector<ItemType> ToVector() const; 

  
 private:
  int GetIndexOf(const ItemType& target) const;   
  static const int kDefaultSetSize_ = 6;  
  ItemType items_[kDefaultSetSize_]; // array of set items
  int item_count_;                    // current count of set items 
  int max_items_;                 // max capacity of the set
  
  // Returns either the index of the element in the array items that
  // contains the given target or -1, if the array does not contain 
  // the target.
};  // end Set


template<class ItemType>
set<ItemType>::set() : item_count_(0), max_items_(kDefaultSetSize_)
{
}  // end default constructor

template<class ItemType>
set<ItemType>::set(const ItemType &an_item) : item_count_(0), max_items_(kDefaultSetSize_)
{
	if(item_count_ < max_items_)
	{
		items_[item_count_] = an_item;
		item_count_++;
	} // end if
}  // end single item constructor


template<class ItemType>
int set<ItemType>::GetCurrentSize() const
{
  return item_count_;
}  // end getCurrentSize

template<class ItemType>
bool set<ItemType>::IsEmpty() const
{
  return item_count_ == 0;
}  // end isEmpty

template<class ItemType>
bool set<ItemType>::Add(const ItemType& new_entry)
{
  bool has_room_to_add = item_count_ < max_items_;
   if (has_room_to_add)
   {
	   for ( int i =0; i <= item_count_; i++)
		{
			// returns a false value if one of the items is the same as the new entry
			if (items_[i] == new_entry)
				return 0;

			// adds a new entry into item is none of the items are repeated
			if (i==item_count_)
			{
				items_[item_count_] = new_entry;
				item_count_++;
				break;
			}  // end if
		} // end for
   } //end if
   
  return has_room_to_add;
}  // end add

template<class ItemType>
bool set<ItemType>::Remove(const ItemType& an_entry)
{
  int located_index = GetIndexOf(an_entry);
  bool can_remove_item = !IsEmpty() && (located_index > -1);
  if (can_remove_item)
    {
      item_count_--;
      items_[located_index] = items_[item_count_];
    }  // end if
  return can_remove_item;
}  // end remove

template<class ItemType>
void set<ItemType>::Clear()
{
  item_count_ = 0;
}  // end clear

template<class ItemType>
int set<ItemType>::GetFrequencyOf(const ItemType& an_entry) const
{
  int frequency = 0;
  int search_index = 0;
  while (search_index < item_count_)
    {
      if (items_[search_index] == an_entry)
	{
	  frequency++;
	}  // end if
      
      search_index++;
    }  // end while
  
   return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool set<ItemType>::Contains(const ItemType& an_entry) const
{
  return GetIndexOf(an_entry) > -1;
}  // end contains

template<class ItemType>
vector<ItemType> set<ItemType>::ToVector() const
{
  vector<ItemType> set_contents;
  for (int i = 0; i < item_count_; i++)
    set_contents.push_back(items_[i]);
  return set_contents;
}  // end toVector

template<class ItemType>
int set<ItemType>::GetIndexOf(const ItemType& target) const
{
  bool found = false;
  int result = -1;
  int search_index = 0;
  // if the set is empty, item_count is zero, so loop is skipped
  while (!found && (search_index < item_count_))
    {
      if (items_[search_index] == target)
	{
	  found = true;
	  result = search_index;
	} 
      else
	{
	  search_index++;
	}  // end if
    }  // end while
  return result;
}  // end getIndexOf

// Displays all contents in a set
template <class ItemType>
void DisplaySet(const set<ItemType> &a_set)
{
	// adds the contents of a_set into the vector set_contents
	vector<ItemType> set_contents = a_set.ToVector();

	// the current size of a_set is added into j
	int j = a_set.GetCurrentSize();

	// displays all the contents of set_contents
	for(int i = 0; i < j; i++)
		cout << set_contents[i] << endl;
}

template <class ItemType>
set<ItemType> UnitedSets(const set<ItemType> &set1, const set<ItemType> &set2)
{

	// gives all the contents from set 1 and set 2 to set_contents1 and set_contents 2 respectively 
	vector<ItemType> set_contents_1 = set1.ToVector();
	vector<ItemType> set_contents_2 = set2.ToVector();

	// gives the current sizes of set 1 and 2 to size1 and size 2
	int size_1 = set1.GetCurrentSize();
	int size_2 = set2.GetCurrentSize();

	//creates a new set
	set<ItemType> total_set; 

	// adds the contents of set_contents1 and set_contents2 into total_set
	for (int i = 0; i < size_1; i++)
		total_set.Add(set_contents_1[i]);

	for (int j = 0; j < size_2; j++)
		total_set.Add(set_contents_2[j]);

	return total_set;
}

#endif  // TEACH_CSCI235_BAGADT_SET_H_
