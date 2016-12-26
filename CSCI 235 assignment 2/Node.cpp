//  Bryan Cantos CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Bryan Cantos

/** @file Node.cpp 
    Listing 4-2 */


#include "Node.h"
#include <cstddef>
#include <iostream>

template<class ItemType>
Node<ItemType>::Node() : next_node_(nullptr)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& a_coefficient, const ItemType& an_exponent) : 
	coefficient_(a_coefficient), exponent_(an_exponent), next_node_(nullptr)
{
} // end constructor
  
template<class ItemType>
Node<ItemType>::Node(const ItemType& a_coefficient, const ItemType& an_exponent, Node<ItemType>* next_node) : 
	coefficient_(a_coefficient), exponent_(an_exponent), next_node_(next_node)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::SetCoefficient(const ItemType& a_coefficient)
{
   coefficient_ = a_coefficient;
} // end setCoefficient

template<class ItemType>
void Node<ItemType>::SetExponent(const ItemType& an_exponent)
{
   exponent_ = an_exponent;
} // end setExponent

template<class ItemType>
void Node<ItemType>::SetNext(Node<ItemType>* next_node)
{
   next_node_ = next_node;
} // end setNext_Node_Ptr

template<class ItemType>
ItemType Node<ItemType>::GetCoefficient() const
{
   return coefficient_;
} // end getCoefficient

template<class ItemType>
ItemType Node<ItemType>::GetExponent() const
{
   return exponent_;
} // end getExponent

template<class ItemType>
Node<ItemType>* Node<ItemType>::GetNext() const
{
   return next_node_;
} // end getNext_Node_Ptr
