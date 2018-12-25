#ifndef INTERACTIVEFIX_H
#define INTERACTIVEFIX_H

class IFilter;
class IFactory;
class InteractiveFix
{

private:
	IFilter * myFilter;

public:
	InteractiveFix(IFactory*);
	virtual void DoInteractiveSession();
	~InteractiveFix();
};

#endif