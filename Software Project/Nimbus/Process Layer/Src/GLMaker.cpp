/*
	Nicholas S. Ewer
	Implementation of GLMaker.h
*/

#include "IRenderMaker.h"
#include "WordMap.h"
#include "GLMaker.h"
#include "MapItem.h"
#include "Rectangle.h"
#include "glut.h"
#include "FontSize.h"
#include "GLUtil.h"



int WindowWidth = 800;
int WindowHeight = 1000;
WordMap * globalMap = 0;

const double glRenderSizes[10] = {
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

/*double getWidth(std::string text, int fontsize, int windowWidth, int windowHeight)
{
	// Assumes each char is the same width (width of 'm')
	if (fontsize < 0 || fontsize > 9)
		fontsize = 5;
	double renderSize = glRenderSizes[fontsize];
	int pixelsWide = 0;
	for (unsigned int i = 0; i < text.size(); i++) {
		pixelsWide = pixelsWide + glutStrokeWidth(GLUT_STROKE_ROMAN, text.c_str()[i]);
	}
	double width = pixelsWide * renderSize;
	return (width);
}


double getHeight(int fontsize, int windowWidth, int windowHeight)
{
	// Assumes each char is the same width (width of 'm')
	if (fontsize < 0 || fontsize > 9)
		fontsize = 5;
	double renderSize = glRenderSizes[fontsize];
	double charHeight = renderSize * (WindowHeight / 8.5);
	return (charHeight);
}*/

void PrintText(double x, double y, std::string text, unsigned int size)
{
	// Display text at position (x,y) using fontsize size
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, WindowWidth, 0.0f, WindowHeight, -1.0f, 1.0f); // (x,y) position is relative to this

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)0);
	glScalef((GLfloat)glRenderSizes[size], (GLfloat)glRenderSizes[size], (GLfloat)1);

	for (unsigned int i = 0; i < text.size(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text.c_str()[i]);
	}

	glScalef(1, 1, 1);

	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.5, 0.7, 1.0); // set the color for drawing

	int start_x = WindowWidth / 2;
	int delta_x = WindowWidth / 40;

	int x = start_x;
	int y = WindowHeight / 20;
	//globalMap->sortByFontSize();
	for (int i = 0; i < globalMap->getSize(); i++)
	{
		//PrintText(x, y, _map->getElement(i)->getWord(), i);
		//double word1_width = getWordWidth(i, globalMap->getElement(i)->getWord());
		//double word1_width = getWidth(globalMap->getElement(i)->getWord(), globalMap->getElement(i)->getFontSize()->getValue(), WindowWidth, WindowHeight);
		PrintText(globalMap->getElement(i)->getRectangle()->getX(), globalMap->getElement(i)->getRectangle()->getY()
			, globalMap->getElement(i)->getWord(), globalMap->getElement(i)->getFontSize()->getValue());
		//PrintText(x + word1_width, y, globalMap->getElement(i)->getWord(), globalMap->getElement(i)->getFontSize()->getValue());
		//x -= delta_x;  // move to the left
		//y += getWordHeight(i);
		//y += getHeight(globalMap->getElement(i)->getFontSize()->getValue(), WindowWidth, WindowHeight);  // move up
	}
	glutSwapBuffers();
}
/*
void Test(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.5, 0.7, 1.0); // set the color for drawing

	int start_x = WindowWidth / 2;
	int delta_x = WindowWidth / 40;

	int x = start_x;
	int y = WindowHeight / 20;
	globalMap->sortByFontSize();
	for (int i = 0; i < globalMap->getSize(); i++)
	{
		//PrintText(x, y, _map->getElement(i)->getWord(), i);
		//double word1_width = getWordWidth(i, globalMap->getElement(i)->getWord());
		double word1_width = getWidth(globalMap->getElement(i)->getWord(), globalMap->getElement(i)->getFontSize()->getValue(), WindowWidth, WindowHeight);

		PrintText(x + word1_width, y, globalMap->getElement(i)->getWord(), globalMap->getElement(i)->getFontSize()->getValue());
		x -= delta_x;  // move to the left
		//y += getWordHeight(i);
		y += getHeight(globalMap->getElement(i)->getFontSize()->getValue(), WindowWidth, WindowHeight);  // move up
	}
	glutSwapBuffers();
}*/

GLMaker::GLMaker() {

}

void GLMaker::MakeTexFile(WordMap * map, std::string filePath) 
{
	char * c = 0;
	globalMap = map;
	//glutInit(0, &c);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//glutInitWindowSize(500, 300);  // width, height
	glutInitWindowSize(616, 780);  // width, height of display window-- output is scaled to fit in here, so keep the aspect ratio
	glutCreateWindow("Layout");
	//glutDisplayFunc(Test);
	glutDisplayFunc(Display);  // maker does this
	glutMainLoop();  // maker does this
}

GLMaker::~GLMaker() {

}