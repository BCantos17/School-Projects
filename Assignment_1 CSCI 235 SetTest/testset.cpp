// Bryan Cantos -- Assignment 1 CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Ioannis Stamos.
// Modfified by Bryan Cantos

/** ADT bag: Array-based implementation.
 @file Bag.h */

#include <iostream> // For cout and cin
#include <string>   // For string objects
#include "set.h"    // For ADT set
#include "setinterface.h" // For ADT set
#include <vector> // For vector objects
using namespace std;

void TestSetImplementation();

void TestUniteSets(); 

template <class ItemType>
void DisplaySet(const set<ItemType> &a_set);

template <class ItemType>
set<ItemType> UnitedSets(const set<ItemType> &set1, const set<ItemType> &set2);

int main()
{
   TestSetImplementation();
   TestUniteSets();
  
   return 0;
}; // end main

 void TestSetImplementation()
 {
	set<int> a_set;
	 
	/*Ensures that an empty set contains no items.*/
	cout << "Creating an empty set called a_set." << endl;
	cout << "This is the empty set (a_set), and a_set.IsEmpty() returns " << a_set.IsEmpty() << endl;

	/*adds 1 to a_set
	 Adds one item to an empty set, and then searches for it (it should be there).*/
	a_set.Add(1);
	cout << "Adding the number 1 to an empty set and a_set.Contains(1]) returns a " << a_set.Contains(1) << endl;
	
	/*Creates a set to a_set by adding the following items: , 10, 3, 10, 5, 10 in that order. */
	a_set.Add(10);
	a_set.Add(3);
	a_set.Add(10);
	a_set.Add(5);
	a_set.Add(10);

	/* outputs the size of a_set 
	Ensures that the set now holds only 4 items*/
	cout << "Adding 10, 3, 10, 5, 10 in addition to the previous set and\n"
		"a_set.GetCurrentSize() returns a " << a_set.GetCurrentSize() << endl;

	/*) Ensures that the search (function Contains()) of an item in the Set returns true,
	and that the search of an item not in the Set returns false.*/

	/*outputs a true value of a_set */
	cout << "This set contains 1 and a_set.Contains(1) returns a " << a_set.Contains(1) << endl;

	/* outputs false value of a_Set*/
	cout << "This set does not contains 2 and a_set.Contains(2) returns a " << a_set.Contains(2) << endl;

	/*outputs false value of a_set 
	Ensures that adding an item already in the Set results in a false flag returned byAdd().*/
	cout << "This set already contains a 1 and an attempt to add it again via\n"
		"a_set.Add(1) returns a " << a_set.Add(1) << endl; 
	
	/*adds 2 and 4 into a_Set */
	cout << "Now adding 2 and 4 to the set to reach its capacity." << endl;
	a_set.Add(2);
	a_set.Add(4);

	/*outputs false value of a_set 
	Ensures that trying to add more items than the maximum capacity, results in a
	false flag returned by Add()*/
	cout << "This set is at its limit and an attempt to add 6 via a_set.Add(6)\n"
		"returns a " << a_set.Add(6) << endl;

	/* creates a new set */
	set<int> a_set2;

	/* returns a false value of a_set2 
	Ensures that removing an item from an empty set results in a false flag returned
	by the function Remove().*/
	cout << "Creating a new empty set and an attempt to remove a number via\n"
		"a_set2.Remove(1) returns a " << a_set2.Remove(1) << endl;

	/* removes 1 from a_Set 
	Ensures that you can remove a given item from the Set.*/
	cout << "Now removing 1 from a_set via a_set.Remove(1)." << endl;
	a_set.Remove(1);

	/* outputs a false value of a_set */
	cout << "This set no longer contains 1 and searching for 1 via\n"
		"a_set.Contains(1) returns a " << a_set.Contains(1) << endl;

 } // ends TestSetImplementation

 void TestUniteSets()
 {
	 //creates 2 new sets
	 set<int> first_set;
	 set<int> second_set;

	 cout << "\nCreating empty sets first_set and second_set." << endl;
	 cout << "Now combing both sets into a new set called third_set." << endl;

	 /*combines the first and second set
	 Ensures that the union of two empty sets is an empty set.*/
	 set<int> third_set = UnitedSets(first_set, second_set);

	 /* outputs the size of third set*/
	 cout << "third_set is empty and third_set.GetCurrentSize() returns a " << third_set.GetCurrentSize() << endl;
	 cout << "Now adding 2 and 3 into second_set and then combining the first and second set\n"
		 "together." << endl;

	 // adds 2 and 3 into the second set
	 second_set.Add(2);
	 second_set.Add(3);

	 /*combines first and second set
	 Ensures that if one of the two input sets is empty, the result equals the non­empty
     set. Use the function DisplaySet() to print the sets (same holds for the next tests).*/
	 third_set = UnitedSets(first_set, second_set);

	 // displays third set
	 cout << "Now displaying third_set using DisplaySet(third_set)." << endl;
	 DisplaySet(third_set); 

	 cout << "Now adding 1 and 4 to first_set and the combining the first and second set\n"
		 "together(Note that they share no common elements." << endl;

	 // adds 1 and 4 into the first set
	 first_set.Add(1);
	 first_set.Add(4); 

	 /* combines the first and second set into the third set
	 Use two sets that do not have common elements (for instance {1, 20, 30} and
	{40, 50}) and ensure that the result is correct.*/
	 third_set = UnitedSets(first_set, second_set);

	 // displays the third set
	 cout << "Now displaying third_set using DisplaySet(third_set)." << endl;
	 DisplaySet(third_set);

	 cout << "Adding 2 into first_set and 4 into second_set and combining them (Note they\n"
		 "share common elements)." << endl;

	 // adds 2 into the first set and 4 into the second set
	 first_set.Add(2);
	 second_set.Add(4);

	 /*combines the first and second set into the third set
	 Use two sets with commone elements and ensure that the results are correct*/
	 third_set = UnitedSets(first_set, second_set);

	 // displays the third set
	 cout << "Now displaying third_set using DisplaySet(third_set)." << endl;
	 DisplaySet(third_set);

 }
