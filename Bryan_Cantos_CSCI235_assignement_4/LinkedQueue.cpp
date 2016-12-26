//  Bryan Cantos CSCI 235
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Bryan Cantos

/** @file LinkedQueue.cpp */

#include "LinkedQueue.h"  
#include <cassert>
#include "PreconditionViolatedException.h"

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(): back_ptr_(nullptr), front_ptr_(nullptr)
{
}  // end default constructor

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& a_queue)
{  
  CopyNodesFrom(a_queue);
}  // end copy constructor

template<class ItemType>
LinkedQueue<ItemType>& LinkedQueue<ItemType>::operator=(const LinkedQueue<ItemType>& right_hand_side) {
  if (this != &right_hand_side) {  
    // Clear all memory for this queue.
    Clear();
    // Copy the nodes from right_hand_side to this queue.
    CopyNodesFrom(right_hand_side); 

  }
  return *this;  // Return self.
}

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
  Clear();
}  // end destructor


template<class ItemType>
bool LinkedQueue<ItemType>::IsEmpty() const
{
   return back_ptr_ == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedQueue<ItemType>::Enqueue(const ItemType& new_entry)
{
   Node<ItemType>* new_node_ptr = new Node<ItemType>(new_entry);	

   // Insert the new node
   if (IsEmpty())
      front_ptr_ = new_node_ptr;        // Insertion into empty queue
   else
     back_ptr_->SetNext(new_node_ptr); // Insertion into nonempty queue
   
   back_ptr_ = new_node_ptr;            // New node is at back
   
   return true;
}  // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::Dequeue()
{
  if (IsEmpty()) return false;

  // Queue is not empty; delete front
  Node<ItemType>* node_to_delete_ptr = front_ptr_;
  if (front_ptr_ == back_ptr_) {  // Special case: one node in queue
      front_ptr_ = nullptr;
      back_ptr_ = nullptr;
  } else {
    front_ptr_ = front_ptr_->GetNext();
  }
  
  // Return deleted node to system
  node_to_delete_ptr->SetNext(nullptr);
  delete node_to_delete_ptr;
  node_to_delete_ptr = nullptr;
  
  return true;	
}  // end dequeue

template<class ItemType>
ItemType LinkedQueue<ItemType>::PeekFront() const throw(PreconditionViolatedException)
{
  if (IsEmpty())
    throw PreconditionViolatedException("PeekFront() called with empty queue.");
  
  // Queue is not empty; return front
  return front_ptr_->GetItem();
}  // end peekFront

template<class ItemType>
LinkedQueue<ItemType> LinkedQueue<ItemType>::operator+(const LinkedQueue<ItemType> &right_hand_side) const {
  // If this queue is empty return the other one.
  if (IsEmpty()) return right_hand_side;

  LinkedQueue<ItemType> new_queue;
  // Add the nodes from this queue to new_queue.
  new_queue.CopyNodesFrom(*this);


  // Makes a copy of right_hand_side.
  LinkedQueue<ItemType> copy_queue;
  copy_queue.CopyNodesFrom(right_hand_side);
  // Continue adding nodes from the right_hand_side queue to new_queue.
  while(!copy_queue.IsEmpty()){
    new_queue.Enqueue(copy_queue.PeekFront());
    copy_queue.Dequeue();
  }
  
  return new_queue;
}

template<class ItemType>
void LinkedQueue<ItemType>::Clear() {
  while (!IsEmpty())
    Dequeue();
  assert ( (back_ptr_ == nullptr) && (front_ptr_ == nullptr) );
}

template<class ItemType>
void LinkedQueue<ItemType>::CopyNodesFrom(const LinkedQueue& a_queue)
{  
  Node<ItemType>* orig_chain_ptr = a_queue.front_ptr_;  // Points to nodes in original chain

  if (orig_chain_ptr == nullptr) {
    front_ptr_ = nullptr;  // Original queue is empty
    back_ptr_ = nullptr;
    return;
  }   
  
  // Copy first node
  front_ptr_ = new Node<ItemType>();
  front_ptr_->SetItem(orig_chain_ptr->GetItem());
  
  // Advance original-chain pointer
  orig_chain_ptr = orig_chain_ptr->GetNext(); 
  
  // Copy remaining nodes
  Node<ItemType>* new_chain_ptr = front_ptr_;        // Points to last node in new chain
  while (orig_chain_ptr != nullptr) {       

    // Create a new node containing the item stored in orig_chain_ptr.
    Node<ItemType>* next_node_ = new Node<ItemType>();
    next_node_->SetItem(orig_chain_ptr->GetItem());

    // Link the new node to the end of chain.
    new_chain_ptr->SetNext(next_node_);

    // Advance pointers.
    new_chain_ptr = new_chain_ptr->GetNext();
    orig_chain_ptr = orig_chain_ptr->GetNext();

  }  // end while

  new_chain_ptr->SetNext(nullptr); 
  back_ptr_ = new_chain_ptr;
}  // end copy constructor

template<class FriendItemType>
ostream& operator<<(ostream& out_stream, const LinkedQueue<FriendItemType>& output_queue)
{
  // The first node of the queue.
  Node<FriendItemType>* curr_ptr = output_queue.front_ptr_;
  // Traverse each node in the queue and use
  while(curr_ptr!= nullptr){
    out_stream << curr_ptr->GetItem() << " ";
    curr_ptr = curr_ptr->GetNext();
  } // end while
  return out_stream;
} // end operator<<

// End of implementation file.
