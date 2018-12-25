/*
	Group 5
	Created 10/3/18
*/
#ifndef MAPITEM_H
#define MAPITEM_H

#include <string>

class Rectangle;
class FontSize;

class MapItem {
private:
	std::string word;
	FontSize * fs;
	Rectangle * r;

public:
	MapItem();
	MapItem(std::string word, FontSize * fs, Rectangle * r);
	virtual std::string asString();
	virtual void fromString(std::string);
	virtual void setWord(std::string);
	virtual std::string getWord();
	virtual FontSize* getFontSize();
	virtual void setFontSize(FontSize *);
	virtual Rectangle* getRectangle();
	virtual void setRectangle(Rectangle *);
	virtual void setRectX(float);
	virtual void setRectY(float);
	virtual void setRectHeight(float);
	virtual void setRectWidth(float);
	virtual ~MapItem();
};

#endif