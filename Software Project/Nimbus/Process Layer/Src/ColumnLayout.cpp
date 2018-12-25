/*
 * ColumnLayout.cpp
 *
 *  Updated on: Nov 19, 2018
 */

#include "ColumnLayout.h"
#include "IRenderFactory.h"
#include "IRenderUtil.h"
#include "WordMap.h"
#include "MapItem.h"
#include "FontSize.h"
#include "Rectangle.h"

ColumnLayout::ColumnLayout() {

}

void ColumnLayout::setLayout(WordMap* map){

	IRenderFactory* rf = NewRenderFactory();
	IRenderUtil* ru = rf->NewRenderUtil();
	float pgHeight = ru->getPageHeight();
	float pgWidth = ru->getPageWidth();
	float firColumnEnd = (pgWidth / 2) - 2;
	float secColumnStart = (pgWidth / 2) + 2;
	float newX = 0.0;
	float newY = 0.0;
	float wordWidth, wordHeight;
	int i;
	std::string word;
	
	FontSize* fs = new FontSize(0);
	FontSize* lgstfs = new FontSize(fs->getLargest());
	float maxWordHeight = ru->getWordHeight(lgstfs);
	
	map->randomizeElements();
	
	MapItem *item;
	
	int size = map->getSize();
	
	for (i = 0; i < size; i++)
	{
		// Grab the data
		item = map->getElement(i);
		fs = item->getFontSize();
		word = item->getWord();
		wordHeight = ru->getWordHeight(fs);
		wordWidth = ru->getWordWidth(fs, word);
		// Make sure the word fits
		if (newX + wordWidth > firColumnEnd)
		{
			// Move to next line
			newX = 0;
			newY += maxWordHeight;
			if (newY + maxWordHeight > pgHeight)
			{
				newX = secColumnStart;
				newY = 0;
				break;
			}
		}
		
		item->setRectangle(new Rectangle(newX, newY, wordWidth, wordHeight));
		
		newX += wordWidth;
	}

	
	for (i = i-1; i < size; i++)
	{
		
		item = map->getElement(i);
		fs = item->getFontSize();
		word = item->getWord();
		wordHeight = ru->getWordHeight(fs);
		wordWidth = ru->getWordWidth(fs, word);
		
		if (newX + wordWidth > pgWidth)
		{
			// Move to next line
			newX = secColumnStart;
			newY += maxWordHeight;
			if (newY + maxWordHeight > pgHeight)
			{
				while (i < size)
				{
					item = map->getElement(i);
					item->setRectangle(new Rectangle(pgWidth*2.0, pgHeight*2.0, 0, 0));
					i++;
				}
				break;
			}
		}
		
		item->setRectangle(new Rectangle(newX, newY, wordWidth, wordHeight));
		
		newX += wordWidth;
	}
}

ColumnLayout::~ColumnLayout() {

}

ICloudLayout* NewLayout() {
	return (new ColumnLayout());
}