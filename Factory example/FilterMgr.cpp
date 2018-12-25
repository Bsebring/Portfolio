#include "FilterMgr.h"
#include "EncryptFactory.h"
#include "LCaseFactory.h"
#include "UCaseFactory.h"
#include "IFactory.h"
#include <iostream>

using namespace std;
FilterMgr::FilterMgr() {

}
string FilterMgr::getChoices() {
	string s = "\n\tuppercase\n\tlowercase\n\tencrypt";
	return s;
}
IFactory* selectFilter(string choice) {
	IFactory* choicePointer;
	if (choice == "encrypt") 
	{
		choicePointer = new EncryptFactory();
		
	}
	else if (choice == "uppercase")
	{
		choicePointer = new UCaseFactory();
		
	}
	else if (choice == "lowercase")
	{
		choicePointer = new LCaseFactory();
	}
	else
	{
		choicePointer = 0;
	}
	return choicePointer;
}
FilterMgr::~FilterMgr(){}

