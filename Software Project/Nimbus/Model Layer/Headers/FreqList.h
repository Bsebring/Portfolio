#ifndef FREQLIST_H
#define FREQLIST_H

using namespace std;
#include <string>
#include <list>
class WordCount;
class FreqList {
private:
	list<WordCount> freqList;
	static bool compareCount(WordCount & , WordCount &);
public:
	FreqList();
	virtual bool read(ifstream&);// read()
	virtual void write(ofstream&);
	virtual void add(WordCount);
	virtual void remove(string);
	virtual void reduce(float);
	virtual void sort();
	virtual void print();
	virtual WordCount* at(int); //returns specific WordCount object at given index
	virtual int size(); //returns the raw size of private list
	virtual ~FreqList();


};

#endif // !FREQLIST_H
