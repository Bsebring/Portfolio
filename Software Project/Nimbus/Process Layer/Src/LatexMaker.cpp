#include "IRenderMaker.h"
#include "LatexMaker.h"
#include "MapItem.h"
#include "WordMap.h"
#include "Rectangle.h"
#include "FontSize.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>



LatexMaker::LatexMaker() {}

void LatexMaker::MakeTexFile(WordMap* map, std::string fileName)
{
	std::string newName = (fileName + ".tex"); // create file tex file name that we are going to write to
	std::ofstream file;							// create output file stream
	file.open(newName);						// open filename that we have just created for writing.

	file << "\\documentclass[11pt]{letter} % letter can only use 10pt, 11pt, or 12pt\n"; // use two backslashes to allowing printing of single backslash to the file
	file << "\\usepackage{times}\n";
	file << "\\usepackage[absolute]{textpos} % positions are from upper-left corner\n";
	file << "\\pagestyle{empty}\n";
	file << "\\setlength{\\TPHorizModule}{.35136mm}\n";
	file << "\\setlength{\\TPVertModule}{.35136mm}\n";
	file << "\\textblockorigin{10mm}{10mm} % upper left corner\n";
	file << "\\begin{document}\n";

	/*for (list<MapItem>::iterator item = map->wordMapList.begin(); item != map->wordMapList.end(); item++)
	{
	file << "\begin{ textblock }{0}(" + "---x-coordinate---" + "," + "---y-coordinate---" + " ) \footnotesize{ learning } \end{ textblock }";
	}*/ // cant figure out how to iterate using lists, workaround created


	for (int i = 0; i < map->getSize(); i++) // while we can still get a map item from the list, add the item and the location to the latex doc
	{
		float x = map->getElement(i)->getRectangle()->getX(); // get x location
		float y = map->getElement(i)->getRectangle()->getY(); // get y location
		std::string s = map->getElement(i)->getWord();			// get string of item
		int size = map->getElement(i)->getFontSize()->getValue();
		std::string font;

		switch (size)
		{
		case 0: font = "tiny";
			break;
		case 1:	font = "scriptsize";
			break;
		case 2: font = "footnotesize";
			break;
		case 3: font = "small";
			break;
		case 4: font = "normalsize";
			break;
		case 5: font = "large";
			break;
		case 6:	font = "Large";
			break;
		case 7:	font = "LARGE";
			break;
		case 8:	font = "huge";
			break;
		case 9:	font = "Huge";
			break;
		}

		file << "\\begin{textblock}{0}(" << x << "," << y << ") " << "\\" << font << "{" << s << "} \\end{textblock}" << "\n";

	}

	file << "\\end{document}";
}

LatexMaker::~LatexMaker() {}