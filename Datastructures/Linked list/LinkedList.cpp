// Ben Sebring  CPSC 250 11:00AM class
// function definitions for LinkedList.h
// The methods in this file can be used to 
// make a link based list using a bode structure
#include "LinkedList.h"	

LinkedList::LinkedList() // Constructor (default)
{

	head = NULL;
}


LinkedList::~LinkedList() {}// Destructor

/* 
appendNode adds a new node to the end of the list,
unless the list is empty.

Parameters: int num
no return
*/
void LinkedList::appendNode(int num)
{
	// Declare nodes for fuction
	ListNode *newNode;
	ListNode *ptrNode;

	// Dynamically allocate the memory for a node
	newNode = new ListNode;

	// Assign the value to be added to the proper location
	newNode->value = num;
	// Initialize pointer to null
	newNode->next = NULL;
	if (!head)
	{
		// If the list is empty, 
		// newNode becomes the first node
		head = newNode;
	}
	else
	{
		// Otherwise search until the end of the list
		// Starting with the head
		ptrNode = head;
		while (ptrNode->next)
		{
			ptrNode = ptrNode->next;
		}
		// Once at the end assign that pointer to point to
		// newNode
		ptrNode->next = newNode;
	}

}

/*
insertNode traverses through the list and places th current
value into the proper sorted location

Precondition: Sorted list
Parameters: int num
no return
*/
void LinkedList::insertNode(int num)
{
	// Declare nodes for fuction
	ListNode *newNode;
	ListNode *ptrNode;
	ListNode *preNode = NULL;

	// Dynamically allocate the memory for a node
	newNode = new ListNode;

	// Assign num to value and null to next;
	newNode->value = num;
	newNode->next = NULL;

	// Set ptrNode to start at the beginnig of the list
	ptrNode = head;

	if (ptrNode)
	{
		while (ptrNode->value < newNode->value && ptrNode->next)
		{// Traverse the list until the end, or until ptrNode
		 // contains a value larger than newNodes value
			preNode = ptrNode;
			ptrNode = ptrNode->next;
			if (!ptrNode->next && ptrNode->value < newNode->value)
			{
			 // If the end is reached, it means newNode 
			 // has the largest value, so add it to the end and break;
				ptrNode->next = newNode;
				break;
			}
		}
		// If ptrNode is the same or larger than newNode
		// insert the node between preNode and newNode
		if (ptrNode->value >= newNode->value)
		{
			preNode->next = newNode;
			newNode->next = ptrNode;
		}
	}
	else
	{
		// Only if the list is empty add the node to the front
		head = newNode;
	}


}

/*
deleteNode searches for a value and deletes it 
from the list.

Parameters: int num
no return
*/
void LinkedList::deleteNode(int num)
{
	// Declaring nodes for function
	ListNode *ptrNode = head;
	ListNode *preNode = NULL;
	if (ptrNode)
	{
		// Search for the value to delete
		// while keeping track of the one before it
		while (ptrNode->value != num)
		{
			preNode = ptrNode;
			ptrNode = ptrNode->next;
		}
		// Remove ptrNode from the list and maintaining 
		// all links
		preNode->next = ptrNode->next;

		// deleting the node from memory
		delete ptrNode;
	}
}
/*
displayList prints the list from beginning to end

Parameters: none
no return
*/
void LinkedList::displayList()
{
	ListNode *ptrNode;
	ptrNode = head;
	// Continue until the end of the list
	while (ptrNode != NULL)
	{
		cout << ptrNode->value << endl;
		// move to the next node
		ptrNode = ptrNode->next;
	}
}

/*
Search searches the list for a value and returns its position

parameters: int num
returns: the position of the value, or zero if the
         value is not in the list
*/
int LinkedList::search(int num)   // search function
{
	ListNode *ptrNode = head;

	//variable to hold positon
	int nodNum = 1;

	// return 0 if the list is empty
	if (ptrNode == NULL)
	{
		return 0;
	}

	// Continue searching until ptrNode->value is equal to
	// the number you are searching for, or the end of the list
	while (ptrNode->value != num && ptrNode->next != NULL)
	{
		ptrNode = ptrNode->next;
		nodNum++;
	}
	if (ptrNode->value == num)
	{
		// return the position of the number in the list
		return nodNum;
	}
	else
	{
		// return 0 if the value is not in the list
		return 0;
	}
}
