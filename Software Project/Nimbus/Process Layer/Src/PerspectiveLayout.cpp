#include "PerspectiveLayout.h"
#include "IRenderUtil.h"
#include "IRenderFactory.h"
#include "WordMap.h"
#include "MapItem.h"
#include "FontSize.h"
#include "Rectangle.h"
PerspectiveLayout::PerspectiveLayout() {
	//default Constructor

}

void PerspectiveLayout::setLayout(WordMap* map) {
	float x, y, height, width, xOff, xOffR, yOff;
	y = 0;
	xOff = 0;
	xOffR = 0;
	int j = 0;
	float myX = 0;
	IRenderFactory* factory = NewRenderFactory();
	IRenderUtil * u = factory->NewRenderUtil();
	float pageHeight = u->getPageHeight();
	x = u->getPageWidth();
	x = x / 2;

	map->sortByFontSize();

	MapItem * mapItem;
	
	for (int i = map->getSize()-1; i >= 0; i--) {
		mapItem = map->getElement(i);
		//check to see if we have the smallest font size.

		FontSize* f = mapItem->getFontSize();
		if(f->getValue() == 0)
		{
			myX = x + (u->getWordWidth(mapItem->getFontSize(), mapItem->getWord()) / 2);
			xOff = myX;
			xOffR = x + (u->getWordWidth(mapItem->getFontSize(), mapItem->getWord()) / 2);
		}
		else if (f->getValue() %2 == 0)
		{
			
			xOffR += u->getWordWidth(mapItem->getFontSize(), mapItem->getWord());
			myX = xOffR;
		}
		else
		{
			xOff -= (u->getWordWidth(mapItem->getFontSize(), mapItem->getWord()));
			if (xOff > 0)
			{
				myX = xOff;
			}
			else
				//xOffR += u->getWordWidth(mapItem->getFontSize(), mapItem->getWord());
				myX = xOffR;
		}
		j = f->getValue();
		while(j == f->getValue() && mapItem != 0)
		{
			
			width = u->getWordWidth(mapItem->getFontSize(), mapItem->getWord());
			height = u->getWordHeight(mapItem->getFontSize());
			Rectangle * r = new Rectangle(myX, y, height, width);
			mapItem->setRectangle(r);
			y += height;
			if (i > 0)
			{
				if (map->getElement(i - 1)->getFontSize()->getValue() == j)
				{
					mapItem = map->getElement(i - 1);
					f = mapItem->getFontSize();
					i--;
				}
				else
					break;
				
			}
			else
			{
				break;
			}
		}
		y = 0;
		j++;
	}

}

PerspectiveLayout::~PerspectiveLayout() {

}
ICloudLayout* NewLayout() {
	return (new PerspectiveLayout());
}