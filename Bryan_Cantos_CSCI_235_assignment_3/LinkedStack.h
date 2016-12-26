//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT stack: Link-based implementation.
    Listing 7-3.
    @file LinkedStack.h */
 
#ifndef TEACH_CSCI235_STACKADT_LINKEDSTACK_H
#define TEACH_CSCI235_STACKADT_LINKEDSTACK_H

#include "StackInterface.h"
#include "Node.h"
#include "PreconditionViolatedException.h"

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
 public:
  // Constructors and destructor:
  LinkedStack();                                   // Default constructor
  LinkedStack(const LinkedStack<ItemType>& a_stack);// Copy constructor 
  virtual ~LinkedStack();                          // Destructor
  
  // Stack operations:
  bool IsEmpty() const;
  bool Push(const ItemType& new_item);
  bool Pop();
  ItemType Peek() const throw(PreconditionViolatedException);

 private:
  Node<ItemType>* top_ptr_; // Pointer to first node in the chain;
                           // this node contains the stack's top

}; // end LinkedStack

#include "LinkedStack.cpp"
#endif  // TEACH_CSCI235_STACKADT_LINKEDSTACK_H
