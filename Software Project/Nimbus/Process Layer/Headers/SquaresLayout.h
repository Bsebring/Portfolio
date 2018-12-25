/*
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* SquaresLayout.h
*/

#ifndef SQUARESLAYOUT_H
#define SQUARESLAYOUT_H
#include "ICloudLayout.h"
class WordMap;

class SquaresLayout: public ICloudLayout {
public:
	SquaresLayout(); // constructor

	virtual void setLayout(WordMap* wordMap); // 

	virtual ~SquaresLayout(); // destructor
};

#endif
