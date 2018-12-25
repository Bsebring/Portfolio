/*
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* DocList.h
*/

#ifndef DOCLIST_H
#define DOCLIST_H
#include <string>

class FreqList;
class WordCount;

class DocList {
private:
	FreqList *freqList;
	std::string fileName;
	virtual void setFilename(std::string fn); // sets the filename
public:
	DocList(); // constructor
	virtual std::string getFilename(); // gets the filename
	virtual void read(std::string fn); // reads the FreqList from a file
	virtual void write(std::string fn); // writes the FreqList to a file
	virtual void add(WordCount);
	virtual void sortByFreq();
	virtual void reduce(float);
	virtual WordCount* at(int);
	virtual int size();
	virtual ~DocList(); // destructor
};
#endif