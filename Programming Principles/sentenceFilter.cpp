//#include <iostream>
//#include <fstream>
//#include <cctype>	// Needed for tolower function.
//#include <string>
//using namespace std;
//
//
//int main()
//{
//	const int SIZE = 81;		// Constant size of filenames
//								// Arrays for file names
//	char fileName1[SIZE];
//	char fileName2[SIZE];
//
//	char ch, ch2;		// Holds character 
//
//	ifstream inFile;	// Input file stream object
//	fstream outFile;	// Output file stream object
//
//
//						// Get FIRST file from user
//	//cout << "Enter the input file name: ";
//	//cin >> fileName1;
//	// Open file for input
//	inFile.open("text.txt");
//	// Test file for errors.
//	 if (!inFile)
//	{
//	cout << "The file " << fileName1 
//	 << " could not be opened.";
//	return(1);
//	}
//	// Get SECOND file(user created) from user 
//	cout << "Enter the output file name: ";
//	cin >> fileName2;
//	// Open and create fileName2 for output
//	outFile.open(fileName2, ios::out);
//	// Process files
//	inFile.get(ch);
//	while (!inFile.eof())
//	{
//		if (ch == '.')
//		{
//			outFile.put(ch);
//			inFile.get(ch2);
//			if (isalpha(ch2))
//			{
//				outFile.put(toupper(ch2));
//			}
//			else
//			{
//				outFile.put(ch2);
//				inFile.get(ch2);
//				outFile.put(toupper(ch2));
//			}
//
//		}
//		else if (isalpha(ch))
//		{
//			outFile.put(tolower(ch));
//		}
//		else
//		{
//			outFile.put(ch);
//		}
//
//
//		inFile.get(ch);
//	}
//	// Close files
//	inFile.close();
//	outFile.close();
//	system("pause");
//	return 0;
//}