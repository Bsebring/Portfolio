//ALexandra Kozak
//Group 5

#include "GLFactory.h"
#include "GLMaker.h"
#include "GLUtil.h"

GLFactory::GLFactory()
{

}
IRenderMaker* GLFactory::NewRenderMaker()
{
	return new GLMaker();
}
IRenderUtil* GLFactory::NewRenderUtil()
{
	 return new GLUtil();
}
GLFactory::~GLFactory()
{

}
IRenderFactory* NewRenderFactory()
{
	return new GLFactory();
};
//IRenderFactory* GLFactory::NewRenderFactory()
//{

//};