i) All parts were completeled except for b.ii) where it ask to add an item to the end of the list.

ii) The Polynomials are not added at the end of the list, other than that, no bugs were found.

iii) When compiling on windows, you must have the line "g++ TestLinkedPolynomial.cpp -o TestLinkedPolynomial -std=c++11" or if on Linux "g++ TestLinkedPolynomial.cpp -o TestLinkedPolynomial -std=c++0x"

iv) Inputs

	cin >> coefficient;
	cin >> exponent;
	cin >> add_more;
	cin >> exponent; 
	cin >> new_coefficient;

	Outputs

	cout << "Creating a Polynomial now." << endl;
	cout << "Enter a coefficient." << endl;
	cout <<"Next, enter an exponent." << endl;
	cout << "Would you like to add more to this Polynomial?\n"
      "Please enter Y for yes or N for no." << endl;
    cout << "Invalid option, try again." << endl;
    cout << "The Degree of this polynomial is: " << a_polynomial.Degree() << endl;
    cout << "We're going to display a coefficient that cooresponds to a given exponent.\n"
    " Please enter an exponent number." << endl;
    cout << "The coefficient that cooresponds to this exponent is: " 
    << a_polynomial.Coefficient(exponent) << endl;
    cout << "We're now going to change the coefficient that cooresponded to the previous exponent.\n"
    "Please enter a coefficient." << endl;
    cout << "Entering a_polynomial.ChangeCoefficient(new_coefficient, exponent) returns a "
    << a_polynomial.ChangeCoefficient(new_coefficient, exponent) << endl;
    cout << "We're now going to add 2 polynomials together." << endl;
    std::cout << "Your Polynomial is: " << std::endl;
    std::cout << next_ptr->GetCoefficient() << " * x^" << next_ptr->GetExponent() << " + ";