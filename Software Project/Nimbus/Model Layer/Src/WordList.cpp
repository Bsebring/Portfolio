/*
 * WordList.cpp
 *
 *  Updated on: Nov 6, 2018
 *      Author: Matthew Yaswinski
 */

#include "WordList.h"
#include <fstream>
#include <iostream>
#include <algorithm>

WordList::WordList() {

}

void WordList::read(std::string inputFilePath){
	std::string word;
	std::ifstream ifs(inputFilePath);
	if (ifs.is_open())
	{
		getline(ifs, word);
		while (ifs)
		{
			words.push_back(word);
			getline(ifs, word);
		}
		ifs.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void WordList::write(std::string outputFilePath){
	std::ofstream ofs(outputFilePath);
	if (ofs.is_open() && words.size() != 0)
	{
		for (int i = 0; i < words.size(); i++)
		{
			ofs << words.at(i);
			if (i < words.size() - 1)
			{
				ofs << "\n";
			}
		}
		ofs.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

bool WordList::compareWords(std::string string1, std::string string2) {
	int i = 0;
	while ((i < string1.length()) && (i < string2.length()))
	{
		if (tolower(string1[i]) < tolower(string2[i])) {
			return true;
		}
		else if (tolower(string1[i]) > tolower(string2[i])) {
			return false;
		}
		i++;
	}

	if (string1.length() < string2.length()) {
		return true;
	}
	else {
		return false;
	}
}

int WordList::wordListSize() {
	return words.size();
}

std::string WordList::getElement(int pos) {
	return words.at(pos);
}

void WordList::addElement(std::string word) {
	words.insert(words.begin(), word);
}

void WordList::removeElement(int pos) {
	words.erase(words.begin() + pos);
}

void WordList::printWordList() {
	for (auto o : words) {
		std::cout << o << "\n";
	}
}

void WordList::sortWordList() {
	std::sort(words.begin(), words.end(), compareWords);
}

void WordList::clearWordList() {
	words.clear();
}

WordList::~WordList() {

}
