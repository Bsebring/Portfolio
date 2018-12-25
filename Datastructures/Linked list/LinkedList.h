// A class template for holding a linked list.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>     // For cout and NULL
using namespace std;

class LinkedList
{
private:
   // Declare a structure for the list
   struct ListNode
   {
      int value;
      struct ListNode *next;
   }; 

   ListNode *head;   // List head pointer

public:
   LinkedList();  // Constructor
    ~LinkedList(); // Destructor
   void appendNode(int);
   void insertNode(int);
   void deleteNode(int);
   void displayList();
   int search(int);    // search function
};
#endif
