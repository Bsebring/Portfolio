// FreqMaker.h
//
// Created by: Danny Chen
// Last Edited by: Danny Chen
// Last Edited on: October 4, 2018

#if !defined FREQMAKER_H
#define FREQMAKER_H

class DocList;

class StemmedList;

class FreqMaker
{
public:

	FreqMaker();

	virtual DocList* process(StemmedList* stem);

	virtual ~FreqMaker();

};

#endif