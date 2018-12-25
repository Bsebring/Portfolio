// StemMaker.cpp
//
// Created by: Matthew Steinmann
// Last Edited by: Matthew Steinmann
// Last Edited on: November 7, 2018

#include "StemMaker.h"
#include "StemmedList.h"
#include "WordList.h"

// Flags for stemming rules
#define CONTAINS_VOWEL 1
#define ENDS_CVC 2
#define NOT_ENDS_CVC 4
#define MEASURE_EQUALS 8

StemMaker::StemMaker()
{
	stopList = 0;
}

void StemMaker::initialize(std::string filePath)
{
	stopList = new WordList;
	stopList->read(filePath);
}

StemmedList* StemMaker::stem(WordList* wordList)
{
	StemmedList* stemmedList = new StemmedList;
	bool stopped;
	for (int i = 0; i < wordList->wordListSize(); i++)
	{
		// check for stopped words
		if (stopList != 0)
		{
			stopped = false;
			for (int j = 0; j < stopList->wordListSize(); j++)
			{
				if (wordList->getElement(i).compare(stopList->getElement(j)) == 0)
				{
					stopped = true;
				}
			}
			if (stopped)
				continue;
		}

		// add the word
		stemmedList->addStemmedWord(stemWord(wordList->getElement(i)), wordList->getElement(i));
	}

	return stemmedList;
}

StemMaker::~StemMaker()
{
	if (stopList != 0)
	{
		delete stopList;
	}
}

// Private Stemming Functions

std::string StemMaker::stemWord(std::string word)
{
	// Implements the Porter stemmer algorithm
	// Source: http://snowball.tartarus.org/algorithms/porter/stemmer.html

	std::string stem = word;
	unsigned length;
	
	// Step 1a
	bool matched;

	matched = replaceMatch(stem, "sses", "ss");
	if (!matched)
		matched = replaceMatch(stem, "ies", "i");
	if (!matched)
		matched = replaceMatch(stem, "ss", "ss");
	if (!matched)
		replaceMatch(stem, "s", "");

	// Step 1b
	bool extraStep = false;
	matched = replaceMatch(stem, "eed", "ee", 1);
	if (!matched)
	{
		matched = replaceMatch(stem, "ed", "", 0, CONTAINS_VOWEL);
		extraStep = matched;
	}
	if (!matched)
	{
		matched = replaceMatch(stem, "ing", "", 0, CONTAINS_VOWEL);
		extraStep = matched;
	}

	if (extraStep)
	{
		matched = replaceMatch(stem, "at", "ate");
		if (!matched)
			matched = replaceMatch(stem, "bl", "ble");
		if (!matched)
			matched = replaceMatch(stem, "iz", "ize");
		if (!matched)
		{
			length = stem.length();
			if (endsDD(stem) && stem[length - 1] != 'l' && stem[length - 1] != 's' && stem[length - 1] != 'z')
			{
				stem.resize(length - 1);
				matched = true;
			}
		}
		if (!matched)
			replaceMatch(stem, "", "e", 1, ENDS_CVC | MEASURE_EQUALS);
	}

	// Step 1c
	replaceMatch(stem, "y", "i", 0, CONTAINS_VOWEL);

	// Step 2
	matched = replaceMatch(stem, "ational", "ate", 1);
	if (!matched)
		matched = replaceMatch(stem, "tional", "tion", 1);
	if (!matched)
		matched = replaceMatch(stem, "enci", "ence", 1);
	if (!matched)
		matched = replaceMatch(stem, "anci", "ance", 1);
	if (!matched)
		matched = replaceMatch(stem, "izer", "ize", 1);
	if (!matched)
		matched = replaceMatch(stem, "abli", "able", 1);
	if (!matched)
		matched = replaceMatch(stem, "alli", "al", 1);
	if (!matched)
		matched = replaceMatch(stem, "entli", "ent", 1);
	if (!matched)
		matched = replaceMatch(stem, "eli", "e", 1);
	if (!matched)
		matched = replaceMatch(stem, "ousli", "ous", 1);
	if (!matched)
		matched = replaceMatch(stem, "ization", "ize", 1);
	if (!matched)
		matched = replaceMatch(stem, "ation", "ate", 1);
	if (!matched)
		matched = replaceMatch(stem, "ator", "ate", 1);
	if (!matched)
		matched = replaceMatch(stem, "alism", "al", 1);
	if (!matched)
		matched = replaceMatch(stem, "iveness", "ive", 1);
	if (!matched)
		matched = replaceMatch(stem, "fulness", "ful", 1);
	if (!matched)
		matched = replaceMatch(stem, "ousness", "ous", 1);
	if (!matched)
		matched = replaceMatch(stem, "aliti", "al", 1);
	if (!matched)
		matched = replaceMatch(stem, "iviti", "ive", 1);
	if (!matched)
		replaceMatch(stem, "biliti", "ble", 1);

	// Step 3
	matched = replaceMatch(stem, "icate", "ic", 1);
	if (!matched)
		matched = replaceMatch(stem, "ative", "", 1);
	if (!matched)
		matched = replaceMatch(stem, "alize", "al", 1);
	if (!matched)
		matched = replaceMatch(stem, "iciti", "ic", 1);
	if (!matched)
		matched = replaceMatch(stem, "ical", "ic", 1);
	if (!matched)
		matched = replaceMatch(stem, "ful", "", 1);
	if (!matched)
		replaceMatch(stem, "ness", "", 1);

	// Step 4
	matched = replaceMatch(stem, "al", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "al", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ance", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ence", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "er", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ic", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "able", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ible", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ant", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ement", "", 2);
	if (!matched)
		replaceMatch(stem, "ment", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ent", "", 2);
	if (!matched)
	{
		length = stem.length();
		if (length >= 4 && (stem[length - 4] == 's' || stem[length - 4] == 't'))
			matched = replaceMatch(stem, "ion", "", 2);
	}
	if (!matched)
		matched = replaceMatch(stem, "ou", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ism", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ate", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "iti", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ous", "", 2);
	if (!matched)
		matched = replaceMatch(stem, "ive", "", 2);
	if (!matched)
		replaceMatch(stem, "ize", "", 2);

	// Step 5a
	matched = replaceMatch(stem, "e", "", 2);
	if (!matched)
		replaceMatch(stem, "e", "", 1, MEASURE_EQUALS | NOT_ENDS_CVC);

	// Step 5b
	length = stem.length();
	if (endsDD(stem) && calcMeasure(stem) > 1 && stem[length - 1] == 'l')
	{
		stem.resize(length - 1);
	}
	
	return stem;
}

bool StemMaker::replaceMatch(std::string& word, std::string suffix, std::string replacement, unsigned measure, char flags)
{
	unsigned wordLength = word.length();
	unsigned suffixLength = suffix.length();

	if (wordLength < suffixLength)
		return false;

	unsigned stemLength = wordLength - suffixLength;

	// Check the measure of the stem (if necessary)
	if (measure != 0 && (calcMeasure(word.substr(0, stemLength)) < measure))
	{
		return false;
	}
	else if ((flags & MEASURE_EQUALS) && (calcMeasure(word.substr(0, stemLength)) != measure))
	{
		return false;
	}

	// Check for a vowel in the stem (if necessary)
	if ((flags & CONTAINS_VOWEL) && !containsVowel(word.substr(0, stemLength)))
	{
		return false;
	}

	// Check for a CVC (consonant-vowel-consonant) end to the stem (if necessary)
	if ((flags & ENDS_CVC) && !endsCVC(word.substr(0, stemLength)))
	{
		return false;
	}
	else if ((flags & NOT_ENDS_CVC) && endsCVC(word.substr(0, stemLength)))
	{
		return false;
	}

	// Perform the comparison and (if necessary) replacement
	if (word.substr(stemLength, suffixLength).compare(suffix.c_str()) == 0)
	{
		word = word.substr(0, stemLength) + replacement;
		return true;
	}

	return false;
}

unsigned StemMaker::calcMeasure(std::string word)
{
	unsigned measure = 0;
	unsigned length = word.length();

	bool seekingVowel = true;
	char c;

	for (int i = 0; i < length; i++)
	{
		c = word[i];

		if (seekingVowel && (isVowel(c) || (c == 'y' && i > 0)))
		{
			seekingVowel = false;
		}
		else if (!seekingVowel && !isVowel(c))
		{
			seekingVowel = true;
			measure++;
		}
	}

	return measure;
}

bool StemMaker::endsCVC(std::string word)
{
	unsigned length = word.length();
	if (length < 3)
		return false;
	else if (word[length - 1] == 'w' || word[length - 1] == 'x' || word[length - 1] == 'y')
		return false;
	else if (!isVowel(word[length - 3]) && isVowel(word[length - 2]) && !isVowel(word[length - 1]))
		return true;
	else
		return false;
}

bool StemMaker::endsDD(std::string word)
{
	
	unsigned length = word.length();
	
	if (length < 2 || isVowel(word[length - 1]))
		return false;
	
	return (word[length - 2] == word[length - 1]);
}

bool StemMaker::containsVowel(std::string word)
{
	unsigned size = word.size();
	for (int i = 0; i < size; i++)
	{
		if (isVowel(word[i]))
			return true;
	}

	return false;
}

bool StemMaker::isVowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}