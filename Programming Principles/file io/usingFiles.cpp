//// This Program reads numbers from a file and 
//// prints to standard output the total numbers,
//// sum, and average of all the numbers read
//
//// Ben Sebring
//
//
//
//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
//
//// Function prototype
//void readFile(string);
//
//
//int main()
//{
//	
//	string fileName = "numbers.txt";
//	readFile(fileName); // function call
//
//	system("pause");
//	return 0;
//}
//
///*
//   ************* readFile function *************
// takes a string as the file name and opens the file 
// the function reads all numbers from the file and 
// prints the total number, sum, and average of all 
// the numbers
//   *********************************************
//*/
//void readFile(string fileName)
//{
//
//	ifstream inFile;
//	// opening the file
//	
//
//	// Declaring neccessary variables
//	float number, sum = 0, totalNum = 0, average;
//
//	// opening the file
//	inFile.open(fileName);
//	if (!inFile)
//		cout << "File not found" << endl;
//
//	// Reading the numbers one by one until the end of file
//	while (inFile >> number)
//	{
//		sum += number; // calculate sum
//		totalNum++;    // update totalNum by adding 1
//		average = sum / totalNum; // calculate average
//	}
//
//	// Output
//	cout << "Number of numbers: " << totalNum << endl;
//	cout << "Sum of the numbers: " << sum << endl;
//	cout << "Average of the numbers: " << average << endl;
//
//	inFile.close(); // close the file
//}