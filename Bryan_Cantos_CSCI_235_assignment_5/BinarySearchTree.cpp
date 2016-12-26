//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinarySearchTree.cpp */
#include <iostream>

#include "BinarySearchTree.h" 
#include "BinaryNode.h" 
#include "LinkedQueue.h"

template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>::BinarySearchTree(const BinarySearchTree<ItemType, OtherType>& tree)
{
  root_ = CopyTree(tree.root_);
}  // end copy constructor

template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>& BinarySearchTree<ItemType, OtherType>::operator=(const BinarySearchTree<ItemType, OtherType>& right_hand_side)
{
  if (this != &right_hand_side) {  
  // Clear all memory for this tree.
  Clear();
  // Copy the nodes from right_hand_side to this tree.
  CopyTree(right_hand_side); 
  }
  return *this;  // Return self.
}  // end operator=


template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>::~BinarySearchTree()
{
   DestroyTree(root_);
}  // end destructor


template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::IsEmpty() const
{
   return root_ == nullptr;
}  // end isEmpty

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetHeight() const
{
   return GetHeightHelper(root_);
}  // end getHeight

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetNumberOfNodes() const
{
   return GetNumberOfNodesHelper(root_);
}  // end getNumberOfNodes

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Clear()
{
   DestroyTree(root_);
   root_ = nullptr;
}  // end clear

template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::Remove(const ItemType& target)
{
  bool success = false;
  RemoveValue(root_, target, success);
  return success;
}  // end remove

template<class ItemType, class OtherType>
OtherType BinarySearchTree<ItemType, OtherType>::GetOther(const ItemType& an_entry) const throw(NotFoundException)
{
  BinaryNode<ItemType, OtherType>* temp_ptr = new BinaryNode<ItemType, OtherType>;
  temp_ptr = FindNode(root_, an_entry); // finds the node that contains the item

// exception if the item is not found
  if(temp_ptr == nullptr)
    throw NotFoundException("Not Found");

  else
    return temp_ptr->GetOther(); // returns the othertype of the node
}  // end getEntry

template<class ItemType, class OtherType>
OtherType& BinarySearchTree<ItemType, OtherType>::GetOtherReference(const ItemType& an_entry) throw(NotFoundException)
{
  BinaryNode<ItemType, OtherType>* temp_ptr = new BinaryNode<ItemType, OtherType>;
  temp_ptr = FindNode(root_, an_entry);// finds the node that contains the item

// exception if the item is not found
  if(temp_ptr == nullptr)
    throw NotFoundException("Not Found");

  else
    return temp_ptr->GetOtherReference();// returns the othertype of the node
}  // end getEntry

template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>:: Contains(const ItemType& an_entry) const
{

  BinaryNode<ItemType, OtherType>* temp_ptr = new BinaryNode<ItemType, OtherType>;

  temp_ptr = FindNode(root_, an_entry); // finds the nodes of the given entry

  if(temp_ptr == nullptr) // returns false if the entry is not found
    return false;
  else if (temp_ptr->GetItem() == an_entry) 
    return true; // returns true if found
}  // end contains


template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PreorderTraverse(void visit(ItemType&)) const
{
   Preorder(visit, root_);
}  // end preorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::InorderTraverse(void visit(ItemType&, OtherType&)) const
{
   Inorder(visit, root_);
}  // end inorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PostorderTraverse(void visit(ItemType&)) const
{
   Postorder(visit, root_);
}  // end postorderTraverse

/*template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::LevelorderTraverse(void visit(ItemType&)) const;
{
  Levelorder(visit, root_);
}*/


//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetHeightHelper(BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr == nullptr)
      return 0;
   else
      return 1 + max(GetHeightHelper(node_ptr->GetLeftPtr()), 
                     GetHeightHelper(node_ptr->GetRightPtr()));
}  // end GetHeightHelper

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetNumberOfNodesHelper(BinaryNode<ItemType, OtherType>* node_ptr) const
{
  if (node_ptr == nullptr)
  return 0;
  else
    return 1 + GetNumberOfNodesHelper(node_ptr->GetLeftPtr()) + GetNumberOfNodesHelper(node_ptr->GetRightPtr());
}  // end GetNumberOfNodesHelper


template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::Add(const ItemType& new_item, const OtherType& new_other)
{
   BinaryNode<ItemType, OtherType>* new_node = new BinaryNode<ItemType, OtherType>(new_item);
   new_node->SetOther(new_other);
   root_ = InsertInorder(root_, new_node);
   return true;
}  // end add


//////////////////////////////////////////////////////////////
//
//      Protected Utility Methods Section
//
//////////////////////////////////////////////////////////////

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::InsertInorder(BinaryNode<ItemType, OtherType>* subTreePtr,
										      BinaryNode<ItemType, OtherType>* newNodePtr)
{
  BinaryNode<ItemType, OtherType>* temp_ptr = new BinaryNode<ItemType, OtherType>;
  // starts a new tree
  if(subTreePtr == nullptr)
    return newNodePtr;
  // new entry goes to the left of the tree if the current value is less than
  if(newNodePtr->GetItem() < subTreePtr->GetItem())
  {
    temp_ptr = InsertInorder(subTreePtr->GetLeftPtr(), newNodePtr);
    subTreePtr->SetLeftPtr(temp_ptr);
  }
  // else goes to the right if it is greater than
  else
  {
    temp_ptr = InsertInorder(subTreePtr->GetRightPtr(), newNodePtr);
    subTreePtr->SetRightPtr(temp_ptr);
  }
  return subTreePtr;
}  // end insertInorder

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveValue(BinaryNode<ItemType, OtherType>* subTreePtr,
										    const ItemType target, 
										    bool& success)
{
  BinaryNode<ItemType, OtherType>* temp_ptr = new BinaryNode<ItemType, OtherType>;

// if value is not found, returns false
  if(subTreePtr == nullptr)
  {
    success = false;
    return nullptr;
  }
  // if value is found, begins removenode function and returns true
  if(subTreePtr->GetItem() == target)
  {
    subTreePtr = RemoveNode(subTreePtr);
    success = true;
    return subTreePtr;
  }
  // is target is less than cuurent node value, goes to left of the tree
  if(subTreePtr->GetItem() > target)
  {
    temp_ptr = RemoveValue(subTreePtr->GetLeftPtr(), target, success);
    subTreePtr->SetLeftPtr(temp_ptr);
    return subTreePtr;
  }
  // else goes to right if it is greater than
  else
  {
    temp_ptr = RemoveValue(subTreePtr->GetRightPtr(), target, success);
    subTreePtr->SetRightPtr(temp_ptr);
    return subTreePtr;
  }
}  // end RemoveValue

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveNode(BinaryNode<ItemType, OtherType>* node_ptr)
{
  BinaryNode<ItemType, OtherType>* node_to_connect = new BinaryNode<ItemType, OtherType>;
  BinaryNode<ItemType, OtherType>* temp_ptr = new BinaryNode<ItemType, OtherType>;
  ItemType new_value;

// deletes node if it doesnt have any child 
  if(node_ptr->IsLeaf())
  {
    delete node_ptr;
    node_ptr = nullptr;
    return node_ptr;
  }
  // else if it has one child, connects the previous node to the next one
  else if( !node_ptr->IsLeaf() && (node_ptr->GetLeftPtr() == nullptr || node_ptr->GetRightPtr() == nullptr))
  {
    if(node_ptr->GetLeftPtr() != nullptr)
      node_to_connect = node_ptr->GetLeftPtr();
    else
      node_to_connect = node_ptr->GetRightPtr();
    delete node_ptr;
    node_ptr = nullptr;
    return node_to_connect;
  }
  // else if it has 2 child, finds the left most node of the right child and gets replaced by it
  else
  {
    temp_ptr = RemoveLeftmostNode(node_ptr->GetRightPtr(), new_value);
    node_ptr->SetRightPtr(temp_ptr);
    node_ptr->SetItem(new_value);
    return node_ptr;
  }

}  // end RemoveNode

template<class ItemType, class OtherType> 
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveLeftmostNode(BinaryNode<ItemType, OtherType>* nodePtr,
                                                                     ItemType& inorderSuccessor)
{
  // returns left most nodes
  if(nodePtr->GetLeftPtr() == nullptr)
  {
    inorderSuccessor = nodePtr->GetItem();
    return RemoveNode(nodePtr);
  }
  // finds left most node
  nodePtr->SetLeftPtr(RemoveLeftmostNode(nodePtr->GetLeftPtr(), inorderSuccessor));
  return nodePtr;
}  // end RemoveLeftmostNode


template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::FindNode(BinaryNode<ItemType, OtherType>* subTreePtr,
                                                           const ItemType& target) const 
{
  // returns nullptr if node is not in tree
  if(subTreePtr == nullptr)
  return nullptr;
// returns target node
  else if (subTreePtr->GetItem() == target)
    return subTreePtr;
// else continues to search through tree
  else if(target < subTreePtr->GetItem())
    return FindNode(subTreePtr->GetLeftPtr(), target);
  else
    return FindNode(subTreePtr->GetRightPtr(), target);

}  // end findNode

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::CopyTree(const BinaryNode<ItemType, OtherType>* node_ptr) const
{
   BinaryNode<ItemType, OtherType>* new_tree_ptr = nullptr;
   // Copy tree nodes during a preorder traversal
   if (node_ptr != nullptr) { 
     // Copy node
     new_tree_ptr = new BinaryNode<ItemType, OtherType>(node_ptr->GetItem());
     new_tree_ptr->SetOther(node_ptr->GetOther());

     new_tree_ptr->SetLeftPtr(CopyTree(node_ptr->GetLeftPtr()));
     new_tree_ptr->SetRightPtr(CopyTree(node_ptr->GetRightPtr()));
   }  // end if
   return new_tree_ptr;
}  // end copyTree

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::DestroyTree(BinaryNode<ItemType, OtherType>* node_ptr)
{
   if (node_ptr != nullptr) {
      DestroyTree(node_ptr->GetLeftPtr());
      DestroyTree(node_ptr->GetRightPtr());
      delete node_ptr;
   }  // end if
}  // end destroyTree

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Preorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
      Preorder(visit, node_ptr->GetLeftPtr());
      Preorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end preorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Inorder(void visit(ItemType&, OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Inorder(visit, node_ptr->GetLeftPtr());
      ItemType theItem = node_ptr->GetItem();
      OtherType theOther = node_ptr->GetOther();
      visit(theItem, theOther);
      Inorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end inorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Postorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Postorder(visit, node_ptr->GetLeftPtr());
      Postorder(visit, node_ptr->GetRightPtr());
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
   } // end if
}  // end postorder

/*void BinarySearchTree<ItemType, OtherType>::Levelorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>*node_ptr) const;
{
  LinkedQueue<ItemType> tree;

  tree.Enqueue(node_ptr->GetItem);
}*/








