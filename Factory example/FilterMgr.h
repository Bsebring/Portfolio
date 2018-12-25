#ifndef FILTERMGR_H
#define FILTERMGR_H


class IFactory;

#include <string>

class FilterMgr {
public:
	FilterMgr();
	virtual std::string getChoices();
	~FilterMgr();
};
IFactory* selectFilter(std::string);

#endif
