/*
Kurt O'Leary
GLUtil.h
*/

#if !defined GLUTIL_H
#define GLUTIL_H
#include <string>
#include "IRenderUtil.h"
#include "glut.h"
class FontSize;
class GLUtil : public IRenderUtil {

public:
	GLUtil();
	virtual float getWordWidth(FontSize*, std::string);
	virtual float getWordHeight(FontSize*);
	virtual float getPageWidth();
	virtual float getPageHeight();
	virtual ~GLUtil();
};


#endif //GLTIL_H