// FreqMaker.cpp
//
// Created by: Danny Chen
// Last Edited by: Danny Chen
// Last Edited on: October 4, 2018

#include "FreqMaker.h"
#include "StemmedList.h"
#include "DocList.h"
#include "Freqlist.h"
#include "WordCount.h"
#include <string>

using namespace std;


FreqMaker::FreqMaker()
{

}

FreqMaker:: ~FreqMaker()
{

}

DocList* FreqMaker::process(StemmedList* list)
{
	DocList* dl = new DocList;
	WordCount wc;

	for (unsigned i = 0; i < list->size(); i++)
	{
		wc.setWord(list->at(i).at(1)->getWord());
		wc.setCount(list->at(i).at(0)->getCount());
		dl->add(wc);
	}

	return dl;
}