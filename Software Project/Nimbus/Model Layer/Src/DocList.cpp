/*
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* DocList.cpp
*/

#include <iostream>
#include <string>

#include <fstream>
#include "WordCount.h"
#include "DocList.h"
#include "FreqList.h"

DocList::DocList() {
	freqList = new FreqList();
	fileName = "";
}

void DocList::setFilename(std::string fn) {
	fileName = fn;
}

std::string DocList::getFilename() {
	return fileName;
}

void DocList::read(std::string fn) {
	setFilename(fn);
	std::ifstream file (fn);
	if (file.is_open()) {
		freqList->read(file);
		file.close();
	} else {
		std::cout << "Unable to open the file!" << std::endl;
	}
}

void DocList::write(std::string fn) {
	std::ofstream file;
	file.open(fn);
	freqList->write(file);
	file.close();
}

void DocList::add(WordCount wc) {
	freqList->add(wc);
}

void DocList::sortByFreq() {
	freqList->sort();
}

void DocList::reduce(float n) {
	freqList->reduce(n);
}

WordCount* DocList::at(int n) {
	WordCount* wc;
	wc = freqList->at(n);
	return wc;
}

int DocList::size() {
	int s = freqList->size();
	return s;
}

DocList::~DocList() {
	delete freqList;
}