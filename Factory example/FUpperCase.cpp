#include "FUpperCase.h"
#include <string>
#include <iostream>

FUpperCase::FUpperCase() {

}

void FUpperCase::execute(std::string  &word)
{
	for (unsigned i = 0; i < word.size(); i++) {
		word.replace(i, 1, 1, toupper(word[i]));
	}
}

FUpperCase::~FUpperCase() {

}