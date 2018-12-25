// StemmedList.cpp
//
// Created by: Matthew Steinmann
// Last Edited by: Matthew Steinmann
// Last Edited on: November 12, 2018

#include "StemmedList.h"
#include "FreqList.h"
#include "WordCount.h"
#include <fstream>
#include <iostream>

StemmedList::StemmedList()
{

}

unsigned StemmedList::size()
{
	return freqLists.size();
}

void StemmedList::addStemmedWord(std::string stem, std::string word)
{
	unsigned size = freqLists.size();
	WordCount* wc;
	int diff;
	for (vector<FreqList>::iterator it = freqLists.begin(); it != freqLists.end(); it++)
	{
		wc = it->at(0);
		diff = stem.compare(wc->getWord());
		if (diff == 0)
		{
			wc->setCount(wc->getCount() + 1);
			for (unsigned i = 1; i < it->size(); i++)
			{
				wc = it->at(i);
				if (word.compare(wc->getWord()) == 0)
				{
					wc->setCount(wc->getCount() + 1);
					it->sort();
					return;
				}
			}

			WordCount w;
			w.setWord(word);
			w.setCount(1);
			it->add(w);
			return;
		}
		else if (diff < 0)
		{
			// Insert a new FreqList at the current position
			FreqList list;
			
			WordCount stemCount;
			stemCount.setWord(stem);
			stemCount.setCount(1);
			list.add(stemCount);
			
			WordCount wordCount;
			wordCount.setWord(word);
			wordCount.setCount(1);
			list.add(wordCount);

			freqLists.insert(it, list);
			return;
		}
	}

	// Insert new FreqList at the end
	FreqList list;

	WordCount stemCount;
	stemCount.setWord(stem);
	stemCount.setCount(1);
	list.add(stemCount);

	WordCount wordCount;
	wordCount.setWord(word);
	wordCount.setCount(1);
	list.add(wordCount);

	freqLists.insert(freqLists.end(), list);
}
	
FreqList& StemmedList::at(unsigned index)
{
	return freqLists.at(index);
}

FreqList& StemmedList::operator[](unsigned index)
{
	return freqLists[index];
}

void StemmedList::add(FreqList& list)
{
	std::cout << "ERROR: StemmedList::add is deprecated. Use StemmedList::addStemmedWord instead.\n";
}

void StemmedList::insert(FreqList& list, unsigned index)
{
	std::cout << "ERROR: StemmedList::insert is deprecated. Use StemmedList::addStemmedWord instead.\n";
}

void StemmedList::remove(unsigned index)
{
	if(index < freqLists.size())
		freqLists.erase(freqLists.begin() + index);
}

void StemmedList::clear()
{
	freqLists.clear();
}

void StemmedList::read(std::string filePath)
{
	ifstream stream;
	string line;
	unsigned size;
	FreqList* list;
	stream.open(filePath);
	if (!stream.is_open())
	{
		// File open error
		return;
	}

	getline(stream, line);
	if (line[0] == '#')
	{
		line = line.substr(1, line.size() - 1);
		line = line.substr(0, line.find('#'));
		size = stoi(line);
	}
	else
	{
		// Header error
		return;
	}
	freqLists.clear();
	for (unsigned i = 0; i < size; i++)
	{
		list = new FreqList;
		list->read(stream);
		freqLists.push_back(*list);
	}
	stream.close();
}

void StemmedList::write(std::string filePath)
{
	ofstream stream;
	stream.open(filePath);
	if (!stream.is_open())
	{
		return;
	}

	unsigned size = freqLists.size();
	stream << "#" << size << "#\n";
	for (unsigned i = 0; i < size; i++)
	{
		freqLists[i].write(stream);
	}
	stream.close();
}

StemmedList::~StemmedList()
{

}