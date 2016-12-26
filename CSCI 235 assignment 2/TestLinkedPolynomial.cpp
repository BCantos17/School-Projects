// Bryan Cantos CSCI 235
#include <iostream> // For cout and cin
#include <string>   // For string objects
#include "LinkedPolynomial.h"    // For ADT bag
using namespace std;

LinkedPolynomial<double> CreatePolynomialFromInput(); // Creats a polynomial
void TestPolynomial();
void TestAddition();

int main()
{
  LinkedPolynomial<double> x;
  x.Add(1,2);
  x.DisplayPolynomial();
  x.Add(3,4);
  x.DisplayPolynomial();
  //TestPolynomial();
  //TestAddition();
   return 0;
}; // end main

LinkedPolynomial<double> CreatePolynomialFromInput()
{
  double coefficient;
  double exponent; 
  char add_more = 'y';
  LinkedPolynomial<double> a_polynomial;

  cout << "Creating a Polynomial now." << endl;
  while(add_more == 'y' || add_more == 'Y') // add_more must be y to continue.
  {
    cout << "Enter a coefficient." << endl;
    cin >> coefficient;

    cout <<"Next, enter an exponent." << endl;
    cin >> exponent;

    a_polynomial.Add(coefficient, exponent); // add the numbers declared by the user to the class.

    cout << "Would you like to add more to this Polynomial?\n"
      "Please enter Y for yes or N for no." << endl;
    cin >> add_more;

    while(add_more!= 'y' && add_more!= 'n' && add_more!= 'Y' && add_more != 'N') // Yes or No to continue.
    {
      cout << "Invalid option, try again." << endl;
      cin >> add_more;
    }

    if(add_more == 'n' && add_more == 'N')
      break;
  }

  return a_polynomial;
}

void TestPolynomial()
{
  LinkedPolynomial<double> a_polynomial = CreatePolynomialFromInput();
  double exponent;
  double new_coefficient;

  a_polynomial.DisplayPolynomial();
  cout << "The Degree of this polynomial is: " << a_polynomial.Degree() << endl;
  cout << "We're going to display a coefficient that cooresponds to a given exponent.\n"
    " Please enter an exponent number." << endl;
  cin >> exponent; 
  cout << "The coefficient that cooresponds to this exponent is: " 
  << a_polynomial.Coefficient(exponent) << endl;
  cout << "We're now going to change the coefficient that cooresponded to the previous exponent.\n"
    "Please enter a coefficient." << endl;
  cin >> new_coefficient;
  cout << "Entering a_polynomial.ChangeCoefficient(new_coefficient, exponent) returns a "
    << a_polynomial.ChangeCoefficient(new_coefficient, exponent) << endl;
  a_polynomial.DisplayPolynomial();
}

void TestAddition()
{
  cout << "We're now going to add 2 polynomials together." << endl;

  LinkedPolynomial<double> polynomial_1 = CreatePolynomialFromInput();
  LinkedPolynomial<double> polynomial_2 = CreatePolynomialFromInput();
  polynomial_1.AddPolynomial(polynomial_2);
  polynomial_1.DisplayPolynomial();
}