#if !defined LATEXUTIL_H
#define LATEXUTIL_H

#include "IRenderUtil.h"

class LatexUtil : public IRenderUtil {
public:
    LatexUtil();
    virtual float getWordWidth(FontSize*, std::string);
    virtual float getWordHeight(FontSize*);
    virtual float getPageWidth();
    virtual float getPageHeight();
    virtual ~LatexUtil();

};
#endif