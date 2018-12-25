#ifndef FILEFIX_H
#define FILEFIX_H
#include <string>
class IFactory;

class FileFix {
private:
	IFactory * myFactory;
public:
	FileFix(IFactory*);
	virtual void ConvertFile(std::string);
	~FileFix();
};

#endif