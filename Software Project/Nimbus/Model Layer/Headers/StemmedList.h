// StemmedList.h
//
// Created by: Matthew Steinmann
// Last Edited by: Matthew Steinmann
// Last Edited on: October 30, 2018

#if !defined STEMMEDLIST_H
#define STEMMEDLIST_H

#include <vector>
#include <string>
class FreqList;

class StemmedList
{
private:

	std::vector<FreqList> freqLists;

public:

	StemmedList();

	virtual void addStemmedWord(std::string stem, std::string word);
	
	virtual unsigned size();
	
	virtual FreqList& at(unsigned index);
	
	virtual FreqList& operator[](unsigned index);
	
	virtual void add(FreqList& list);
	
	virtual void insert(FreqList& list, unsigned index);
	
	virtual void remove(unsigned index);
	
	virtual void clear();

	virtual void read(std::string filePath);

	virtual void write(std::string filePath);

	~StemmedList();

};

#endif