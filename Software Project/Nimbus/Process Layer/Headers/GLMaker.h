/*
	Nicholas S. Ewer
	GLMaker.h that describes a GLMaker
*/

#if !defined GLMAKER_H
#define GLMAKER_H

#include <string>
#include "IRenderMaker.h"

class WordMap;

class GLMaker: public IRenderMaker {
private:
	std::string _fileName;
	WordMap * _map;
public:
	GLMaker();
	virtual void MakeTexFile(WordMap *, std::string);
	virtual ~GLMaker();
};

#endif //GLMAKER_H