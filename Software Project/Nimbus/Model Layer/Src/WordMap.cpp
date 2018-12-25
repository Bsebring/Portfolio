/*	Group 5
	Created: 10/1/2018

*/
#include "WordMap.h"
#include "MapItem.h"
#include "FontSize.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <random>


WordMap::WordMap() {
	// Should we remove this constructor and have something like
	/*
	WordMap(string fileName) {
		read(fileName);
	}
	*/
	// instead?
}

int WordMap::getSize() {
	return (int)wordMapList.size(); // cast to avoid compiler warning
}

void WordMap::read(std::string fileName) {
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open()){
		std::cout << "WordMap read() error: File not opened.";
		return;
	}

	std::string line;
	MapItem * mapPtr;


	while(std::getline(file, line)){
		mapPtr = new MapItem();
		mapPtr->fromString(line);
		addElement(mapPtr);
		//delete(mapPtr); // Memory management: what happens to the old mapPtr?
	}
}

void WordMap::write(std::string fileName) {
	std::ofstream wordFile;
	wordFile.open(fileName);

	if (!wordFile.is_open()){
		std::cout << "WordMap write() error: File not opened.";
		return;
	}

	for (auto it = wordMapList.begin(); it != wordMapList.end(); ++it){
	    wordFile << it->asString() << "\n";
	}
}

// Comparator to be used by sortByFontSize()
bool comp(MapItem &a, MapItem &b) {
	return (a.getFontSize())->getValue() > (b.getFontSize())->getValue();
}

void WordMap::sortByFontSize() {
	std::sort(wordMapList.begin(),wordMapList.end(), comp);
}

// Shuffle code inspired by: https://stackoverflow.com/a/6926473
void WordMap::randomizeElements() {
	std::random_device randDev;
	auto randomGenerator = std::default_random_engine{ randDev() };
	std::shuffle(std::begin(wordMapList), std::end(wordMapList), randomGenerator);
}

void WordMap::addElement(MapItem* item) {
	if (item == NULL) {
		std::cout << "WordMap Error: Requested MapItem is null.";
		return;
	}
	
	wordMapList.push_back(*item);
}

std::string WordMap::removeElement(int index) {
	if (index < 0 || index >= wordMapList.size()){
		std::cout << "\nWordMap removeElement Error: Index (" << index << ") is out of bounds.\n";
		return "";
	}

	auto it = wordMapList.begin();
	std::advance(it, index);

	MapItem* oldElem = new MapItem(it->getWord(), it->getFontSize(), it->getRectangle());

	wordMapList.erase(it);

	return oldElem->asString();
}

MapItem* WordMap::getElement(int index) {
	if (index < 0 || index >= wordMapList.size()) {
		std::cout << "\nWordMap getElement Error: Index (" << index << ") is out of bounds.\n";
		return NULL;
	}
	
	// A copy is no longer used. Rejoice.
	return &wordMapList.at(index);
}

// Should the destructor do anything here?
WordMap::~WordMap() {

}