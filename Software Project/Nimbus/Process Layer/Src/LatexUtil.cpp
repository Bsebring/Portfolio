
#include "IRenderUtil.h"
#include "LatexUtil.h"
#include "FontSize.h"
#include <math.h>

int pageHeight = 750;
int pageWidth = 540;

const float latexRenderSizes[10] = {
	6,
	8,
	9,
	10,
	10.95,
	12,  // char width is about 20
	14.4,
	17.28,
	20.74,
	24.88
};

LatexUtil::LatexUtil() {

}

float LatexUtil::getWordWidth(FontSize* myWordFont, std::string myWord) {

	//returns the width of the word in float form based on the font size of the word.
	//Assumes FontSize object is a not square, and therefore uses the amount of chars to calculate the width, hopefully

	float fontvalueW = latexRenderSizes[myWordFont->getValue()];
	float width = 0;

	for (int i = 0; i < myWord.length(); i++) {
		if (myWord[i] == 'i' || myWord[i] == 'j' || myWord[i] == 'l' || myWord[i] == 't')
			width += fontvalueW * (10.0 / 31.0);
		else if (myWord[i] == 'f' || myWord[i] == 'r' || myWord[i] == 's')
			width += fontvalueW * (14.0 / 31.0);
		else if (myWord[i] == 'm' || myWord[i] == 'w')
			width += fontvalueW * (26.0 / 31.0);
		else
			width += fontvalueW * (16.0 / 31.0);
	}

	width += 5.0; //small padding
	
	return width;
}

float LatexUtil::getWordHeight(FontSize* myFont) {
	
	
	float fontvalueH = latexRenderSizes[myFont->getValue()];

	return fontvalueH;
}


float LatexUtil::getPageWidth() {
	//if "\TPHorizModule" is found in the file, set value as the width
	//returns the width of the page in float form.
	// max width for the doc is 60 units which is set earlier in this file

	return pageWidth;
}

float LatexUtil:: getPageHeight() {
	//if"TPVertModule" is found in the file, set value as the height
    //returns the height of the page in float form.
	// max height for the doc is 105 units which is set earlier in this file
    return pageHeight;
}



LatexUtil::~LatexUtil(){}