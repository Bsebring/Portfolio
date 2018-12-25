#if !defined FishEyeLayout_h
#define FishEyeLayout_h

#include "ICLoudLayout.h"
#include "WordMap.h"

class WordMap;

class FishEyeLayout : public ICloudLayout
{
private:
	WordMap * wordMap;
public:
	FishEyeLayout();
	virtual ~FishEyeLayout() {};

	virtual void setLayout(WordMap*);
};
#endif

