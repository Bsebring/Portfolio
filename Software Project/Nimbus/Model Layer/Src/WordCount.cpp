#include "WordCount.h"
#include <cstring>

WordCount::WordCount() {
	//default Constructor
	this->count = 0;
	this->word = "";
}
int WordCount::getCount() {
	return count;
}
void WordCount::setCount(int c) {
		count = c;
}
string WordCount::getWord() {
	return word;
}
void WordCount::setWord(string s) {
	word = s;
}
string WordCount::asString() {
	return getWord() + " " + to_string(getCount());
}
void WordCount::fromString(string s) {
	char* point;
	char*nextPoint;
	char cs[sizeof s];
	strcpy_s(cs, sizeof cs, s.c_str());
	point = strtok_s(cs, " ", &nextPoint);
	setWord(point);
	setCount(stoi(nextPoint));
}
WordCount::~WordCount() {

}