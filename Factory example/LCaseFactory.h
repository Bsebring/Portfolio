#ifndef LCASEFACTORY_H
#define LCASEFACTORY_H

#include "IFactory.h"

class LCaseFactory:public IFactory
{
public:
	LCaseFactory();
	virtual IFilter* NewFilter() override;
	~LCaseFactory();
};

#endif
