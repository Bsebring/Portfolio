// LinesLayout.cpp
//
// Created by: Matthew Steinmann
// Last Edited by: Kevin Krause
// Last Edited on: November 08, 2018

#include "LinesLayout.h"
#include "IRenderFactory.h"
#include "IRenderUtil.h"
#include "WordMap.h"
#include "MapItem.h"
#include "FontSize.h"
#include "Rectangle.h"

LinesLayout::LinesLayout()
{

}

void LinesLayout::setLayout(WordMap* map)
{
	IRenderFactory* rf = NewRenderFactory();
	IRenderUtil* ru = rf->NewRenderUtil();	
	float pageHeight = ru->getPageHeight();
	float pageWidth = ru->getPageWidth();
	// Calculate max word height
	FontSize *fs = new FontSize(0);
	FontSize *maxfs = new FontSize(fs->getLargest()); // LOL
	float maxWordHeight = ru->getWordHeight(maxfs);
	// The position of the next rectangle's top left corner
	float nextX = 0.0;
	float nextY = 0.0;
	// Randomize the word order
	map->randomizeElements();
	// Iterate through the map
	MapItem *item;
	std::string s;
	float wordWidth;
	float wordHeight;
	int size = map->getSize();
	for (int i = 0; i < size; i++)
	{
		// Grab the data
		item = map->getElement(i);
		fs = item->getFontSize();
		s = item->getWord();
		wordHeight = ru->getWordHeight(fs);
		wordWidth = ru->getWordWidth(fs, s);
		// Make sure the word fits
		if (nextX + wordWidth > pageWidth)
		{
			// Move to next line
			nextX = 0;
			nextY += maxWordHeight;
			if (nextY + maxWordHeight > pageHeight)
			{
				// No more room for words
				while (i < size)
				{
					item = map->getElement(i);
					item->setRectangle(new Rectangle(pageWidth*2.0, pageHeight*2.0, 0, 0));
					i++;
				}
				break;
			}
		}
		// Place the word
		item->setRectangle(new Rectangle(nextX, (nextY/* + maxWordHeight - wordHeight*/), wordWidth, wordHeight));
		// Move the position for the next word
		nextX += wordWidth;
	}
}

LinesLayout::~LinesLayout()
{

}

ICloudLayout* NewLayout()
{
	return new LinesLayout;
}





