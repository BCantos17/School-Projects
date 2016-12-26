// Bryan Cantos CSCI 235

#include <iostream>
#include <ctype.h>
#include <string>
#include <sstream>
#include <fstream>
#include "BinarySearchTree.h"
#include "LinkedQueue.h"
#include "NotFoundException.h"

using namespace std;

void TextToBST(BinarySearchTree<string, LinkedQueue<int>>& tree_, LinkedQueue<int>& line_queue, 
                string line, int line_num, string& item)
{
  istringstream text(line);
  LinkedQueue<int> queue_count;
  string word;
  int size;
  int counter = 0;
  int prev_count = 0;
  char c;

  while(text >> word) // inserts text into a string word by word
  {
    size = word.size(); // gets total characters of word

    if(word[0] >= 'A' && word[0] <='Z')  // if there are caps, becomes lower case
      word[0] = tolower(word[0]);

    // removes any symbols at the end of the word.
    while(word[size-1] == '.' || word[size-1] == ',' || word[size-1] == '-' || word[size-1] == ':')
      word.erase(size-1);

    // ignores numbers
    if(word[0] >= '1' && word[0] <='9') continue;

    // add word and is line number to the BTS if it isnt in the tree already
    else if(!tree_.Contains(word))
    {
      line_queue.Enqueue(line_num);
      tree_.Add(word, line_queue);
      line_queue.Dequeue();
    } // end if

    // else it just adds the line number to the queue.
    else
    {
      tree_.GetOtherReference(word).Enqueue(line_num);
      queue_count = tree_.GetOther(word); // new queue

      // keeps track of the highest number of occurences for future fucntion
      while(!queue_count.IsEmpty())
      {
        queue_count.Dequeue();
        counter++;
      } //end while
      if(counter > prev_count)
      {
        item = word;
        prev_count = counter;
      }
      counter = 0;
    }
  } // end while
} // TextToBST

void display( string& anItem, LinkedQueue<int>& an_Other)
{
  LinkedQueue<int> temp_queue = an_Other;
  int count = 0;

  // gets the number of counts of a word in the queue
  while(!temp_queue.IsEmpty())
  {
    temp_queue.Dequeue();
    count++;
  }
  // displays the word, count and its lines
  cout << anItem << " Count: " << count << " Lines: ";
  while(!an_Other.IsEmpty()) 
    {
      cout << an_Other.PeekFront() << ", ";
      an_Other.Dequeue();
    }
  cout << "\n"; 
}  // end display

void HighestOccurence(string& anItem, BinarySearchTree<string, LinkedQueue<int>> tree_)
{
  LinkedQueue<int> temp_queue, queue_count;
  int counter = 0; 
  temp_queue = tree_.GetOther(anItem);
  queue_count = temp_queue;

  // gets number of counts of a word
  while(!queue_count.IsEmpty())
  {
    queue_count.Dequeue();
    counter++;
  }

  // displays the highest occurrences 
  cout << "The word with the maximum number of occurrences is " << "'" << anItem << "'" << " which appears " << counter << 
  " times " << "on lines ";
  while(!temp_queue.IsEmpty()) 
  {
    cout << temp_queue.PeekFront() << ", ";
    temp_queue.Dequeue();
  }
  cout << "\n"; 
}

void GetWord(BinarySearchTree<string, LinkedQueue<int>> tree_)
{
  string word_to_find;
  LinkedQueue<int> lines, queue_count;
  int counter = 0;

  cout << "Please type in a word to find in this index" << endl;
  cin >> word_to_find; // user inputted word to find in tree

  // stops if the word is not in tree
  if(!tree_.Contains(word_to_find))
    cout << "Word not in index." << endl;
  // else displays inputted word
  else
  {
    lines = tree_.GetOther(word_to_find);
    queue_count = lines;
    // get counts of a word in a queue
    while(!queue_count.IsEmpty())
    {
      queue_count.Dequeue();
      counter++;
    } // end while

    // displays the word, its count and the lines it appears on
    cout << "The word " << "'" << word_to_find << "'" << " appears " << counter << " times on lines ";
    while(!lines.IsEmpty())
    {
      cout << lines.PeekFront() << ", ";
      lines.Dequeue();
    } // end while

  } // end else

} // end GetWord

void RemoveWord(BinarySearchTree<string, LinkedQueue<int>>& tree_)
{
  string word_to_remove; 

  cout << "Please enter word to remove." << endl;
  cin >> word_to_remove; // user inputted word to remove

  // stops if the word is not in tree
  if(!tree_.Contains(word_to_remove))
    cout << "Word not in index." << endl;
  // calls function Remove() to remove word
  else
  {
    // returns a true value if word is found
    cout << "Word is in index and tree_.Contains returns a " << tree_.Contains(word_to_remove) << "." << endl;
    cout << "Removing word" << endl;
    tree_.Remove(word_to_remove); // removing word
    // returns false value if the word is not in tree
    cout << "Word is removed and tree_.Contains returns a " << tree_.Contains(word_to_remove) << "." << endl;
  }
}

int main() {
  ifstream instream;
  string line, most_item;
  int line_num = 1;
  LinkedQueue<int> line_queue;
  BinarySearchTree<string, LinkedQueue<int>> index;

// open documents and stops program if it isnt found
  instream.open("document1.txt");
  if(instream.fail())
  {
    cout << "document1.txt file opening failed." << endl;
    return 0;
  }

  // gets the text line by line to give to the TextToBTS function
  while(getline(instream, line))
  {
    TextToBST(index, line_queue, line, line_num, most_item);
    line_num++;
  }

// displays the tree in InOrder
  cout << "Index: \n";
  index.InorderTraverse(display);
  cout << "\n";

// gets the total number of nodes
  cout << "Total number of nodes in this tree is " << index.GetNumberOfNodes() << "." << endl;

  // gets the total height ofthe tree
  cout << "The height of the tree is " << index.GetHeight() << "." << endl;
  
  // displays the word that appears the most times
  HighestOccurence(most_item, index);
  // user inputs a word and this searches for it and displays it, the count and its lines
  GetWord(index);
  RemoveWord(index);

  return 0;
} 
