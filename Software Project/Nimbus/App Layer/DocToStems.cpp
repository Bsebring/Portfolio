/*
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* DocToStems.cpp
*/
#include <fstream>
#include <iostream>
#include "WordListParser.h"
#include "StemMaker.h"
#include "StemmedList.h"

int main(int argc, char* argv[]) {
	/* takes input ASCII file and stop file. Puts ASCII
	file into WordListParser which returns a WordList.
	ASCII file and stop list is then inputted into StemMaker,
	which outputs a stemmed list.
	Calling the executable: DocToStems.exe asciiFile stopFile
	*/
	if (argc == 1) {
		std::cout << "NO ARGUMENTS GIVEN" << std::endl;
	} else if (argc == 2) {
		std::cout << "NOT ENOUGH ARGUMENTS" << std::endl;
	} else if (argc == 3) {
		std::string asciiFile = argv[1];
		std::string stopFile = argv[2];
		WordListParser *wlp = new WordListParser();
		WordList *wl = wlp->parse(asciiFile);
		StemMaker *sm = new StemMaker();
		sm->initialize(stopFile);
		StemmedList *sl = sm->stem(wl);
		sl->write("stemmedList.txt");
	} else {
		std::cout << "TOO MANY ARGUMENTS" << std::endl;
	}

	system("pause");
	return 0;
}