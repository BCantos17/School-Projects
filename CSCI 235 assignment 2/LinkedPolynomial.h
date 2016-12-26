//  Bryan Cantos CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Ioannis Stamos.
//  Modified by Bryan Cantos.

/** ADT Polynomial: Link-based implementation.
    @file LinkedPolynomial.h 
    Listing 4-3 */
#ifndef TEACH_CSCI235_LINKEDBAG_LINKEDBAG_H_
#define TEACH_CSCI235_LINKEDBAG_LINKEDBAG_H_

//#include "BagInterface.h"
#include "Node.h"

// Linked-based implementation of the Polynomial ADT.
// Sample usage:
//    LinkedPolynomial<int> a_polynomial;
//    while (read a_value)
//        a_polynomial.Add(a_value);
//    if (a_polynomial.Contains(10))
//      cout << "10 is in the polynomial" << endl;
//    else
//      cout << "10 is not in the polynomial" << endl;
//    cout << "Frequency of 20 is " << a_polynomial.GetFrequencyOf(20) << endl;
//    const vector<int> a_vector = a_polynomial.ToVector();
//    /* Note C++11 syntax for accessing elements of vectors here*/
//    for (const auto &element: a_vector)
//       cout << element << " ";
//    cout << endl;
template<class ItemType>
class LinkedPolynomial
{
public:
   LinkedPolynomial();
   LinkedPolynomial(const LinkedPolynomial<ItemType>& a_polynomial); // Copy constructor.
   LinkedPolynomial<ItemType>& operator=(const LinkedPolynomial<ItemType>& right_hand_side); // Overloading of the assignment operator.
   virtual ~LinkedPolynomial();                       // Destructor should be virtual
   int GetCurrentSize() const;
   bool IsEmpty() const;
   bool Add(const ItemType& new_entry_1, const ItemType& new_entry_2);
   //bool Remove(const ItemType& an_entry);
   void Clear();
   bool Contains(const ItemType& an_ntry) const;
   int GetFrequencyOf(const ItemType& an_entry) const;
   //vector<ItemType> ToVector() const; 
   void DisplayPolynomial() const;
   ItemType Degree() const;
   ItemType Coefficient(const ItemType& exponent) const;
   bool ChangeCoefficient(ItemType new_coefficient, ItemType exponent);
   void AddPolynomial(const LinkedPolynomial<ItemType> &b_polynomial);

private:
   Node<ItemType>* head_ptr_; // Pointer to first node
   int item_count_;           // Current count of Polynomial items
   
   // @return either a pointer to the node containing a given entry
   // or the null pointer if the entry is not in the Polynomial.
   Node<ItemType>* GetPointerTo(const ItemType& target_1) const;
   
   // @param a_polynomial a given Polynomial.
   // Allocates space and copies all the nodes from a_polynomial.
   // The function does not check whether this Polynomial contains
   // any items, but it assumes that it is empty.
   void CopyNodesFrom(const LinkedPolynomial<ItemType> &a_polynomial);
}; // end LinkedPolynomial

#include "LinkedPolynomial.cpp"
#endif  // TEACH_CSCI235_LINKEDBAG_LINKEDBAG_H_
