/*
	Group 5
	Created 10/3/18
*/
#include "MapItem.h"
#include "FontSize.h"
#include "Rectangle.h"
#include <iostream>
#include <cstring>
#include <string>

MapItem::MapItem() {

}

MapItem::MapItem(std::string _word, FontSize * _fs, Rectangle * _r) {
	setWord(_word);
	setFontSize(_fs);
	setRectangle(_r);
}

std::string MapItem::asString() {
	return getWord() + " " + std::to_string(fs->getValue()) + " " + std::to_string(r->getX()) + " " 
		+ std::to_string(r->getY()) + " " + std::to_string(r->getWidth()) + " " + std::to_string(r->getHeight());
}

void MapItem::fromString(std::string str) {
	std::string delimiter = " ";
	int loc = str.find(delimiter);
	std::string w = str.substr(0, loc);
	setWord(w);

	str = str.substr(loc + 1, str.length());
	loc = str.find(delimiter);
	std::string fs = str.substr(0, loc);
	FontSize *font = new FontSize(std::stoi(fs, nullptr));
	setFontSize(font);

	str = str.substr(loc + 1, str.length());
	loc = str.find(delimiter);
	std::string x = str.substr(0, loc);

	str = str.substr(loc + 1, str.length());
	loc = str.find(delimiter);
	std::string y = str.substr(0, loc);

	str = str.substr(loc + 1, str.length());
	loc = str.find(delimiter);
	std::string width = str.substr(0, loc);

	str = str.substr(loc + 1, str.length());
	loc = str.find(delimiter);
	std::string height = str.substr(0, loc);

	Rectangle *rect = new Rectangle(std::stof(x, nullptr), std::stof(y, nullptr), std::stof(width, nullptr), std::stof(height, nullptr));
	setRectangle(rect);
}

std::string MapItem::getWord() {
	return word;
}

void MapItem::setWord(std::string w) {
	if (w == "") {
		std::cout << "Error: word cannot be an empty string" << std::endl;
	}
	else {
		word = w;
	}
}

FontSize* MapItem::getFontSize() {
	return new FontSize(fs->getValue());
}

void MapItem::setFontSize(FontSize * newFS) {
	fs = new FontSize(newFS->getValue());
}

Rectangle* MapItem::getRectangle() {
	return new Rectangle(r->getX(), r->getY(), r->getWidth(), r->getHeight());
}

void MapItem::setRectangle(Rectangle * newR) {
	r = new Rectangle(newR->getX(), newR->getY(), newR->getWidth(), newR->getHeight());
}

void MapItem::setRectX(float x) {
	r->setX(x);
}

void MapItem::setRectY(float y) {
	r->setY(y);
}

void MapItem::setRectHeight(float height) {
	r->setHeight(height);
}

void MapItem::setRectWidth(float width) {
	r->setWidth(width);
}

MapItem::~MapItem() {

}