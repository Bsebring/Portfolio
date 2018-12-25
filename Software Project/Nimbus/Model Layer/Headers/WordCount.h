#ifndef WORDCOUNT_H
#define WORDCOUNT_H

using namespace std;
#include <string>

class WordCount
{
private:
	int count;
	string word;
public:
	WordCount();
	virtual int getCount();
	virtual void setCount(int);
	virtual string getWord();
	virtual void setWord(string);
	virtual string asString();
	virtual void fromString(string);
	virtual ~WordCount();
};

#endif // !WORDCOUNT_H

