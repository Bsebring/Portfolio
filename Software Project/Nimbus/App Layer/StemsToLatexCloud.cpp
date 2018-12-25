
#include <fstream>
#include <iostream>
#include <string>
#include "FreqMaker.h"
#include "DocList.h"
#include "WordMapMaker.h"
#include "WordMap.h"
#include "StemmedList.h"
#include "ICloudLayout.h"
#include "LatexMaker.h"
#include "WordCount.h"
#include"IRenderFactory.h"
#include"IRenderMaker.h"


//using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Please enter the correct amount of arguments" << endl;
	}
	string inFile = "sl.txt";

	if (*argv[1] == true) {
	inFile = argv[1];
	}
	
	//string stopFile = argv[2];
	int reduceAmount = 25;

	bool flag = true;
	if (*argv[2] == '-t' || *argv[1] == '-t') {
		flag = true;
	}
	
	StemmedList* list = new StemmedList();
	list->read(inFile);
	FreqMaker freqMaker;
	std::cout << "FreqMaker created" << endl;
	DocList* docList = freqMaker.process(list);
	std::cout << "Parsed StemmedList to generate DocList" << endl;
	if (flag == true) {
		docList->write(inFile + "_freq.txt");
	}
	docList->sortByFreq();
	std::cout << "Sorted DocList by frequency" << endl;
	docList->reduce(reduceAmount);
	std::cout << "Reduced DocList by the reduce percentage" << endl;

	WordMapMaker wordMapMaker;
	std::cout << "Created WordMapMaker" << endl;
	WordMap * wordMap = wordMapMaker.getWordMap(docList);
	std::cout << "Parsed DocList to generate WordMap" << endl;

	

	ICloudLayout * cloud = NewLayout();
	std::cout << "Created ICloudLayout" << endl;
	cloud->setLayout(wordMap);
	std::cout << "Used WordMap to set the layout" << endl;
	if (flag == true) {
		wordMap->write(inFile + "_map.txt");
	}
	IRenderFactory* latex = NewRenderFactory();
	latex->NewRenderMaker();
	IRenderMaker* latexMaker = latex->NewRenderMaker();
	std::cout << "Created Latex Maker" << endl;
	latexMaker->MakeTexFile(wordMap, inFile + ".tex");
	std::cout << "Ran MakeTexFile on Latex Maker" << endl;
	
	system("pause");
	return 0;
}
