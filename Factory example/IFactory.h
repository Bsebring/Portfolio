#ifndef IFACTORY_H
#define IFACTORY_H
class IFilter;
class IFactory {
public:
	virtual IFilter* NewFilter() = 0;
};

#endif