// StemMaker.h
//
// Created by: Matthew Steinmann
// Last Edited by: Matthew Steinmann
// Last Edited on: November 7, 2018

#if !defined STEMMAKER_H
#define STEMMAKER_H

#include <string>
class WordList;
class StemmedList;

class StemMaker
{
private:

	WordList* stopList;

	// Stemming Functions

	virtual std::string stemWord(std::string word);

	virtual bool replaceMatch(std::string& word, std::string suffix, std::string replacement, unsigned measure = 0, char flags = 0);

	virtual unsigned calcMeasure(std::string word);

	virtual bool endsCVC(std::string word);

	virtual bool endsDD(std::string word);

	virtual bool containsVowel(std::string word);

	virtual bool isVowel(char c);

public:

	StemMaker();

	virtual void initialize(std::string filePath);

	virtual StemmedList* stem(WordList* wordList);

	~StemMaker();
};

#endif