#include "LatexFactory.h"
#include "LatexMaker.h"
#include "LatexUtil.h"

LatexFactory::LatexFactory()
{

}
IRenderMaker* LatexFactory::NewRenderMaker()
{
	return new LatexMaker();
}
IRenderUtil* LatexFactory::NewRenderUtil()
{
	return new LatexUtil();
}
LatexFactory::~LatexFactory()
{

}
IRenderFactory* NewRenderFactory()
{
	return new LatexFactory();
};
