#ifndef ENCRYPTFACTORY_H
#define ENCRYPTFACTORY_H

#include "IFactory.h"

class EncryptFactory :public IFactory
{
public:
	EncryptFactory();
	virtual IFilter* NewFilter() override;
	~EncryptFactory();
};

#endif
