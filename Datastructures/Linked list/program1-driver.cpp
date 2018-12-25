// List search
#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
   // Create an instance of LinkedList
   LinkedList list;
  
   cout << "\nHere are the initial values:\n";
   list.displayList();
   // Build the list
   list.appendNode(2);    // Append 2
   list.appendNode(4);    // Append 4
   list.appendNode(6);    // Append 6
   list.appendNode(8);    // Append 8
   list.appendNode(9);    // Append 9
   list.insertNode(3);
   list.insertNode(9);
   list.insertNode(13);

   // Display the list nodes.
   cout << "\nHere are the values:\n";
   list.displayList();
   cout << endl;

   // Search for the value 6.
   cout << "\nSearching for the value 6.";
   cout << "\nFound in node number:  " 
        << list.search(6) << endl << endl;
   // Search for the value 10.
   cout << "\nSearching for the value 10.";
   cout << "\nFound in node number:  " 
        << list.search(10) << endl << endl;

   list.deleteNode(6);
   list.deleteNode(9);
   list.insertNode(10);
   // Display the list nodes.
   cout << "\nHere are the values:\n";
   list.displayList();
   cout << endl;

   // Search for the value 6.
   cout << "\nSearching for the value 6.";
   cout << "\nFound in node number:  " 
        << list.search(6) << endl << endl;

   // Search for the value 10.
   cout << "\nSearching for the value 10.";
   cout << "\nFound in node number:  " 
        << list.search(10) << endl << endl;
   
   system("pause");
   return 0;
}
