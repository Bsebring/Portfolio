/*
 * WordListParser.cpp
 *
 *  Updated on: Nov 7, 2018
 *      Author: John Hanley
 */

#include "WordListParser.h"
#include "WordList.h"
#include <fstream>
#include <iostream>


WordListParser::WordListParser() {

}

WordList* WordListParser::parse(std::string inputFilePath) {
	WordList* access = new WordList();
	std::vector<std::string> token;
	int freq, counter = 0;
	bool digit = false;
	std::string word, holder, tokenized, filtered;
	char c;
	std::ifstream ifs(inputFilePath);

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			getline(ifs, tokenized);
			std::vector<char> characters(tokenized.begin(), tokenized.end());
			for (int i = 0; i < characters.size(); i++)
			{
				c = characters.at(i);
				if (iswspace(c))
				{
					token.push_back(word);
					word = "";
				}
				else
				{
					if (i == characters.size() - 1)
					{
						word += tolower(c);
						token.push_back(word);
						word = "";
					}
					else
					{
						word += tolower(c);
					}

				}

			}

			if (token.size() == 2)
			{
				std::string tmp = token.at(1);
				for (int p = 0; p < tmp.length(); p++)
				{
					c = token.at(1)[p];
					if (isdigit(c))
					{
						digit = true;
					}
					else
					{
						digit = false;
						break;
					}

				}
				
			}

			if (digit == true)
			{
				freq = stoi(token.at(1));
				holder = token.at(0);
				for (int k = 0; k < holder.length(); k++)
				{
					c = holder[k];
					if (isalpha(c))
					{
						filtered += tolower(c);
					}
					else if (ispunct(c) || iswspace(c) || isdigit(c))
					{
						continue;
					}
				}

				if (!filtered.empty())
				{
					for (int q = 0; q < freq; q++)
					{
						access->addElement(filtered);
					}
				}

				token.clear();
				filtered = "";
				digit = false;
			}
			else
			{

				for (int d = 0; d < token.size(); d++)
				{
					holder = token.at(d);
					for (int i = 0; i < holder.length(); i++)
					{
						c = holder[i];

						if (isalpha(c))
						{
							filtered += tolower(c);
						}
						else if (ispunct(c) || iswspace(c) || isdigit(c))
						{
							continue;
						}
					}

					if (!filtered.empty())
					{
						access->addElement(filtered);
						filtered = "";
					}

				}
				token.clear();
			}

		}
		ifs.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
	return access;
}

WordListParser::~WordListParser() {

}