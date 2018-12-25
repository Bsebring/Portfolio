#ifndef FENCRYPT_H
#define FENCRYPT_H
#include "IFilter.h"

class FEncrypt :public IFilter {
public:
	FEncrypt();
	virtual void execute(std::string &) override;
	~FEncrypt();
};

#endif