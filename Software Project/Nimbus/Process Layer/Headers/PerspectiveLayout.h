#ifndef PERSPECTIVELAYOUT_H
#define PERSPECTIVELAYOUT_H

#include "ICloudLayout.h"
#include "WordMap.h"
using namespace std;

class WordMap;

class PerspectiveLayout : public ICloudLayout {


private:
	WordMap * wordMap;

public:
	PerspectiveLayout();
	virtual ~PerspectiveLayout();
	virtual void setLayout(WordMap*);
};

#endif 
