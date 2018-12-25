

#if  !defined RANDOMLAYOUT_H
#define RANDOMLAYOUT_H
#include "ICloudLayout.h"
class WordMap;

class RandomLayout: public ICloudLayout{

private:
	WordMap * _map;

public:

	RandomLayout();
	virtual void setLayout(WordMap*);
	virtual ~RandomLayout();

};

#endif