#ifndef FUPPERCASE_H
#define FUPPERCASE_H
#include "IFilter.h"
class FUpperCase:public IFilter {
	public:
		FUpperCase();
		virtual void execute(std::string&) override;
		~FUpperCase();
};

#endif