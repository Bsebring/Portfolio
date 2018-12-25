/*
* Group 2
* Angela Dutan, Mustafa Ali, Rocky Ho
* CPSC 430 - Nimbus
* SquaresLayout.cpp
*/

#include <iostream>
#include "SquaresLayout.h"
#include "IRenderFactory.h"
#include "IRenderUtil.h"
#include "WordMap.h"
#include "MapItem.h"
#include "FontSize.h"
#include "Rectangle.h"
#include "WordMap.h"

SquaresLayout::SquaresLayout() {
	//constructor
}

void SquaresLayout::setLayout(WordMap *wordMap) {
	/*lays out words, first along the edge of the page
	(a row at the top, a column along the right edge, a
	row at the bottom, and a column along the left edge)
	*/
	wordMap->randomizeElements();
	IRenderFactory* rf = NewRenderFactory();
	IRenderUtil* ru = rf->NewRenderUtil();
	float pageHeight = ru->getPageHeight();
	float pageWidth = ru->getPageWidth();
	std::cout << "Page Height: " << pageHeight << std::endl;
	std::cout << "Page Width: " << pageWidth << std::endl;
	enum EdgeFlag {TOP_EDGE, RIGHT_EDGE, BOTTOM_EDGE, LEFT_EDGE};
	EdgeFlag edge = TOP_EDGE;
	float top = 0.0, right = pageWidth, bottom = pageHeight, left = 0.0; // dynamic page boundaries
	float next = 0.0; // x or y coordinate for next word
	float largest = 0.0; // size of largest word in current row or column
	MapItem *mi;
	FontSize *fs;
	int i;
	for (i = 0; i < wordMap->getSize(); i++) {
		mi = wordMap->getElement(i);
		fs = mi->getFontSize();
		float wordHeight = ru->getWordHeight(fs);
		float wordWidth = ru->getWordWidth(fs, mi->getWord());
		if (wordWidth > (right - left) || wordHeight > (bottom - top))
			break; // word doesn't fit in remaining space
		if (edge == TOP_EDGE) {
			if (next > (right - wordWidth)) {
				edge = RIGHT_EDGE;
				top += largest;
				if (wordHeight > (bottom - top))
					break; // word doesn't fit in remaining space
				largest = wordWidth;
				mi->setRectangle(new Rectangle((right - wordWidth), top, wordWidth, wordHeight));
				next = top + wordHeight;
				continue;
			} else {
				mi->setRectangle(new Rectangle(next, top, wordWidth, wordHeight));
				next += wordWidth;
				if (wordHeight > largest) {
					largest = wordHeight;
				}
			}
		} else if (edge == RIGHT_EDGE) {
			if (next > (bottom - wordHeight)) {
				edge = BOTTOM_EDGE;
				right -= largest;
				if (wordWidth > (right - left))
					break; // word doesn't fit in remaining space
				largest = wordHeight;
				mi->setRectangle(new Rectangle((right-wordWidth), (bottom - wordHeight), wordWidth, wordHeight));
				next = right - wordWidth;
				continue;
			} else {
				mi->setRectangle(new Rectangle((right - wordWidth), next, wordWidth, wordHeight));
				next += wordHeight;
				if (wordWidth > largest) {
					largest = wordWidth;
				}
			}
		} else if (edge == BOTTOM_EDGE) {
			if (next < (left + wordWidth)) {
				edge = LEFT_EDGE;
				bottom -= largest;
				if (wordHeight > (bottom - top))
					break; // word doesn't fit in remaining space
				largest = wordWidth;
				mi->setRectangle(new Rectangle(left, (bottom - wordHeight), wordWidth, wordHeight));
				next = bottom - wordHeight;
				continue;
			} else {
				mi->setRectangle(new Rectangle((next - wordWidth), (bottom - wordHeight), wordWidth, wordHeight));
				next -= wordWidth;
				if (wordHeight > largest) {
					largest = wordHeight;
				}
			}
		} else if (edge == LEFT_EDGE) {
			if (next < top + wordHeight) {
				edge = TOP_EDGE;
				left += largest;
				if (wordWidth > (right - left))
					break; // word doesn't fit in remaining space
				largest = wordHeight;
				mi->setRectangle(new Rectangle(left, top, wordWidth, wordHeight));
				next = left + wordWidth;
				continue;
			} else {
				mi->setRectangle(new Rectangle(left, (next - wordHeight), wordWidth, wordHeight));
				next -= wordHeight;
				if (wordWidth > largest) {
					largest = wordWidth;
				}
			}
		}
	}
	while (i < wordMap->getSize()) {
		mi = wordMap->getElement(i);
		mi->setRectangle(new Rectangle(pageWidth * 2.0, pageHeight * 2.0, 0, 0));
		i++;
	}
}

SquaresLayout::~SquaresLayout() {
	//destructor
}

ICloudLayout* NewLayout(void) {
	// implementation of a global method
	return (new SquaresLayout());
}