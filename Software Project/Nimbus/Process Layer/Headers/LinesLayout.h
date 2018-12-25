// LinesLayout.h
//
// Created by: Matthew Steinmann
// Last Edited by: Matthew Steinmann
// Last Edited on: October 4, 2018

#if !defined LINESLAYOUT_H
#define LINESLAYOUT_H

#include "ICloudLayout.h"

class WordMap;

class LinesLayout : public ICloudLayout
{
public:
	
	LinesLayout();

	virtual void setLayout(WordMap* map);

	~LinesLayout();
};

#endif