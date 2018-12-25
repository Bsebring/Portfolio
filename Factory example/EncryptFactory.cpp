#include "EncryptFactory.h"
#include "FEncrypt.h"

EncryptFactory::EncryptFactory()
{

}
IFilter* EncryptFactory::NewFilter()
{
	return new FEncrypt();
}
EncryptFactory::~EncryptFactory() {}
