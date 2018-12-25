/* 
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* WordMapMaker.h
*/

#ifndef WORDMAPMAKER_H
#define WORDMAPMAKER_H

class WordMap;
class DocList;

class WordMapMaker {
public:
	WordMapMaker(); // constructor

	virtual WordMap* getWordMap(DocList* doclist); // Converts a frequency list (DocList* object) to a WordMap* object

	virtual ~WordMapMaker(); // destructor
};

#endif