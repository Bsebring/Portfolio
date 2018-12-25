#ifndef UCASEFACTORY_H
#define UCASEFACTORY_H

#include "IFactory.h"

class UCaseFactory:public IFactory
{
public:
	UCaseFactory();
	virtual IFilter* NewFilter() override;
	~UCaseFactory();
};

#endif
