/*
	Nicholas S. Ewer
	IRenderUtil.h that GLUtil and LatexUtil implement and each layout uses
*/

#if !defined IRENDERUTIL_H
#define IRENDERUTIL_H

#include <string>

class FontSize;

class IRenderUtil {
public:
	virtual float getWordWidth(FontSize*, std::string) = 0;
	virtual float getWordHeight(FontSize*) = 0;
	virtual float getPageWidth() = 0;
	virtual float getPageHeight() = 0;
	virtual ~IRenderUtil() {};
};

#endif //IRENDERUTIL_H