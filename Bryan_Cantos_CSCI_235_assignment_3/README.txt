i) All parts were completeled

ii) No bugs were found.

iii) When compiling on windows, you must have the line "g++ TestLinkedPolynomial.cpp -o TestLinkedPolynomial -std=c++11" or if on Linux "g++ TestLinkedPolynomial.cpp -o TestLinkedPolynomial -std=c++0x"

iv) Inputs files
        ((1+2) * 3 -2) /7
        (11+(3-2))/4
        (1-2
        1-2)
        1++2
        (12 + 3) * ( 9 - 74) + 34 / ((85 - 93) +(3 + 5) * 3) - 5
        1+2

    Output files
        1,2,+,3,*,2,-,7,/ = 1
        11,3,2,-,+,4,/ = 3
        Error: missing right parenthesis.
        Error: missing left Parenthesis.
        Error: too many operators.
        12,3,+,9,74,-,*,34,85,93,-,3,5,+,3,*,+,/,+,5,- = -977.875
        1,2,+ = 3
