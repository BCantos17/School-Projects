// Created by Bryan Cantos.
// CSCI 235

#include "InfixToPostfixCalculator.h"
#include <string>
#include <cstdlib>
#include <cmath>

InfixToPostfixCalculator::InfixToPostfixCalculator()
{
}  // end default constructor

string InfixToPostfixCalculator::ConvertInfixToPostfix(const string &input_infix)
{
	postfix_expression.clear(); // clears anything in this string for use

	//goes throuh each vaule of an infix expression one by one
	for(int i=0; i<input_infix.size(); i++)
	{
		if(input_infix[i] == ' ') continue; // if space, continue

		// checks if current value is an operator
		else if(IsOperator(input_infix[i]))
		{
			// check if next value is an opertor and displays error
			if(IsOperator(input_infix[i+1]))
			{
				while(!operation_stack.IsEmpty())
				operation_stack.Pop();
				return "Error: too many operators.";
			}

			/*puts operator into postfix expression unless there is a left parenthesis in operation_stack or
			if operation_stack is empty or if OperationHasHigherSway returns a false */
			while(!operation_stack.IsEmpty() && operation_stack.Peek() != '(' 
				  && OperatorHasHigherSway(operation_stack.Peek(), input_infix[i]))
			{
				postfix_expression+= operation_stack.Peek();
				postfix_expression+= ',';
				operation_stack.Pop();
			} // end while

			operation_stack.Push(input_infix[i]); // pushes operator into stack
		} // end else if

		// pushes left parenthesis into a stack
		else if(input_infix[i] == '(')
			operation_stack.Push(input_infix[i]);

		// Puts all operators in the postfix expression until it runs into a left parenthesis
		else if (input_infix[i]==')')
		{
			while(operation_stack.Peek() != '(')
			{
				postfix_expression+= operation_stack.Peek();
				operation_stack.Pop();
				postfix_expression+= ',';

				// if operation_stack is empty, returns an error.
				if(operation_stack.IsEmpty())
					return "Error: missing left Parenthesis.";
				
			} // end while
			operation_stack.Pop();
		} // end else if
	
		// checks to see if value is a number
		else if(IsNumber(input_infix[i]))
		{
			// if it's a number, puts the value into the postfix expression
			postfix_expression+=input_infix[i];

			// if number is a multi-digit number, continues to put it into postfix expression
			while(IsNumber(input_infix[i+1]))
			{
				i++;
				postfix_expression+=input_infix[i];
			} // end while
			postfix_expression+=',';
		 }// end else if

	} // end for

	// empties out remaining stack and puts it into postfix expression
	while(!operation_stack.IsEmpty()) 
	{
		// if operation_stack has a left parenthesis, returns an error
		if(operation_stack.Peek() == '(')
		{
			// continues to empty out operation_stack then returns an error
			while(!operation_stack.IsEmpty())
				operation_stack.Pop();
			return "Error: missing right parenthesis.";
		}
		postfix_expression += operation_stack.Peek();
		operation_stack.Pop();
	}

	return postfix_expression;
}

double InfixToPostfixCalculator::CalculatePostfix(const string &input_postfix)
{
	double temp;
	position = 0;

	// goes through each value of the postfix one by one
	while (position < input_postfix.size())
	{
		// ignores a comma
		if(input_postfix[position] == ',') 
			position++;

		// if it is a number, pushes number into num_stack
		else if(IsNumber(input_postfix[position]))
		{
			temp = StackNumber(input_postfix);
			num_stack.Push(temp);
		}

		// if it is not a number, must be an operator, therefore pushes operator into a stack and does an operation
		else 
		{
			operation_stack.Push(input_postfix[position]);
			position++;
			DoOperation();
		}

	} // end while

	answer = num_stack.Peek();
	num_stack.Pop(); // Pops last remaining stack

	return answer;
}

int InfixToPostfixCalculator::WhichOperation(char operation)
{
	int sway = -1; 

	// orders the operation in correct pattern
	switch(operation)
	{
	case '+':
	case '-':
		sway = 1;
		break;
	case '*':
	case '/':
		sway = 2;
		break;
	case '^':
		sway = 3;
		break;
	}
	return sway;
}

int InfixToPostfixCalculator::OperatorHasHigherSway(char operation1, char operation2)
{

	// If operators have equal precendence, then nothing changes
	if(WhichOperation(operation1) == WhichOperation(operation2))
	{
		// if it is an exponent, this has more precedence in postfix expression
		if(operation1 == '^') return false;
		else return true;
	}
	// returns true if first operator has higher precedence than the second operator 
	return WhichOperation(operation1) > WhichOperation(operation2) ?  true: false;
}

bool InfixToPostfixCalculator::IsNumber(char number)
{
	// checks to see if values are only numbers.
	if (number>='0' && number <= '9')
		return true;
	return false;
}

bool InfixToPostfixCalculator::IsOperator(char operation)
{
	// checks to see if values are only valid operators 
	if(operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '^')
		return true;
	return false;
}

double InfixToPostfixCalculator::StackNumber(const string &input_postfix)
{
	string next_num;
	next_num += input_postfix[position]; // puts current value of the postfix into next_num
	double term = 0;
	position++;

	// if the number is a multi-digit number, continues to put it into next_num
	while(IsNumber(input_postfix[position]))
	{
		next_num += input_postfix[position];
		position++;
	}

	term = atoi(next_num.c_str()); // turns all c-string of next_num into an integer and returns that number as term
	return term;
}

bool InfixToPostfixCalculator::DoOperation()
{
	double temp;

	char operation = operation_stack.Peek(); // puts current operation into char operation
	operation_stack.Pop();
	// puts the top number of num_stack into second_num
	second_num = num_stack.Peek();
	num_stack.Pop();
	// puts the next number of num_stack into first_num
	first_num = num_stack.Peek();
	num_stack.Pop();

	// depending on what is in operation, does the math accordingly 
	if(operation=='+')
	{
		temp = first_num + second_num;
		num_stack.Push(temp);
		return true;
	}
	else if(operation =='-')
	{
		temp = first_num - second_num;
		num_stack.Push(temp);
		return true;
	}
	else if(operation =='*')
	{
		temp = first_num * second_num;
		num_stack.Push(temp);
		return true;
	}
	else if(operation =='/')
	{
		temp = first_num / second_num;
		num_stack.Push(temp);
		return true;
	}
	else if(operation =='^')
	{
		temp = pow(first_num, second_num);
		num_stack.Push(temp);
		return true;
	}
	else
		return false;
}