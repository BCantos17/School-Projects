// Created by Bryan Cantos
// Class CSCI 335

#ifndef _335_Assignment_
#define _335_Assignment_

using namespace std;

class Chain{
public:
    Chain(); //Default Constructor
    Chain(int new_entry); //One Element Constructor
    Chain(const Chain & right_hand_size); //Copy Constructor
    ~Chain(); //Destructor
    Chain(Chain && right_hand_size); //Move Constructor
    Chain & operator= (const Chain & right_hand_size); //Copy Assignment
    Chain & operator= (Chain && right_hand_size); //Move Assignment
    Chain operator+ (const Chain & right_hand_size) const; //Add Assignment
    Chain operator+ (int new_entry) const; //Add one element Assignment 
    int & operator[] (int chain_item); //Subscrit operator
    friend ostream & operator<< (ostream & out_stream, const Chain & output_chain); // Overload Ostream 
    friend istream & operator>>(istream& in_stream, Chain& input_chain); //Overload Istream
    int Length(); //Get Length
    void Clear(); // Clear Chain
    void Add(int new_entry); //Add new entry

private:
    int item_count; //Number of items in chain
    int CAPACITY = 100; // Max capacity of array
    int *chain_arr; 
    void CopyChainFrom(const Chain & a_chain); //Copies Chain
};

#include "Chain.cpp"
#endif /* defined(_335_Assignment_) */
