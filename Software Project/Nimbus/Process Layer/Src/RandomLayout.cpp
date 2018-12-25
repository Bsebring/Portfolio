#include "RandomLayout.h"
#include "WordMap.h"
#include "MapItem.h"
#include "Rectangle.h"
#include "LatexUtil.h"
#include "LatexFactory.h"
#include "FontSize.h"
#include <cstdlib>

RandomLayout::RandomLayout()
{

}

void RandomLayout::setLayout(WordMap* map){

	float x, y, height, width;

	IRenderFactory * fact = NewRenderFactory();
	IRenderUtil * u = fact->NewRenderUtil();
	MapItem* mapItem;

	for (int i = 0; i < map->getSize(); i++)
	{
		mapItem = map->getElement(i);										// get index of the wordmap we need
		width = u->getWordWidth(mapItem->getFontSize(), mapItem->getWord()); // get width of the word
		height = u->getWordHeight(mapItem->getFontSize());					 // use font size to get word height
		x = (rand() % (int)u->getPageWidth() + 1);						     // generate random x location
		y = (rand() % (int)u->getPageHeight() + 1);							 // generate random y location

		Rectangle * r = new Rectangle(x, y, height, width); // create new rectangle
		mapItem->setRectangle(r);							// set the newly created rectangle for the mapitem
	}

}

RandomLayout::~RandomLayout()
{

}


ICloudLayout* NewLayout() 
{
	return (new RandomLayout());
}