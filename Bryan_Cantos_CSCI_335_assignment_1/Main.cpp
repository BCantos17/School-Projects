// Created by Bryan Cantos
// Class CSCI 335

#include <iostream>
#include <cstdlib>
#include <string>
#include "Chain.h"

using namespace std;

Chain GetChain();

int main() {

    cout << "Creating Chain a, b ,c." << endl;
	Chain a, b, c; //Three empty chains are created
    cout << "Creating Chain d with 10 in chain." << endl;
    Chain d{10}; //A chain containing just one element: 10
    cout << "Displaying length of Chain a." << endl;
    cout << a.Length() << endl; // yields 0
    cout << "Beginning user input of numbers into Chain a." << endl;
    cin >> a; // User types [2 3 7]
    cout << "Outputting Chain a." << endl;
    cout << a; // Output is [2 3 7]
    cout << "Beginning user input of numbers into Chain b." << endl;
    cin >> b; // User types [8 4 2 1]
    cout << "Copying Chain a into Chain c." << endl;
    c = a; // Copy assignment
    cout << "Outputting Chain c." << endl;
    cout << c; // Output should be [2 3 7]
    cout << "Outputting Chain a + b." << endl;
    cout << a + b << endl; // Output is [2 3 7 8 4 2 1]
    cout << "Outputting Chain a + 5." << endl;
    cout << a + 5; // Output is [2 3 7 5]
    cout << "Creating new Chain e with values of Chain c using copy constructor." << endl;
    Chain e{c}; //Copy Constructor
    cout << "Outputting Chain e." << endl;
    cout << e; //Output should be [2 3 7]
    cout << "Outputting the second item in Chain a." << endl;
    cout << a[1] << endl; //Should printout 3
    cout << "Changing the second item of Chain c to 100." << endl;
    c[1] = 100; //Should change c[1]
    cout << "Outputting Chain c." << endl;
    cout << c; //Should print [2 100 7]
    cout << "Outputting Chain e." << endl;
    cout << e;//Should print [2 3 7]
    cout << "Creating Chain f with the values of funtion GetChain()." << endl;
    Chain f = GetChain(); //GetChain() should be a function that returns by value a Chain of some elements. Write this simple functioin.
    cout << "Outputting Chain f." << endl;
    cout << f; //Should print whatever GetChain() returned.

	return 0;
}

Chain GetChain()
{
    Chain new_chain(1);

    return new_chain + 2;
}