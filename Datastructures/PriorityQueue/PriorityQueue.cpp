// Ben Sebring
// Email: bsebring@live.esu.edu
// CPSC 250
// 11 AM class
// 4/30/2017

#include "PriorityQueue.h"
#include <iostream>
using namespace std;

priorityQueue::priorityQueue()//constructor
{
	size = 0;
	data = new int[CAPACITY];
}
priorityQueue::~priorityQueue()//destructor
{
	delete data;
}
int priorityQueue::getParent(int index)
{
	return (index - 1) / 2;
}
int priorityQueue::getLeftChild(int index)
{
	return (2 * index) + 1;
}
int priorityQueue::getRightChild(int index)
{
	return (2 * index) + 2;
}
void priorityQueue::swap(int &first, int &second)
{
	int temp = first;
	first = second;
	second = temp;
}
void priorityQueue::insert(int item) //enqueue - heap_insert
{
	size++;
	int i = size - 1;
	while (i > 0 && data[getParent(i)] > item)
	{
		data[i] = data[getParent(i)];
		i = getParent(i);
	}
	data[i] = item;
	cout << "After inserting " << item << " Priority Queue has\n";
	printArray(data);
}
void priorityQueue::printArray(int data[])
{
	for (int i = 0; i < size; i++)
	{
		cout << data[i] << ", ";
	}
	cout << endl << endl;
}
void priorityQueue::heapify(int index)
{
	int smallest = 0;
	int leftchild = getLeftChild(index);
	int rightchild = getRightChild(index);
	
	if (leftchild < size && data[leftchild] < data[index])
	{
		smallest = leftchild;
	}
	else
	{
		smallest = index;
	}
	if (rightchild < size && data[rightchild] < data[smallest])
	{
		smallest = rightchild;
	}
	if (smallest != index)
	{
		swap(data[index], data[smallest]);
		heapify(smallest);
	}
}

	//remove and return the smallest item currently in the priority queue
int priorityQueue::extractMin()//dequeue 
{
	int smallest = min();
	data[0] = data[size - 1];
	size--;
	heapify(0);
	cout << "After extracting the minimum value Priority Queue has\n";
	printArray(data);
	return smallest;
}
bool priorityQueue::empty() const
{
	if (size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int priorityQueue::min() const//return the smallest item
{
	return data[0];
}
