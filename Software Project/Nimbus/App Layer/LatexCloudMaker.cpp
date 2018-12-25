#include "IRenderFactory.h"// <-------------------interface
#include "ICloudLayout.h"// <-------------------interface
#include "WordList.h"// //
#include "StemMaker.h"// //
#include "StemmedList.h"// //
#include "WordListParser.h"// // 
#include "FreqMaker.h"// // 
#include "Doclist.h"// // 
#include "WordMapMaker.h"// // 
#include "WordMap.h"// //
#include "LatexMaker.h"// //

#include <iostream>
#include <string>
#include <fstream>

#define n 10

int main(int argc, char * argv[]) // passed file name to read from, write to and tracing flag
{
	if (argc != 4) {
		std::cout << "Error: Incorrect number of command line arguments." << std::endl;
		std::cout << "First arguement: input file" << std::endl;
		std::cout << "Second argument: stopfile" << std::endl;
		std::cout << "Third argument: \"t\" for tracing on, \"f\" for off" << std::endl;
		std::system("pause");
		return 0;
	}

	std::string inputFileName = argv[1];
	std::string stopFileName = argv[2];
	bool flag = false;
	if (*argv[3] == 't') {
		flag = true;
	}

	// LAST MINUTE FIXES SPONSORED BY BAND-AID (TM)
	std::ifstream bandaid;
	bandaid.open(inputFileName);
	if (!bandaid.is_open())
	{
		std::cout << "Error: Unable to open " + inputFileName << '\n';
		return 0;
	}
	bandaid.close();
	bandaid.open(stopFileName);
	if (!bandaid.is_open())
	{
		std::cout << "Error: Unable to open " + stopFileName << '\n';
		return 0;
	}
	bandaid.close();

	WordListParser parser; // created wordlist parser
	WordList* allWords = parser.parse(inputFileName); // create wordlist using the parser that we just created
	StemMaker stemMaker; //create stemmaker
	stemMaker.initialize(stopFileName); // write to the stop file name
	StemmedList* stems = stemMaker.stem(allWords); //generates the stemmed list with the word list we previously created

	if (flag == true) // if we are tracing
		stems->write(inputFileName + "_stems.txt"); // write to the file and change the name of the file to show its stems


													//-----------------------------------------------------------------------------------------------------------------------------------------------

	FreqMaker freqMaker; // create freqency maker
	DocList* docList = freqMaker.process(stems); // create doclist with the stem list using freq maker, doclist is a 
												 //freqlist with the associated filename that we created earlier
	if (flag == true) // if we are tracing
		docList->write(inputFileName + "_freq.txt"); // write to a file that is a freqlist

													 //-----------------------------------------------------------------------------------------------------------------------------------------------
	docList->sortByFreq(); // sort by frequency
	docList->reduce(n);  // 10.0 is a test number 

	WordMapMaker wordMapMaker; // create wordmap

	WordMap * wordMap = wordMapMaker.getWordMap(docList);

	if (flag == true) // if he have tracing
		wordMap->write(inputFileName + "_map.txt"); // write current junk to a map file

													//-----------------------------------------------------------------------------------------------------------------------------------------------

	ICloudLayout* cloud = NewLayout(); // replace with a call to the factory method
	cloud->setLayout(wordMap); // set the layout that we are going to use
	LatexMaker latex; // create the latexmaker so we can later pass it our current doc

	latex.MakeTexFile(wordMap, (inputFileName)); // create the final doc

														  //-----------------------------------------------------------------------------------------------------------------------------------------------

}