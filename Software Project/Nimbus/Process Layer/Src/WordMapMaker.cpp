/*
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* WordMapMaker.cpp
*/

#include <iostream>
#include "WordMapMaker.h"
#include "WordCount.h"
#include "WordMap.h"
#include "DocList.h"
#include "FontSize.h"
#include "MapItem.h"
#include "Rectangle.h"

WordMapMaker::WordMapMaker() {
}

WordMap* WordMapMaker::getWordMap(DocList* docList) {
	WordMap *wordMap = new WordMap();
	int size = docList->size()-1;
	WordCount* s = docList->at(size);
	WordCount* b = docList->at(0);
	float big = b->getCount();
	float small = s->getCount();
	float range = ((big - small) / 10);

	for (int i = 0; i <= size; i++) {
		MapItem *mi = new MapItem();
		WordCount* wc = docList->at(i);
		string word = wc->getWord();
		int wordfreq = wc->getCount();
		mi->setWord(word);
		int fontsize = 0;
		
		if (wordfreq >= small && wordfreq < (small + range)) {
			fontsize = fontsize + 0;
		}
		else if (wordfreq >= (small + range) && wordfreq < (small + (2 * range))) {
			fontsize = fontsize + 1;
		}
		else if (wordfreq >= (small + (2 * range)) && wordfreq < (small + (3 * range))) {
			fontsize = fontsize + 2;
		}
		else if (wordfreq >= (small + (3 * range)) && wordfreq < (small + (4 * range))) {
			fontsize = fontsize + 3;
		}
		else if (wordfreq >= (small + (4 * range)) && wordfreq < (small + (5 * range))) {
			fontsize = fontsize + 4;
		}
		else if (wordfreq >= (small + (5 * range)) && wordfreq < (small + (6 * range))) {
			fontsize = fontsize + 5;
		}
		else if (wordfreq >= (small + (6 * range)) && wordfreq < (small + (7 * range))) {
			fontsize = fontsize + 6;
		}
		else if (wordfreq >= (small + (7 * range)) && wordfreq < (small + (8 * range))) {
			fontsize = fontsize + 7;
		}
		else if (wordfreq >= (small + (8 * range)) && wordfreq < (small + (9 * range))) {
			fontsize = fontsize + 8;
		}
		else if (wordfreq >= (small + (9 * range)) && wordfreq <= (small + (10 * range))) {
			fontsize = fontsize + 9;
		}
		FontSize *f = new FontSize(fontsize);
		mi->setFontSize(f);
		Rectangle *r = new Rectangle(0.0,0.0,0.0,0.0);
		mi->setRectangle(r);
		wordMap->addElement(mi);
	}
	return wordMap;
}

WordMapMaker::~WordMapMaker() {
}