// Created by Bryan Cantos
// CSCI 235

#include <iostream>
#include <string>
#include <fstream>
#include "InfixToPostfixCalculator.h"

using namespace std;

bool exceptions(string expression)
{
	string opertor_exception = "Error: too many operators."; // exception for too many operators
	string left_Par_exception = "Error: missing left Parenthesis."; // exceptions for missing left parenthesis
	string right_Par_exception = "Error: missing right parenthesis."; // exception for missing right parenthesis

	// checks if postfix equals exception
	if (expression == opertor_exception || expression == left_Par_exception ||
		expression == right_Par_exception)
	{
		return true;
	}
	return false;
}

int main()
{
	ifstream infixFile; // open text file with infix expression inside
	ofstream resultFile; // open text file for postfix expression and results of said expression
	InfixToPostfixCalculator infix; // class for conversion and answer
	string expression, postfix;
	double answer;

	infixFile.open("infixFile.txt");
	if(infixFile.fail())
	{
		cout << "infixFile.txt file opening failed." << endl;
		return 0;
	}
	resultFile.open("resultFile.txt");

	while(getline(infixFile, expression))
	{
		// begins conversion from infix to postfix
		postfix = infix.ConvertInfixToPostfix(expression);
		
		if (exceptions(postfix)) // if there are errors in expression, returns an exception
			resultFile << postfix << endl; // returns exceptions into resultFile
		else // otherwise calculates expression
		{
			answer = infix.CalculatePostfix(postfix);
			resultFile << postfix << " = " << answer << endl;
		}
	}

	infixFile.close(); //closes text files
	resultFile.close();

	return 0;
}