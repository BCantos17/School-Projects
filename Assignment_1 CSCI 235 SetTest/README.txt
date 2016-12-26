Bryan Cantos -- Assignment 1 CSCI 235
1.)
	I modified the Add function to make sure it would not accept duplicate items.
	Created a contructor that can add a single item without functions. ex: a_set(1) where 1 is added into the set.
	Created a function called TestSetImplementation() where all the test ask by the assignment, is tested and completled correctly.
	Created 2 functions DisplaySet() and UnitedSets() where displayset displays all the contents in a set and unitedset combines 2 set into a 3rd set
	Created a function called TestUniteSets()

2.) 
	I have not encountered any bugs 

3.) 
	Have the testset.cpp, set.h and setinterface.h in one project and compile it together

4.)
	No input files

	outputfiles:
	Creating an empty set call a_set.
	This is the empty set (a_set), and a_set.IsEmpty() returns 1	
	Adding the number 1 to an empty set and a_set.Contains(1) returns a 1	
	Adding 10, 3, 10, 5, 10 in addition to the previous set and a_set.GetCurrentSize() returns a 4	
	This set contains 1 and a_set.Contains(1) returns a 1    
	This set does not contains 2 and a_set.Contains(2) returns a 0    
	This set already contains a 1 and an attempt to add it again via a_set.Add(1) returns a 0    
	Now adding 2 and 4 to the set to reach its capacity.
	This set is at its limit and an attempt to add 6 via a_set.Add(6) returns a 0	
	Creating a new empty set and an attempt to remove a number via a_set2.Remove(1) returns a 0    
	Now removing 1 from a_set via a_set.Remove(1).
	This set no longer contains 1 and searching for 1 via a_set.Contains(1) returns a 0

	Creating empty sets first_set and second_set.
	Now combing both sets into a new set called third_set.
    	third_set is empty and third_set.GetCurrentSize() returns a 0
	Now adding 2 and 3 into second_set and then combining the first and second set together.
    	Now displaying third_set using DisplaySet(third_set).
	2
	3
	Now adding 1 and 4 to first_set and the combining the first and second set together(Note that they share no common elements.
    	Now displaying third_set using DisplaySet(third_set).
	1
	4
	2
	3
    	Adding 2 into first_set and 4 into second_set and combining them (Note they share common elements).
    	Now displaying third_set using DisplaySet(third_set).
	1
	4
	2
	3