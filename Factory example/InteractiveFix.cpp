#include "InteractiveFix.h"
#include "IFactory.h"
#include "IFilter.h"

#include <iostream>
#include <string>

InteractiveFix::InteractiveFix(IFactory* factoryType)
{
	myFilter = factoryType->NewFilter();
}

void InteractiveFix::DoInteractiveSession() {
	std::string input;
	std::cout << "\n\nEnter your word: ";
	std::cin >> input;

	if (input == "q")
	{
		//do nothing
	}
	else
	{
		myFilter->execute(input);
		std::cout << "Filtered word: " << input << "\n\n";
	}
}
InteractiveFix::~InteractiveFix() {

}