//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 7-4.
    @file LinkedStack.cpp */

#include <cassert>        // For assert
#include "LinkedStack.h"  // Header file

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : top_ptr_(nullptr)
{
}  // end default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& a_stack)
{
   // Point to nodes in original chain
   Node<ItemType>* orig_chain_ptr = a_stack.top_ptr_;
   
   if (orig_chain_ptr == nullptr)
      top_ptr_ = nullptr;  // Original stack is empty
   else
   {
      // Copy first node
      top_ptr_ = new Node<ItemType>();
      top_ptr_->SetItem(orig_chain_ptr->GetItem());
      
      // Point to last node in new chain
      Node<ItemType>* new_chain_ptr = top_ptr_;     
      
      // Advance original-chain pointer
      orig_chain_ptr = orig_chain_ptr->GetNext();
      
      // Copy remaining nodes
      while (orig_chain_ptr != nullptr)
      {                  
         // Link new node to end of new chain
	new_chain_ptr->SetNext(new Node<ItemType>(orig_chain_ptr->GetItem()));   
	
	// Advance pointer to new last node      
	new_chain_ptr = new_chain_ptr->GetNext();
        
	// Advance original-chain pointer
	orig_chain_ptr = orig_chain_ptr->GetNext();
      }  // end while
      
      new_chain_ptr->SetNext(nullptr);           // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	// Pop until stack is empty
	while (!IsEmpty())
	  Pop();
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::IsEmpty() const
{
	return top_ptr_ == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedStack<ItemType>::Push(const ItemType& new_item) {
  Node<ItemType>* new_node_ptr = new Node<ItemType>(new_item, top_ptr_);				
  top_ptr_ = new_node_ptr;
  new_node_ptr = nullptr;
  return true;
}  // end push
 
 template<class ItemType>
 bool LinkedStack<ItemType>::Pop()
 {
   if (IsEmpty()) return false;
   // Stack is not empty; delete top
   Node<ItemType>* node_to_delete_ptr = top_ptr_;
   top_ptr_ = top_ptr_->GetNext();
   
   // Return deleted node to system
   node_to_delete_ptr->SetNext(nullptr);
   delete node_to_delete_ptr;
   node_to_delete_ptr = nullptr;
   
   return true;
}  // end pop
 
 template<class ItemType>	
 ItemType LinkedStack<ItemType>::Peek() const throw(PreconditionViolatedException)
 {
   if (IsEmpty())
     throw PreconditionViolatedException("Peek() called with empty stack"); 
   return top_ptr_->GetItem();
 }  // end peek
 // End of implementation file.
