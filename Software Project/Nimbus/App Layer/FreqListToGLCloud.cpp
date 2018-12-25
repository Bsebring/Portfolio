/*  Group 5
	Created 10-3-2018

	Command line arguments
		argv[0]: Name of program (./FreqListToGLCloud)
		argv[1]: Name of text file (Ex: freqList.txt)
		argv[2]: Name of output .tex file

	Command line compile and run using gcc:
	>   gcc FreqListToGLCloud.cpp -o FreqListToGLCloud
	>   ./FreqListToGLCloud freqList.txt

*/

#include <string>
#include <iostream>
#include <fstream>
#include "DocList.h"
#include "FreqList.h"
#include "WordMapMaker.h"
#include "ICloudLayout.h"
#include "LatexMaker.h"
#include "FishEyeLayout.h"
#include "IRenderFactory.h"
#include "LatexFactory.h"
#include "WordList.h"

int main(int argc, char *argv[]){

	string fileName = ""; // Name of input FreqList .txt file (no extension in name)
	string outputFileName = ""; // Name of your output .tex file (no extension in name)

	if (argc < 2) {
		std::cout << "Please provide two arguments: [intputfile.txt] [outputFile]\n\n";

		fileName = "independence.txt"; // Declaration of Independence
		//fileName = "gettysburg.txt"; // Gettysburg Address
		outputFileName = "myTexFile";
	}
	else {
		fileName = argv[1];  // Name of input FreqList .txt file (no extension in name)
		outputFileName = argv[2]; // Name of your output .tex file (no extension in name)
	}

	float percentReduce = 10.0;
	// DocList opens a FreqList file
	DocList* dl = new DocList();
	if (fileName == "")
		return 1;
	dl->read(fileName); // Open file, read into FreqList.
	dl->sortByFreq();
	printf("Length of %s : %d words\n", fileName.c_str(), dl->size());
	dl->reduce(percentReduce); // Reduce the list by some percentage
	printf("Reduced %.0f%% to %d words\n", percentReduce, dl->size());

	WordMapMaker *w = new WordMapMaker();
	WordMap *wMap = w->getWordMap(dl);

	ICloudLayout* fishLayout = NewLayout();
	fishLayout->setLayout(wMap);

	LatexFactory *lf = new LatexFactory();
	IRenderMaker *latexMaker = lf->NewRenderMaker();

	latexMaker->MakeTexFile(wMap, outputFileName);
	
	std::cout << "\n\n";
	//system("pause");
	cin.get();
	return 0;
}

