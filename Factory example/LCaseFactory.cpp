#include "LCaseFactory.h"
#include "FLowerCase.h"

LCaseFactory::LCaseFactory()
{

}
IFilter* LCaseFactory::NewFilter()
{
	return new FLowerCase();
}
LCaseFactory::~LCaseFactory() {}
