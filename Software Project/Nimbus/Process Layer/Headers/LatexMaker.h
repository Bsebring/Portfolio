#include "IRenderMaker.h"

#if !defined LATEXMAKER_H
#define LATEXMAKER_H


class WordMap;

class LatexMaker : public IRenderMaker{
	
	
	private:
		std::string _fileName;
		WordMap * _map;

	public:
		LatexMaker();
		virtual void MakeTexFile(WordMap*, std::string);
		virtual ~LatexMaker();


};
#endif
