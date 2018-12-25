#include "FileFix.h"
#include "IFactory.h"
#include "IFilter.h"
#include <fstream>
#include <iostream>
FileFix::FileFix(IFactory* factoryType) {
	myFactory = factoryType;
}

void FileFix::ConvertFile(std::string inputFile) {
	IFilter* myFilter = myFactory->NewFilter();
	std::ifstream inStream;
	std::ofstream outStream;
	inStream.open(inputFile, std::ifstream::in);
	if (!inStream.is_open())
	{
		std::cout << "\nError! File: " << inputFile << " Not Found!!";
	}
	else
	{
		outStream.open(inputFile + ".fix", std::ofstream::out);
		std::string line; 
		while (getline(inStream, line))
		{
			myFilter->execute(line);
			outStream << line << "\n";
		}
		inStream.close();
		outStream.close();
	}
}
FileFix::~FileFix() {}