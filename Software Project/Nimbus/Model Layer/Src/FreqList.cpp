#include "FreqList.h"
#include "WordCount.h"
#include <fstream>
#include <functional>
#include <iostream>
FreqList::FreqList() {
	
}
bool FreqList::read(ifstream& fileName) {
	// read()
	string line = "";
	while (getline(fileName, line))
	{
		if (line.compare("#") == 0)
			break; // exit the loop because the end of list was detected
		WordCount wc;
		wc.fromString(line);
		add(wc);
	}
	return true;
}
void FreqList::write(ofstream& fileName) {
	unsigned i = 0;
	list<WordCount>::iterator it = freqList.begin();
	for (list<WordCount>::iterator it = freqList.begin(); it != freqList.end(); it++)
	{
		fileName << it->asString() << "\n";
	}
	fileName << "#\n";

}
void FreqList::add(WordCount wc) {
	freqList.push_back(wc);
}
void FreqList::remove(string name) {
	for (list<WordCount>::iterator it = freqList.begin(); it != freqList.end(); it++)
	{
		if (it->getWord() == name)
		{
			it = freqList.erase(it);
			it--;
		}
	}
}
void FreqList::reduce(float percent) {
	// precondition 0 < percent < 100
	int reduceNumber = 0;
	int keepNumber = 0;
	if (0 <= percent && percent <= 100)
	{
		sort();
		// determine number of elements to reduce
		reduceNumber = freqList.size() * (percent/100);
		if (reduceNumber <= 0)
		{
			reduceNumber = 1;
		}
		list<WordCount>::iterator it;
		for (it = freqList.begin(); it != freqList.end(); it++)
		{
			if (it == freqList.begin())
			{
				keepNumber = freqList.size() - reduceNumber;
				advance(it, keepNumber);
			}
			string s = it->getWord();
			it = freqList.erase(it);
			it--;
		}

	}


}
void FreqList::sort() 
{
	freqList.sort(compareCount);
}
void FreqList::print()
{
	cout << "Current List:\n";
	for (list<WordCount>::iterator it = freqList.begin(); it != freqList.end(); it++)
	{
		cout << it->asString() << "\n";
	}
	cout << "\n";
}
WordCount* FreqList::at(int index)
{
	//returns specific WordCount object at given index
	list<WordCount>::iterator it = freqList.begin();
	advance(it, index);
	/*string s = it->asString();
	WordCount* wc = new WordCount();
	wc->fromString(s);*/
	
	return &(*it);
}
int FreqList::size()
{
	return freqList.size();
}
bool FreqList::compareCount(WordCount &count, WordCount &count2 ) {
	return (count.getCount() > count2.getCount());


}
FreqList::~FreqList() {}