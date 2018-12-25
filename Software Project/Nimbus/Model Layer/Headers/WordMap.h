/*	Group 5 
	Created: 10/1/2018
*/
#ifndef WORDMAP_H
#define WORDMAP_H

#include<vector>
#include<string>


class MapItem; // Forward declaration

class WordMap {

private:
	std::vector<MapItem> wordMapList;

public:
	WordMap();
	virtual void read(std::string fileName);
	virtual void write(std::string fileName);
	virtual int  getSize();
	virtual void addElement(MapItem *);
	virtual std::string removeElement(int index);
	virtual MapItem* getElement(int index);
	virtual void sortByFontSize();
	virtual void randomizeElements();
	virtual ~WordMap();
};

#endif