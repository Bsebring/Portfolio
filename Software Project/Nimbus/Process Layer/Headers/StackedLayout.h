/*
Nicholas S. Ewer
StackedLayout.h that the describes a StackedLayout
*/

#if !defined STACKEDLAYOUT_H
#define STACKEDLAYOUT_H

#include "ICloudLayout.h"

class WordMap;

class StackedLayout: public ICloudLayout {
public:
	StackedLayout();
	virtual void setLayout(WordMap*);
	virtual ~StackedLayout();
};
#endif //STACKEDLAYOUT_H