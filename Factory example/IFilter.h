#ifndef IFILTER_H
#define IFILTER_H

#include <string>

class IFilter {
public:
	virtual void execute(std::string&) = 0;
	virtual ~IFilter() {};
};

#endif