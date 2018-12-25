//Group 5
//Jared LaBar

#if !defined(IRENDERFACTORY_H)
#define IRENDERFACTORY_H

class IRenderUtil;
class IRenderMaker;

class IRenderFactory {
public:
	virtual IRenderUtil* NewRenderUtil() = 0;
	virtual IRenderMaker* NewRenderMaker() = 0;
	virtual ~IRenderFactory() {}
};

IRenderFactory* NewRenderFactory();

#endif
