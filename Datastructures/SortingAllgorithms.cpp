// Ben Sebring
// CPSC 250 
// 11:00 am class
// 3/6/2017
// Email: bsebring@live.esu.edu
// The following program implements the 
// insertion sort, merge sort, and quick sort algorithms

#include <iostream>
#include <time.h>

using namespace std;
typedef int itemType; // user defined data type

// Function ptototypes
void quickSort(itemType[], int, int, int&, int&);
void quickSort2(itemType[], int, int, int&, int&);
void swap(itemType[], int, int);
int partition(itemType[], int, int, int&);
int partition2(itemType[], int, int, int&);
void sortFirstMiddleLast(itemType[], int, int, int, int&);
void insertionSort(itemType[], int, int &);
void mergeSort(itemType[], int, int, int&);
void merge(itemType[], int, int, int, int&);

// Initializing constants
const int SIZE = 16;
const int MIN_SIZE = 4;

int main()
{
	int mergeCount = 0, insertCount = 0;
	int quickCount = 0;
	clock_t start, stop;

	// Initializing the arrays with random integers
	srand(time(NULL));
	itemType theArray[SIZE];
	for (int i = 0; i < SIZE; i++)
		theArray[i] = rand() % SIZE + 1;

	itemType anArray[SIZE];
	for (int i = 0; i < SIZE; i++)
		anArray[i] = rand() % SIZE + 1;

	itemType array[SIZE];
	for (int i = 0; i < SIZE; i++)
		array[i] = rand() % SIZE + 1;

	itemType array2[SIZE];
	for (int i = 0; i < SIZE; i++)
		array2[i] = rand() % SIZE + 1;

	// Output before and after; including run time and number of comparisons
	cout << "array before insertionSort: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << array[i] << " ";
	}
	start = clock();
	insertionSort(array, SIZE, insertCount);
	stop = clock();
	cout << endl;
	cout << "The number of comparisons in insertionSort is: " << insertCount << endl;
	cout << "Running time for insertionSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "array after insertionSort: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl << endl;

	// Output before and after; including run time and number of comparisons
	cout << "anArray before mergeSort: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << anArray[i] << " ";
	}
	start = clock();
	mergeSort(anArray, 0, SIZE-1, mergeCount);
	stop = clock();
	cout << endl;
	cout << "The number of comparisons in mergeSort is: " << mergeCount << endl;
	cout << "Running time for mergeSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "anArray after mergeSort: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << anArray[i] << " ";
	}
	cout << endl << endl;

	// Output before and after; including run time and number of comparisons
	cout << "theArray before quickSort: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << theArray[i] << " ";
	}
	insertCount = 0;

	start = clock();
	quickSort(theArray, 0, SIZE-1, insertCount, quickCount);
	stop = clock();
	cout << endl;
	cout << "The number of comparisons in quickSort is: " << quickCount << endl;
	cout << "Running time for quickSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "theArray after quickSort: ";
	for (int i = 0; i < SIZE; i++)
	{
		cout << theArray[i] << " ";
	}
	cout << endl << endl;

	// Output before and after; including run time and number of comparisons
	cout << "array2 before quickSort2: ";
	for (int i = 0; i < SIZE; i++)
	{
	cout << array2[i] << " ";
	}
	insertCount = 0;
	quickCount = 0;
	start = clock();
	quickSort2(array2, 0, SIZE - 1, insertCount, quickCount);
	stop = clock();
	cout << endl;
	cout << "The number of comparisons in quickSort2 is: " << quickCount << endl;
	cout << "Running time for quickSort2 is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "array2 after quickSort2: ";
	for (int i = 0; i < SIZE; i++)
	{
	cout << array2[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

/***************
void insertionSort
Description:
	- An iterative sorting algorithm that works from right to left sorting the array element 
	  by element
Input:
	- an array of type itemType
	- int n: the size of the array to be sorted
	- int &insertCount: a counter for number of comparisons
Return:
	- void
****************/
void insertionSort(itemType array[], int n, int &insertCount)
{
	// Loop until unsorted == n (size of the array to be sorted)
	for (int unsorted = 1; unsorted < n; unsorted++)
	{
		int nextItem = array[unsorted];
		int loc = unsorted;
		// Loop until loc == 0 or array[loc - 1] <= nextItem
		while (loc > 0 && (array[loc - 1] > nextItem))
		{
			// increment counter, copy value from left, decrement loc
			insertCount++;
			array[loc] = array[loc - 1];
			loc--;
		}
		// Place nextItem
		array[loc] = nextItem;
	}
}

/***************
void mergeSort
Description:
	- A recursive sorting algorithm that implements the merge function,
	  and has a base case of array size 1
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &mergeCount: a counter for number of comparisons
Return:
	- void
****************/
void mergeSort(itemType theArray[], int first, int last, int &mergeCount)
{
	if (first < last)
	{
		int mid = first + (last - first) / 2;
		mergeSort(theArray, first, mid, mergeCount);
		mergeSort(theArray, mid + 1, last, mergeCount);
		merge(theArray, first, mid, last, mergeCount);
	}
}

/***************
void merge
Description:
	- merges two arrays into one, in ascending order
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int mid: the middle position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &mergeCount: a counter for number of comparisons
Return:
	- void
****************/
void merge(itemType theArray[], int first, int mid, int last, int &mergeCount)
{
	itemType tempArray[SIZE];

	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (theArray[first1] <= theArray[first2])
		{
			// add the value to the left half of the temporary array, and increment first1
			// and mergeCount
			tempArray[index] = theArray[first1];
			first1++;
			mergeCount++;
		}
		else
		{
			// add the value to the right half of the temporary array, and increment first2
			// and mergeCount
			tempArray[index] = theArray[first2];
			first2++;
			mergeCount++;
		}
		index++;
	}
	// Updating the left half of the temporary array based on the index
	while (first1 <= last1)
	{
		mergeCount++;
		tempArray[index] = theArray[first1];
		first1++;
		index++;
	}
	// Updating the right half of the temporary array based on the index
	while (first2 <= last2)
	{
		mergeCount++;
		tempArray[index] = theArray[first2];
		first2++;
		index++;
	}
	// assigning the temporary array back into the original array
	for (index = first; index <= last; index++)
	{
		theArray[index] = tempArray[index];
	}
}

/***************
void quickSort
Description:
	- recursive sorting algorithm that utilizes the partitition function.
	it also uses the insertionSort algorithm for the base case. upon completion,
	the result is an array sorted in ascending order.
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &quickCount: counter for number of comparisons
	- int &insertCount: counter for number of comparisons
Return:
	- void
****************/
void quickSort(itemType theArray[], int first, int last, int &insertCount, int& quickCount)
{
	if ((last - first + 1) < MIN_SIZE)
	{
		insertionSort(theArray, (last+ 1), insertCount);
		quickCount += insertCount;
	}
	else
	{
		// Divide theArray by the pivotIndex
		int pivotIndex = partition(theArray, first, last, quickCount);
		quickSort(theArray, first, pivotIndex - 1, insertCount, quickCount);
		quickSort(theArray, pivotIndex + 1, last, insertCount, quickCount);
	}
}

/***************
void quickSort2
Description:
	- recursive sorting algorithm that utilizes the partitition2 function.
	  it also uses the insertionSort algorithm for the base case. upon completion,
	  the result is an array sorted in ascending order.
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &quickCount: counter for number of comparisons
	- int &insertCount: counter for number of comparisons
Return:
	- void
****************/
void quickSort2(itemType theArray[], int first, int last, int &insertCount, int& quickCount)
{
	if ((last - first + 1) < MIN_SIZE)
	{
		insertionSort(theArray, (last + 1), insertCount);
		quickCount += insertCount;
	}
	else
	{
		// Divide theArray by the pivotIndex
		int pivotIndex = partition2(theArray, first, last, quickCount);
		quickSort2(theArray, first, pivotIndex - 1, insertCount, quickCount);
		quickSort2(theArray, pivotIndex + 1, last, insertCount, quickCount);
	}
}

/***************
void swap
Description:
	- swaps two values of an array
Input:
	- an array of type itemType
	- two integers containing the positions to swap
Return:
	- void
****************/
void swap(itemType array[], int firstPos, int secondPos)
{
	// Swapping the two positions in the array
	int temp = array[firstPos];
	array[firstPos] = array[secondPos];
	array[secondPos] = temp;
}

/***************
int partition
Description:
	- Sorts the first, middle, and last elements of the array in ascending
	  order, then return the proper pivotIndex
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &quickCount: counter for number of comparisons
Return:
	- int pivotIndex
****************/
int partition(itemType array[], int first, int last, int& quickCount)
{
	int mid = first + (last - first) / 2;
	// Sort the first, mid, and last positions in ascending order
	sortFirstMiddleLast(array, first, mid, last, quickCount); 
	swap(array, mid, last - 1); // Swapping 2 values
	int pivotIndex = last - 1;	// Setting the pivotIndex
	int pivot = array[pivotIndex]; // Storing the value at array[pivotIndex]

	int indexFromLeft = first + 1;
	int indexFromRight = last - 2;

	bool done = false;
	// loop until the indexfromLeft >= indexFromRight (or until done == true)
	while (!done)
	{
		// increment indexFromLeft and quickCount until array[indexFromLeft] >= pivot
		while (array[indexFromLeft] < pivot)
		{
			quickCount++;
			indexFromLeft++;
		}
		// decrement indexFromRight and increment quickCount until array[indexFromRight] <= pivot
		while (array[indexFromRight] > pivot)
		{
			indexFromRight--;
			quickCount++;
		}
		if (indexFromLeft < indexFromRight)
		{
			// swap the two array values, and update the indexes
			swap(array, indexFromLeft, indexFromRight);
			indexFromLeft++;
			indexFromRight--;
		}
		else
		{
			// end the outer loop
			done = true;
		}
	}
	// Swap the two values, and update the pivotIndex
	swap(array, pivotIndex, indexFromLeft);
	pivotIndex = indexFromLeft;

	return pivotIndex;
}

/***************
int partition
Description:
	- Sorts the first, middle, and last elements of the array in ascending
	order, then return the proper pivotIndex
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &quickCount: counter for number of comparisons
Return:
	- int pivotIndex
****************/
int partition2(itemType array[], int first, int last, int& quickCount)
{
	int mid = first + (last - first) / 2;
	// Sort the first, mid, and last positions in ascending order
	sortFirstMiddleLast(array, first, mid, last, quickCount);
	swap(array, first, last - 1); // Swapping 2 values
	int pivotIndex = last - 1; // Setting the pivotIndex
	int pivot = array[pivotIndex]; // Storing the value at array[pivotIndex]

	int indexFromLeft = first;
	int indexFromRight = last - 2;

	bool done = false;
	// loop until the indexfromLeft >= indexFromRight (or until done == true)
	while (!done)
	{
		// increment indexFromLeft and quickCount until array[indexFromLeft] >= pivot
		while (array[indexFromLeft] < pivot)
		{
			quickCount++;
			indexFromLeft++;
		}
		// decrement indexFromRight and increment quickCount until array[indexFromRight] <= pivot
		while (array[indexFromRight] > pivot)
		{
			indexFromRight--;
			quickCount++;
		}
		if (indexFromLeft < indexFromRight)
		{
			// swap the two array values, and update the indexes
			swap(array, indexFromLeft, indexFromRight);
			indexFromLeft++;
			indexFromRight--;
		}
		else
		{
			// end the outer loop
			done = true;
		}
	}
	// Swap the two values, and update the pivotIndex
	swap(array, pivotIndex, indexFromLeft);
	pivotIndex = indexFromLeft;

	return pivotIndex;
}

/***************
void sortFirstMiddleLast
Description:
	- Sorts the first, middle, and last elements of the array in ascending
order
Input:
	- an array of type itemType
	- int first: the first position of the array to be sorted
	- int middle: the middle position of the array to be sorted
	- int last:  the last position of the array to be sorted
	- int &quickCount: counter for number of comparisons
Return:
	- int pivotIndex
****************/
void sortFirstMiddleLast(itemType array[], int first, int middle, int last, int &quickCount)
{
	// swap if array[first] > array[middle] and increment quickCount
	if (array[first] > array[middle])
	{
		swap(array, first, middle);
		quickCount++;
	}
	quickCount++;
	// swap if array[middle] > array[last] and increment quickCount
	if (array[middle] > array[last])
	{
		swap(array, middle, last);
		quickCount++;
	}
	quickCount++;
	// swap if array[first] > array[middle] and increment quickCount
	if (array[first] > array[middle])
	{
		swap(array, first, middle);
		quickCount++;
	}
	quickCount++;
}