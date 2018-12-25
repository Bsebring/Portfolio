#include "FLowerCase.h"
#include <string>
#include <iostream>

using namespace std;

FLowerCase::FLowerCase() {
}

void FLowerCase::execute(std::string  &word)
{
	for (unsigned i = 0; i < word.size(); i++) {
		word.replace(i, 1, 1, tolower(word[i]));
	}
}

FLowerCase::~FLowerCase() {

}