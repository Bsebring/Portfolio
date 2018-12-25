#include <fstream>
#include <iostream>
#include <string>
#include "StemMaker.h"
#include "WordListParser.h"
#include "StemmedList.h"
#include "FreqMaker.h"
#include "DocList.h"
#include "WordMapMaker.h"
#include "WordMap.h"
#include "Rectangle.h"
#include "MapItem.h"
#include "FontSize.h"
#include "ICloudLayout.h"
#include "IRenderMaker.h"
#include "IRenderFactory.h"
#include "GLMaker.h"
#include "WordCount.h"

#include "glut.h"

#define N 10

using namespace std;

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);

	if (argc != 4) {
		cout << "Error: Incorrect number of command line arguments." << endl;
		cout << "First arguement: input file" << endl;
		cout << "Second argument: stopfile" << endl;
		cout << "Third argument: \"-t\" for tracing on, \"-f\" for off" << endl;
		system("pause");
		return 0;
	}
	string inputFile = argv[1];
	string stopFile = argv[2];
	bool flag = false;
	std::string s = &*argv[3];

	if (s.compare("-t") == 0) {
		flag = true;
	}

	// LAST MINUTE FIXES SPONSORED BY BAND-AID (TM)
	std::ifstream bandaid;
	bandaid.open(inputFile);
	if (!bandaid.is_open())
	{
		std::cout << "Error: Unable to open " + inputFile << '\n';
		return 0;
	}
	bandaid.close();
	bandaid.open(stopFile);
	if (!bandaid.is_open())
	{
		std::cout << "Error: Unable to open " + stopFile << '\n';
		return 0;
	}
	bandaid.close();

	WordListParser parser;
	WordList * allWords = parser.parse(inputFile);

	StemMaker stemMaker;
	stemMaker.initialize(stopFile);
	StemmedList * stems = stemMaker.stem(allWords);

	if (flag == true) {
		stems->write(inputFile + "_stems.txt");
	}

	FreqMaker freqMaker;
	DocList* docList = freqMaker.process(stems);

	if (flag == true) {
		docList->write(inputFile + "_freq.txt");
	}

	docList->sortByFreq();
	docList->reduce(N);

	WordMapMaker wordMapMaker;
	WordMap * wordMap = wordMapMaker.getWordMap(docList);

	if (flag == true) {
		wordMap->write(inputFile + "_map.txt");
	}

	wordMap->sortByFontSize();

	ICloudLayout * cloud = NewLayout();
	cloud->setLayout(wordMap);

	//Used for testing purposes.
	/*MapItem * temp = 0;
	cout << "#\tWord\tFontSize\tWidth" << endl;
	for (int i = 0; i < wordMap->getSize(); i++) {
		temp = wordMap->getElement(i);
		cout << i << "\t" << temp->getWord() << "\t" << temp->getFontSize()->getValue() << "\t" <<
			temp->getRectangle()->getWidth() << endl;
	}*/

	IRenderFactory * factory = NewRenderFactory();
	IRenderMaker * render = factory->NewRenderMaker();

	render->MakeTexFile(wordMap, inputFile + ".tex");

	system("pause");
	return 0;
}
