//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

#include <iostream>
#include <string>
#include "LinkedQueue.h" // ADT Queue operations

using namespace std;

void CopyConstructorAndAssignmentTester() {
  LinkedQueue<string> queue;
  string items[] = {"zero", "one", "two", "three", "four", "five"}; // items for queue setup
  // add the items in string items[], into queue
  for (int i = 0; i < 6; i++) {
    cout << "Adding " << items[i] << endl;
    bool success = queue.Enqueue(items[i]);
    // exception if adding fails
    if (!success)
      cout << "Failed to add " << items[i] << " to the queue." << endl;
  }
  cout << "Queue contains, from front to back, zero one two three four five." << endl;
  
  cout << "Checking Copy Constructor tester " << endl;
  
  // creates a new quene called "copy_of_queue" and copys all the items from queue
  LinkedQueue<string> copy_of_queue(queue);
  cout << "Copy of queue contains, from front to back, ";
  // displays contents in copy_of)queue
  for (int i = 0; i < 6; i++)
    {
      cout << " " << copy_of_queue.PeekFront(); // displays front of queue
      copy_of_queue.Dequeue(); // removes the front of queue
    }
  cout << "." << endl;
  
  // setup for testing the operator =
  cout << "Checking Assignment Operator tester " << endl;
  LinkedQueue<string> assigned_queue;
  assigned_queue.Enqueue("ha"); // adds "ha" then "ba" to assigned_queue
  assigned_queue.Enqueue("ba");
  assigned_queue = queue; // erases the contents in assigned_queue and replaces it with the items in queue
  cout << assigned_queue << endl; // displays the contents in assigned_queue using operator <<

  cout << "Assigned queue contains, from front to back, ";
  // displays contents of assigned_queue using function PeekFront()
  for (int i = 0; i < 6; i++)
    {
      cout << " " << assigned_queue.PeekFront();
      assigned_queue.Dequeue(); 
    }
  cout << "." << endl;
  
  cout << "Original queue contains, from front to back,";
  // displays the contents of queue using the function PeekFront()
  for (int i = 0; i < 6; i++) {
    cout << " " << queue.PeekFront();
    queue.Dequeue();
  }
  cout << "." << endl << endl;
}  // end copyConstructorTester

void ConcatenateTester() {
  LinkedQueue<string> queue_1;
  const string items_1[] = {"zero", "one", "two", "three", "four", "five"};

  // add items from string items_1[] into queue_1 using function Enqueue()
  for (int i = 0; i < 6; i++) {
    queue_1.Enqueue(items_1[i]);
  }
  cout << "Queue 1 is " << queue_1 << endl; // displays function of queue_1 using operator << 


  LinkedQueue<string> queue_2;
  const string items_2[] = {"a", "b", "c", "d"};
  // adds contents from string items_2 into queue_2
  for (int i = 0; i < 4; i++) {
    queue_2.Enqueue(items_2[i]);
  }
  cout << "Queue 2 is " << queue_2 << endl; // displays function of queue_1 using operation << 

  // Makes a new queue that has all the contents of queue_1 and queue_2 using operator +
  LinkedQueue<string> queue_3 = queue_1 + queue_2;
  cout << "Concatenated queue is " << queue_3 << endl; // displays contents of queue_3 using operator <<
}

int main()
{
   CopyConstructorAndAssignmentTester();
   ConcatenateTester();
   return 0;
}  // end main

