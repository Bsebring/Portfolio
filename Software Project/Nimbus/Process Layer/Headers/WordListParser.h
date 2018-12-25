/*
 * WordListParser.h
 *
 *  Updated on: Oct 30, 2018
 *      Author: Matthew Yaswinski
 */

#if !defined WORDLISTPARSER_H_
#define WORDLISTPARSER_H_
#include <string>

class WordList;

class WordListParser {
public:
	WordListParser();

	virtual WordList* parse(std::string inputFilePath);
	virtual ~WordListParser();
};

#endif /* WORDLISTPARSER_H */
