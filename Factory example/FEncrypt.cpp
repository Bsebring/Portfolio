#include "FEncrypt.h"
#include <string>
#include <iostream>

using namespace std;

FEncrypt::FEncrypt() {

}

void FEncrypt::execute(std::string  &word)
{
	unsigned i = 0;
	while (i< word.size()) {
		if (word[i] == 'a') {
			word.replace(i, 1, 1, '9');
		}
		else if (word[i] == 'e') {
			word.replace(i, 1, 1, '8');
		}
		else if (word[i] == 'i') {
			word.replace(i, 1, 1, '1');
		}
		else if (word[i] == 'o') {
			word.replace(i, 1, 1, '0');
		}
		else if (word[i] == 'u') {
			word.replace(i, 1, 1, '2');
		}

		i++;
	}
}
FEncrypt::~FEncrypt() {

}
