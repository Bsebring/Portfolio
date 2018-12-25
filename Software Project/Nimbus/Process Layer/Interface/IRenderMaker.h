 #if !defined IRENDERMAKER_H
#define IRENDERMAKER_H
#include <string>

class WordMap;

class IRenderMaker {

public:

    virtual void MakeTexFile(WordMap*, std::string) = 0;
	virtual ~IRenderMaker() {};
};

#endif 