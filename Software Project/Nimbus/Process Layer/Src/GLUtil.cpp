/*
Authors: Aaron Fleury-Charles; Kurt O'Leary
GLUtil.cpp
*/
#define NDEBUG
#include "FontSize.h"
#include "GLUtil.h"
#include "IRenderUtil.h"
#include "glut.h"

int winWidth = 800; int winHeight = 1000;
const float glRenderSizes[10] = {
	0.100,
	0.133,
	0.166,
	0.200,
	0.233,
	0.266,  // char width is about 20
	0.300,
	0.333,
	0.366,
	0.4
};

GLUtil::GLUtil() {

}

float GLUtil::getWordWidth(FontSize* fontsize, std::string text)
{
	float renderSize = glRenderSizes[fontsize->getValue()];
	int pixelsWide = 0;

	for (unsigned int i = 0; i < text.size(); i++) {
		pixelsWide = pixelsWide + glutStrokeWidth(GLUT_STROKE_ROMAN, text.c_str()[i]);
	}

	float width = pixelsWide * renderSize;

	return width + 5.0; // scaled to create space between words
}

float GLUtil::getWordHeight(FontSize* fontsize)
{
	float renderSize = glRenderSizes[fontsize->getValue()];
	float charHeight = renderSize * (winHeight / 8.5);

	return charHeight;
}

float GLUtil::getPageWidth()
{
	return winWidth;
}

float GLUtil::getPageHeight()
{
	return winHeight;
}

GLUtil::~GLUtil() {

}