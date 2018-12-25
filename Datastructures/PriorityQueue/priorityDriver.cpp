#include "PriorityQueue.h"
#include <iostream>
using namespace std;
int main()
{
	priorityQueue myqueue;

	if (myqueue.empty())
		cout << "My priority Queue is empty\n" << endl;

	myqueue.insert(59);
	myqueue.insert(41);
	myqueue.insert(25);
	myqueue.insert(12);
	myqueue.insert(91);
	myqueue.min();
	myqueue.extractMin();

	myqueue.insert(34);
	myqueue.insert(63);
	myqueue.extractMin();

	myqueue.insert(75);
	myqueue.insert(85);
	myqueue.extractMin();



	cout << "Minimum value is ";
	cout << myqueue.min() << endl;

	system("pause");
	return 0;
}