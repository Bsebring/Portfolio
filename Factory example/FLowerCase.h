#ifndef FLOWERTCASE_H
#define FLOWERCASE_H
#include "IFilter.h"

class FLowerCase :public IFilter {
public:
	FLowerCase();
	virtual void execute(std::string &) override;
	~FLowerCase();
};

#endif