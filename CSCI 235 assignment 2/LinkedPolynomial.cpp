//  Bryan Cantos CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
// Modified by Ioannis Stamos.
//  Modified by Bryan Cantos.

/** ADT Polynomial: Link-based implementation.
    @file LinkedPolynomial.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <iostream>

template<class ItemType>
LinkedPolynomial<ItemType>::LinkedPolynomial() : head_ptr_(nullptr), item_count_(0)
{
}  

template<class ItemType>
LinkedPolynomial<ItemType>::LinkedPolynomial(const LinkedPolynomial<ItemType>& a_polynomial)
{
  CopyNodesFrom(a_polynomial);
}  

template<class ItemType>
LinkedPolynomial<ItemType>& LinkedPolynomial<ItemType>::operator=(const LinkedPolynomial<ItemType>& right_hand_side) {
  if (this != &right_hand_side) {  
    Clear(); // First deallocate all memory.
    CopyNodesFrom(right_hand_side);  // Then copy everything.
  }
  return *this;  // Return self.
}

template<class ItemType>
LinkedPolynomial<ItemType>::~LinkedPolynomial()
{
  Clear();
}  

template<class ItemType>
bool LinkedPolynomial<ItemType>::IsEmpty() const
{
  return item_count_ == 0;
}  

template<class ItemType>
int LinkedPolynomial<ItemType>::GetCurrentSize() const
{
  return item_count_;
}  

template<class ItemType>
bool LinkedPolynomial<ItemType>::Add(const ItemType& new_entry_1, const ItemType& new_entry_2)
{
  Node<ItemType>* next_node_ptr = new Node<ItemType>(new_entry_1, new_entry_2, head_ptr_); 
  Node<ItemType>* exp_check = head_ptr_; 

  // Compares exp_check exponent to next_node_ptr exponent.
  for(int i=0; i< item_count_; i++)
  {
    //  If the user inputted exponent exist, return nothing.
    if(exp_check->GetExponent() == next_node_ptr->GetExponent())
      return false;
      
    exp_check = exp_check->GetNext(); 
  } // end for

  head_ptr_ = next_node_ptr; // New node is now first node
  item_count_++;
  
  return true;
}  

template<class ItemType>
void LinkedPolynomial<ItemType>::Clear()
{
  Node<ItemType>* current_node_to_delete = head_ptr_;
  while (head_ptr_ != nullptr) {
    head_ptr_ = head_ptr_->GetNext();
    // Return node to the system
    current_node_to_delete->SetNext(nullptr);
    delete current_node_to_delete;
    current_node_to_delete = head_ptr_;  // Move to the next one.
  }  // end while
  item_count_ = 0;
}  

template<class ItemType>
int LinkedPolynomial<ItemType>::GetFrequencyOf(const ItemType& an_entry) const
{
  int frequency = 0;
  int counter = 0;
  Node<ItemType>* current_ptr = head_ptr_;
  while (current_ptr != nullptr){
    if (an_entry == current_ptr->GetCoefficient()) {
      frequency++;
    } // end if
    counter++;
    current_ptr = current_ptr->GetNext();
    // Check for possible serious error.
    if (counter > item_count_) {
       std::cout << "Serious error in LinkedPolynomial<ItemType>::GetFrequencyOf" << std::endl;
       return frequency;
    }
  } // end while
  return frequency;
} 

template<class ItemType>
bool LinkedPolynomial<ItemType>::Contains(const ItemType& an_entry) const
{
  return (GetPointerTo(an_entry) != nullptr);
}  // end Contains


template<class ItemType>
Node<ItemType>* LinkedPolynomial<ItemType>::GetPointerTo(const ItemType& an_entry_1) const
{
   Node<ItemType> *current_ptr = head_ptr_;
   
   while (current_ptr != nullptr) {
     if (an_entry_1 == current_ptr->GetCoefficient())
       return current_ptr;
     else
       current_ptr = current_ptr->GetNext();
   } // end while 
   return nullptr;
} 


template<class ItemType>
void LinkedPolynomial<ItemType>::CopyNodesFrom(const LinkedPolynomial<ItemType> &a_polynomial) {
  item_count_ = a_polynomial.item_count_;  
  Node<ItemType>* a_polynomial_current_pointer = a_polynomial.head_ptr_;  // Pointer to beginning of a_polynomial.
   
  if (a_polynomial_current_pointer == nullptr) {  // a_polynomial is empty.
    head_ptr_ = nullptr;  
    return;
  } 
  // Copy first node
  head_ptr_ = new Node<ItemType>();
  head_ptr_->SetCoefficient(a_polynomial_current_pointer->GetCoefficient());
  head_ptr_->SetExponent(a_polynomial_current_pointer->GetExponent());
  
  // Copy remaining nodes
  Node<ItemType>* last_pointer = head_ptr_;      // Points to last node in new chain
  a_polynomial_current_pointer = a_polynomial_current_pointer->GetNext();     // Advance original-chain pointer
  
  while (a_polynomial_current_pointer != nullptr) {
    // Create a new node holding the item of a_polynomial_current_pointer.
    Node<ItemType>* new_node_pointer = new Node<ItemType>(a_polynomial_current_pointer->GetCoefficient(),
      a_polynomial_current_pointer->GetExponent());
    
    // Link new node to end of new chain
    last_pointer->SetNext(new_node_pointer);
    
    // Advance pointer to new last node
    last_pointer = last_pointer->GetNext();
    
    // Advance original-chain pointer
    a_polynomial_current_pointer = a_polynomial_current_pointer->GetNext();
  }  // end while
  last_pointer->SetNext(nullptr); 
}

template<class ItemType>
void LinkedPolynomial<ItemType>::DisplayPolynomial() const 
{
  Node<ItemType>* next_ptr = head_ptr_; //Makes a new node pointing to the beginning of the node.

  std::cout << "Your Polynomial is: " << std::endl;
  // Displays the set of numbers in "C * x^E +" form counting down from the beginning of the pointer.
  for(int i=0; i<item_count_; i++)
  {
    // If the node is at the last set of numbers, it will not add the "+" sign and skip a line.
    if(i==item_count_-1)
    {
      std::cout << next_ptr->GetCoefficient() << " * x^" << next_ptr->GetExponent() << std::endl;
      break;
    } // end if
    std::cout << next_ptr->GetCoefficient() << " * x^" << next_ptr->GetExponent() << " + ";
    next_ptr = next_ptr->GetNext(); // Points the the next node.
  } // end for
}

template<class ItemType>
ItemType LinkedPolynomial<ItemType>::Degree() const 
{
  // Returns -1 if the pointer is empty.
  if (item_count_==0)
    return -1;

  Node<ItemType>* exp_check_1 = head_ptr_; // Node that points to the beginning of head_ptr_.
  Node<ItemType>* exp_check_2 = head_ptr_->GetNext(); // Node that points to the 2nd pointer of head_ptr_.
  ItemType _degree= exp_check_1->GetExponent(); // the highest exponent in a pointer.

  // The for loop is set at item_count_-1 because exp_check_2 would go a non-exisiting pointer
  // if it reaches (i<item_count_)
  for (int i=0; i< item_count_-1; i++)
  {
    // Compares one exponent to the previous exponent.
    if( exp_check_2->GetExponent() > exp_check_1->GetExponent())
    {
      // If exponent is bigger, _degree is set to that exponent.
      if(exp_check_2->GetExponent() > _degree)
        _degree = exp_check_2->GetExponent();
    }

    exp_check_1 = exp_check_1->GetNext(); // Goes to the next pointer.
    exp_check_2 = exp_check_2->GetNext(); // Goes to the next pointer.
  }

  return _degree;
}

template<class ItemType>
ItemType LinkedPolynomial<ItemType>::Coefficient(const ItemType& exponent) const
{
  Node<ItemType>* exp_check = head_ptr_; // Pointer that points to the beginning of head_ptr_
  ItemType _coefficeint = 0;

  // Compares the user inputted exponent to everything the pointer points to.
  for(int i =0; i<item_count_; i++)
  {
    if(exponent == exp_check->GetExponent())
    {
      // if exponent is equal to a number pointed by exp.check, it initializes _coefficent to that number.
      _coefficeint = exp_check->GetCoefficient();
    }

    exp_check = exp_check->GetNext(); // Goes to the next pointer
  }

  return _coefficeint;
}

template<class ItemType>
bool LinkedPolynomial<ItemType>::ChangeCoefficient(ItemType new_coefficient, ItemType exponent)
{
  Node<ItemType>* exp_check = head_ptr_; // Pointer that points to the beginning of head_ptr_

  // Compares exponent to the number exp_check is pointing to.
  for(int i =0; i<item_count_; i++)
  {
    if(exponent == exp_check->GetExponent())
    {
      exp_check->SetCoefficient(new_coefficient); // changes the coefficient if it finds the exponent
      break;
    }

    exp_check = exp_check->GetNext(); // Goes to the next pointer

    if(i == item_count_-1)
      return false; // returns false if the user inputted exponent is not found
  }

  return true;
}

template<class ItemType>
void LinkedPolynomial<ItemType>::AddPolynomial(const LinkedPolynomial<ItemType> &b_polynomial)
{
  int size = b_polynomial.GetCurrentSize();
  Node<ItemType>* b_node_ptr = b_polynomial.head_ptr_;

  //Adds the numbers b_node_ptr is pointing to into the class pointer.
  for (int i =0; i<size; i++)
  {
    Add(b_node_ptr->GetCoefficient(), b_node_ptr->GetExponent());
    b_node_ptr = b_node_ptr->GetNext(); // Goes to next pointer.
  }
}