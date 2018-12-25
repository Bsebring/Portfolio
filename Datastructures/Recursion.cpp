// Ben Sebring
// CPSC 250 
// 11:00 am class
// 2/11/2017
// Email: bsebring@live.esu.edu
// The following is a collection of recursive programs
// that perform various operations on numbers, arrays, and strings

#include <iostream>
#include <string>

using namespace std;

//Function prototypes
int computeSum(const int anArray[], int n);
int sum(int start, int end);
void writeBackward(string s);
void writeBackward2(string s);
void writeIntegers(int m, int n);
int sumOfSquares(int n);
void reverseDigits(int integer);
void writeLine(char ch, int n);
void writeBlock(char ch, int m, int n);

const int SIZE = 8;

int main()
{
	// Creating the test array
	int anArray[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	// Creating the test string
	string s = "cat";

	// Outputting labels and calling other functions
	cout << "1. computeSum(anArray, 5) returns: " << computeSum(anArray, 5) << endl << endl;
	cout << "2. sum(2, 5) returns: " << sum(2, 5) << endl << endl;

	cout << "3. a. writeBacward(s) returns : ";
	writeBackward(s);
	cout << endl << endl;
	cout << "3. b. writeBackward2(s) returns: ";
	writeBackward2(s);
	cout << endl << endl;

	cout << "4. writeIntegers(2, 5) returns: ";
	writeIntegers(2, 5);
	cout << endl << endl;

	cout << "5. sumOfSquares(5) returns: " << sumOfSquares(5) << endl << endl;
	cout << "6. reverseDigits(1234) returns: ";
	reverseDigits(1234);
	cout << endl << endl;

	cout << "7. a. writeLine('*', 5) returns :\n";
	writeLine('*', 5);
	cout << endl << endl;

	cout << "7. b. writeBlock('*', 5, 3) returns: \n";
	writeBlock('*', 5, 3);
	cout << endl << endl;



	system("pause");
	return 0;
}

//Function Definitions

/* int computeSum(const int anArray[], int n)
computes the sum of the given number of integers in an array

preconditions: 
	the array has at least n integers

parameters:
	const int anArray[] - an array of integers
	int n - the number of integers from the array to sum together

postconditions: n/a

return:
	integer number or anArray[n-1] + recursive call to the function

*/
int computeSum(const int anArray[], int n)
{
	// Base case
	if (n == 1)
		return 1;
	else
		// Add the n-1 position to the return of the funtion with one less number to evaluate
		return anArray[n - 1] + computeSum(anArray, n - 1);
}

/* int sum(int start, int end)
computes the sum of all integers from start to end

preconditions:
	end >= start

parameters:
	int start - the number to start adding with
	int end - the last number to be added

postconditions: n/a

return:
	integer number or end + recursive call to the function
*/
int sum(int start, int end)
{
	// Base case
	if (start == end)
		return start;
	else
		// Add end to the function call and decrement the end
		return end + sum(start, end - 1);
}

/* void writeBackward(string s)
writes a string in reverse order

preconditions:
	n/a

parameters:
	string s - the string to be written in reverse
*/
void writeBackward(string s)
{
	// Initialize length to the length of string s
	int length = s.length();
	// Base case
	if (length == 1)
		cout << s;
	else
	{
		// Print the last letter in string s
		cout << s.substr(length - 1, 1);
		// Call to function with one less letter
		writeBackward(s.substr(0, length - 1));
	}
}

/* void writeBackward2(string s)
A different aproach to writing a string in reverse order

preconditions:
	n/a

parameters:
	string s - the string to be written in reverse
*/
void writeBackward2(string s)
{
	// Initializing length to the size of the string
	int length = s.size();
	// Base case is length == 0 because then this function prints nothing
	if (length > 0)
	{
		// Call the function without the first character in string s
		writeBackward2(s.substr(length - (length - 1), length));
		// Print the first character in string s
		cout << s.substr(0, 1);
	}

}

/* void writeIntegers(int m, int n)
writes the integers m through n (inclusively) to the console
sepparated by a comma and a space (, ).

preconditions:
	m > 0
	m < n

parameters:
	int m - the first integer to print
	int n - the last integer to print
*/
void writeIntegers(int m, int n)
{
	// Base case
	if (n == m)
		cout << n << ", ";
	else
	{
		// Call the function with n-1
		writeIntegers(m, n - 1);
		cout << n << ", ";
	}
}

/* int sumOfSquares(int n)
computes the sum of the squares from 1 through n (inclusively)

preconditions:
	n > 0

parameters:
	int n - the last number to square and sum together

postconditions: 
	n/a

return:
	integer number or (n*n) + recursive call to the function
*/
int sumOfSquares(int n)
{
	// Base case
	if (n == 1)
		return 1;
	// Add (n*n) to the function call and decriment n
	else
		return n*n + sumOfSquares(n - 1);

}

/* void reverseDigits(int integer)
Prints an integer to the console in reverse order

preconditions:
	integer > 0

parameters:
	int integer - the number to be displayed in reverse order
*/
void reverseDigits(int integer)
{
	// Base case because 1-9 is one character
	if (integer < 10)
		cout << integer;
	else
	{
		// Print the last character by utilizing modulo operator
		cout << integer % 10;
		// call function and drop last number by dividing by 10
		reverseDigits(integer / 10);
	}
}

/* void writeLine(char ch, int n)
Prints out a specific number of any character on one line

preconditions:
	n/a

parameters:
	int n - the number of character for the line
	char ch - the character to be printed n times
*/
void writeLine(char ch, int n)
{
	// Base case
	if (n == 1)
		cout << ch << endl;
	else
	{
		cout << ch;
		// Call the function with one less star needed
		writeLine(ch, n - 1);
		
	}
}

/* void writeBlock(char ch, int m, int n)
Prints out a block of a specific character, 
using the writeLine function

preconditions:
n/a

parameters:
int n - the number of characters for the line
char ch - the character to be printed n times
int m - he number of times to call writeLine
*/
void writeBlock(char ch, int m, int n)
{
	// Base case
	// Call writeLine to print a single line
	if (m == 1)
		writeLine(ch, n);
	else
	{
		// Call writeBlock with one less row
		writeBlock(ch, m - 1, n);
		// Call writeLine to print a single line
		writeLine(ch, n);
	}
}