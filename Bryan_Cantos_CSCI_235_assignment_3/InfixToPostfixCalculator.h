// Created by Bryan Cantos
 
#ifndef TEACH_CSCI235_STACKADT_INFIXTOPOSTFIXCALCULATOR_H
#define TEACH_CSCI235_STACKADT_INFIXTOPOSTFIXCALCULATOR_H

#include <string>
#include "LinkedStack.h"
#include "StackInterface.h"

class InfixToPostfixCalculator
{
public:
	InfixToPostfixCalculator(); // constructor
	string ConvertInfixToPostfix(const string &input_infix); 
	double CalculatePostfix(const string &input_postfix);

private:
	LinkedStack<char> operation_stack; // stack for opertors
	LinkedStack<double> num_stack; // stack for numbers
	string postfix_expression;
	double first_num, second_num, answer; // values for doing operations in a postfix expression
	int position; // position of where we are up to in a postfix
	int WhichOperation(char operation); 
	int OperatorHasHigherSway(char operation1, char operation2); // checks to see which operation should be done first
	bool IsNumber(char number); // checks to see if current vaule is a number
	bool IsOperator(char operation); // checks to see if current vaule is an operator
	double StackNumber(const string &input_postfix); // stacks numbers of a postfix to num_stack
	bool DoOperation(); // does operation using num_stack and operation_stack
};

#include "InfixToPostfixCalculator.cpp"
#endif  // TEACH_CSCI235_STACKADT_INFIXTOPOSTFIXCALCULATOR_H