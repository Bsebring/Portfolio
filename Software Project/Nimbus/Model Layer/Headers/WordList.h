/*
 * WordList.h
 *
 *  Updated on: Nov 6, 2018
 *      Author: Matthew Yaswinski
 */

#if !defined WORDLIST_H
#define WORDLIST_H
#include <vector>
#include <string>

class WordList {
private:
	std::vector<std::string> words;
	static bool compareWords(std::string first, std::string second);
public:
	WordList();
	int wordListSize();
	std::string getElement(int pos);
	virtual void addElement(std::string word);
	virtual void removeElement(int pos);
	virtual void printWordList();
	virtual void sortWordList();
	virtual void clearWordList();
	virtual void read(std::string inputFilePath);
	virtual void write(std::string outputFilePath);
	virtual ~WordList();
};

#endif /* WORDLIST_H */
