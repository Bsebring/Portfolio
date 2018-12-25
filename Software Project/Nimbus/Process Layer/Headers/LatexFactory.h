#if !defined(LATEXFACTORY_H)
#define LATEXFACTORY_H

#include "IRenderFactory.h"

class LatexFactory: public IRenderFactory {
public:
	LatexFactory();
	virtual IRenderUtil* NewRenderUtil();
	virtual IRenderMaker* NewRenderMaker();
	virtual ~LatexFactory();
};
#endif