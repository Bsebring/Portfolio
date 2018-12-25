/*
	Nicholas S. Ewer
	Implementation of StackedLayout.h
*/

#include "WordMap.h"
#include "Rectangle.h"
#include "MapItem.h"
#include "StackedLayout.h"
#include "FontSize.h"
#include "IRenderUtil.h"
#include "IRenderFactory.h"
#include <algorithm>
#include <vector>
#include <cstdlib>

std::vector<MapItem> v;

bool test(MapItem &x, MapItem &y) {
	if (x.getFontSize()->getValue() == y.getFontSize()->getValue()) {
		if (x.getRectangle()->getWidth() > y.getRectangle()->getWidth()) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void sortByWidth() {
	std::sort(v.begin(), v.end(), test);
}

StackedLayout::StackedLayout() {

}

void StackedLayout::setLayout(WordMap * map) {
	float x, y, height, width;
	y = 0;

	IRenderFactory* factory = NewRenderFactory();
	IRenderUtil * u = factory->NewRenderUtil();

	x = u->getPageWidth();
	x = x / 2;

	MapItem * mapItem;
	
	for (int i = 0; i < map->getSize(); i++) {
		mapItem = map->getElement(i);
		FontSize * fs = new FontSize((i%3) + 7);
		mapItem->setFontSize(fs);
	}

	map->sortByFontSize();

	for (int i = 0; i < map->getSize(); i++) {
		mapItem = map->getElement(i);
		//int myX = x - (mapItem->getWord().length() / 2);
		width = u->getWordWidth(mapItem->getFontSize(), mapItem->getWord());
		height = u->getWordHeight(mapItem->getFontSize());
		int myX = x - (width / 2);
		Rectangle * r = new Rectangle(myX, y, width, height);
		mapItem->setRectangle(r);
		y += height;
		v.push_back(*mapItem);
	}

	y = 0;
	sortByWidth();
	int mapSize = map->getSize();
	for (int i = 0; i < mapSize; i++) {
		map->removeElement(0);
		map->addElement(&v.at(i));
	}

	for (int i = 0; i < map->getSize(); i++) {
		mapItem = map->getElement(i);
		//int myX = x - (mapItem->getWord().length() / 2);
		width = u->getWordWidth(mapItem->getFontSize(), mapItem->getWord());
		height = u->getWordHeight(mapItem->getFontSize());
		int myX = x - (width / 2);
		Rectangle * r = new Rectangle(myX, y, width, height);
		mapItem->setRectangle(r);
		y += height;
	}

}



StackedLayout::~StackedLayout() {

}

ICloudLayout* NewLayout() {
	return (new StackedLayout());
}