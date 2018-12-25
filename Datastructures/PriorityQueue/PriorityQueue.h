#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

class priorityQueue
{
private:
	int size;
	int *data;

public:
	static const int CAPACITY = 50;
	priorityQueue();//constructor
	~priorityQueue();//destructor
	int getParent(int index);
	int getLeftChild(int index);
	int getRightChild(int index);
	void swap(int &, int &);
	void insert(int item); //enqueue - heap_insert
	void printArray(int[]);
	void heapify(int index);

	//remove and return the smallest item currently in the priority queue
	int extractMin();//dequeue 
	bool empty() const;
	int min() const; //return the smallest item
};
#endif
