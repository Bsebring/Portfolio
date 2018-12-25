//ALexandra Kozak
//Group 5

#if !defined(GLFACTORY_H)
#define GLFACTORY_H

#include "IRenderFactory.h"

class GLFactory : public IRenderFactory 
{
public:
	GLFactory();
	virtual IRenderUtil* NewRenderUtil();
	virtual IRenderMaker* NewRenderMaker();
	virtual ~GLFactory();
};
#endif

