/*

FishEyeLayout.cpp
Group 5
10/04/2018

*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "FishEyeLayout.h"
#include "IRenderUtil.h"
#include "IRenderFactory.h"
#include "WordMap.h"
#include "MapItem.h"
#include "FontSize.h"
#include "Rectangle.h"

#define UP true
#define DOWN false

FishEyeLayout::FishEyeLayout()
{

}

struct ColInfo {
	float nextY;  // Next available Ypos in the up direction
	float middleX; // middle X val of column
	bool orient;
};

void setItemFromMid(MapItem* item, float midX, float midY) {
	item->setRectX(midX - item->getRectangle()->getWidth()/2);
	item->setRectY(midY - item->getRectangle()->getHeight()/2);
}

void updateColInfo(ColInfo& col, float itemY, float itemHeight) {
	if (col.orient == UP) {
		col.nextY = col.nextY - itemHeight*.8 - 0.5;
	}
	if (col.orient == DOWN) {
		col.nextY = col.nextY + itemHeight*.8 + 0.5;
	}
}

float dist(float x, float y, float x2, float y2) {
	return sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
}

// check what the center of mass is with the current cloud and one more item
// COM should really be cached to avoid long load times
float centerOfMass(std::vector<MapItem> &v, ColInfo &col, MapItem *m, float centerX, float centerY) {
	float Xnumerator = (m->getFontSize()->getValue() + 1)*col.middleX;
	float Ynumerator = (m->getFontSize()->getValue() + 1)*col.nextY;
	float denominator = (m->getFontSize()->getValue() + 1);


	for (int i = 0; i < v.size(); i++) {
		Xnumerator += (v[i].getFontSize()->getValue() + 1)*v[i].getRectangle()->getX();
		Ynumerator += (v[i].getFontSize()->getValue() + 1)*v[i].getRectangle()->getY();
		denominator += (v[i].getFontSize()->getValue() + 1);
	}

	float x_COM = Xnumerator / denominator;
	float y_COM = Ynumerator / denominator;

	return dist(x_COM, y_COM, centerX, centerY);
}

void FishEyeLayout::setLayout(WordMap* map)
{
	const float WIDTH_PAD = 0.1;
	const float HEIGHT_PAD = 0.1;
	IRenderFactory* irf = NewRenderFactory();
	IRenderUtil* iru = irf->NewRenderUtil();
	float pageHeight = iru->getPageHeight();
	float pageWidth = iru->getPageWidth();
	float pageCenterX = pageWidth / 2;
	float pageCenterY = pageHeight / 2;
	float wordHeight = 0;
	float wordWidth = 0;
	FontSize* fs = new FontSize(0);
	FontSize* maxfs = new FontSize(fs->getLargest());
	FontSize* minfs = new FontSize(fs->getSmallest());
	float maxWordHeight = iru->getWordHeight(maxfs);
	float uHeight = iru->getWordHeight(minfs);		// Smallest height
	float uWidth = iru->getWordWidth(minfs, "l");   // Smallest width - fundamental unit of page
	int gridX = (int)(pageWidth / uWidth); // How many discrete units are on the page?
	int gridY = (int)(pageHeight / uHeight);
	int area = gridX * gridY; // Area of page
	float requiredArea = 0;
	std::string message = "L o a d i n g . . . . . . . . . . . . . . . . . . .";

	MapItem *item;
	Rectangle *rect;
	int letterCount = 0;
	float avgWordLength = 0;
	int numColumns = 0;
	float longestWord = 0;

	// Setting all the word heights and widths in the map based on their font sizes
	for (int i = 0; i < map->getSize(); i++) {
		item = map->getElement(i);
		wordHeight = iru->getWordHeight(item->getFontSize());
		wordWidth = iru->getWordWidth(item->getFontSize(), item->getWord());

		item->setRectHeight(wordHeight + HEIGHT_PAD);
		item->setRectWidth(wordWidth + WIDTH_PAD);

		if (wordWidth > longestWord) {
			longestWord = wordWidth;
		}

		letterCount += item->getWord().length(); // Statistics
		if (i < 10)
			printf("%-12s (%0d) x: %.2f y: %.2f H:%.2f, W:%.2f \n", item->getWord().c_str(), item->getFontSize()->getValue(), item->getRectangle()->getX(), item->getRectangle()->getY(), wordHeight, wordWidth);
		requiredArea += wordWidth * wordHeight; // Statistics
	}

	avgWordLength = letterCount / map->getSize();
	numColumns = (int)(pageWidth / longestWord);

	if (requiredArea > pageWidth*pageHeight) {
		std::cout << "\nWarning: Words require more space than is provided.\n";
	}

	// Debug info for console
	printf("\nPage Dimensions %3.1f x %3.1f = Page Area %5.2f\n", pageWidth, pageHeight, pageWidth*pageHeight);
	printf("Page units (X,Y):(%d,%d) Area: %d \n", gridX, gridY, area);
	printf("Total letters in map: %d required area: %6.2f \n", letterCount, requiredArea);
	if (numColumns % 2 == 0)
		numColumns++;
	printf("Avg word length: %.2f    Suggested columns: %d\n\n", avgWordLength, numColumns);

	std::vector<MapItem> cloud;
	std::vector<ColInfo> candidatesUp(numColumns);
	std::vector<ColInfo> candidatesDown(numColumns);
	int colMidInterval = (pageWidth / numColumns);
	int colPrev = colMidInterval;

	// Initialize candidate vector
	for (int i = 0; i < numColumns; i++) {
		candidatesUp[i].nextY = pageCenterY - maxWordHeight*.25;
		candidatesUp[i].middleX += colPrev;
		colPrev += colMidInterval;
		candidatesUp[i].orient = UP;
	}
	colPrev = colMidInterval;
	for (int i = 0; i < numColumns; i++) {
		candidatesDown[i].nextY = pageCenterY + maxWordHeight*.25;
		candidatesDown[i].middleX += colPrev;
		colPrev += colMidInterval;
		candidatesDown[i].orient = DOWN;
	}

	int currElem = 0;

	MapItem *tempItem = map->getElement(0);
	cloud.push_back(*tempItem);
	// Placing first word in the middle of the middle column

	setItemFromMid(tempItem, candidatesUp[numColumns/2].middleX, pageCenterY - 2);
	updateColInfo(candidatesUp[numColumns / 2], tempItem->getRectangle()->getY(), tempItem->getRectangle()->getHeight());
	updateColInfo(candidatesDown[numColumns / 2], tempItem->getRectangle()->getY(), tempItem->getRectangle()->getHeight());


	/* Algorithm:
	loop through all elements in the word map.
	check all available column spots. Check the COM of each spot, save index of the lowest COM
	*/
	float lowestCOM = INT_MAX;
	float lowestCOMIndex = 0;
	float tempCOM = 0;
	bool bestLoc = DOWN;

	int progress = 0;

	for (int i = 1; i < map->getSize(); i++) {
		tempItem = map->getElement(i);
		rect = tempItem->getRectangle();
		// Search candidate vector to find the best location
		for (int j = 0; j < candidatesUp.size(); j++) {
			tempCOM = centerOfMass(cloud, candidatesUp[j], tempItem, pageCenterX, pageCenterY);
			tempCOM = abs(tempCOM);
			if (tempCOM < lowestCOM) {
				lowestCOM = tempCOM;
				lowestCOMIndex = j;
				bestLoc = UP;
			}
		}
		for (int j = 0; j < candidatesDown.size(); j++) {
			tempCOM = centerOfMass(cloud, candidatesDown[j], tempItem, pageCenterX, pageCenterY);
			tempCOM = abs(tempCOM);
			if (tempCOM < lowestCOM) {
				lowestCOM = tempCOM;
				lowestCOMIndex = j;
				bestLoc = DOWN;
			}
		}
		// lowestCOMIndex is the index of the best place to position the item i
		//set tempItem's rect values
		//printf("\nCOM %f for %s.\n", lowestCOM, tempItem->getWord().c_str());
		if (bestLoc == UP) {
			setItemFromMid(tempItem, candidatesUp[lowestCOMIndex].middleX, candidatesUp[lowestCOMIndex].nextY);
			updateColInfo(candidatesUp[lowestCOMIndex], tempItem->getRectangle()->getY(), tempItem->getRectangle()->getHeight());
		}
		else {
			setItemFromMid(tempItem, candidatesDown[lowestCOMIndex].middleX, candidatesDown[lowestCOMIndex].nextY);
			updateColInfo(candidatesDown[lowestCOMIndex], tempItem->getRectangle()->getY(), tempItem->getRectangle()->getHeight());
		}
		cloud.push_back(*tempItem);
		lowestCOM = INT_MAX;
		lowestCOMIndex = numColumns/2;
		printf("\r");
		progress = (int)(i * message.size() / map->getSize());
		//for (int c = 0; c < (int)(i*60 / map->getSize()); c++) {
		printf("%s", message.substr(0, progress).c_str());
		//}
		fflush(stdout);
	}
	printf("\nLayout Done computing!\n");
}

ICloudLayout* NewLayout()
{
	return (new FishEyeLayout());
}