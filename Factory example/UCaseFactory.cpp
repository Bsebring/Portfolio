#include "UCaseFactory.h"
#include "FUpperCase.h"

UCaseFactory::UCaseFactory()
{

}
IFilter* UCaseFactory::NewFilter()
{
	return new FUpperCase();
}
UCaseFactory::~UCaseFactory(){}
