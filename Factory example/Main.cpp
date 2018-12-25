#include "IFactory.h"
#include "FilterMgr.h"
#include <iostream>
#include "InteractiveFix.h"
#include "FileFix.h"
using namespace std;
bool done = false;

int main() {
	FilterMgr fm;
	string input, type = "";
	while (!done) {
		cout << "Enter your choice of the folowing filters <q to quit>" <<
			fm.getChoices() << "\n";
		cin >> type;

		if (type == "q")
		{
			done = true;
			break;
		}
		else if (type != "lowercase" && type != "uppercase" && type != "encrypt")
		{
			cout << "Sorry, that is not a valid coice. Please try again.\n";
			continue;
		}


		IFactory* choice; 
		choice = selectFilter(type);
		string mode;
		while (mode != "q")
		{
			std::cout << "Enter i for interactive word fix, and f to fix an entire file <q to quit>.\n";
			cin >> mode;
			done = true;
			while (mode != "q" && mode != "i" && mode != "f")
			{
				std::cout << "Please choose a proper input!\nEnter i for interactive word fix, and f to fix an entire file <q to quit>.\n";
				cin >> mode;
			}

			if (mode == "q")
			{
				done = true;
				break;
			}
			else if (mode == "i")
			{
				InteractiveFix* wordFix = new InteractiveFix(choice);
				//call DoInteractiveFix()
				wordFix->DoInteractiveSession();
				delete wordFix;

			}
			else if (mode == "f")
			{
				//prompt for file name
				string inputFile;
				cout << "Enter the file you would like to fix: ";
				cin >> inputFile;
				cout << "\nAttempting to open file...\n\n";
				//call FileFix()
				FileFix* fileFix = new FileFix(choice);
				cout << "\nApplying filter to output file...\n";
				fileFix->ConvertFile(inputFile);
				cout << "\nFileConversion successful!!!\n";
				delete fileFix;
			}
		}

		delete choice, fm;
	}
	system("pause");
	return 0;
}