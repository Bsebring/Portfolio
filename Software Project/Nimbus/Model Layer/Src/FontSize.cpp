/*
	Group 5
	Created 10/3/18
*/
#include "FontSize.h"
#include <iostream>

FontSize::FontSize(int v) {
	if (v < 0 || v > 9) {
		std::cout << "Error: Value must be from 0 to 9" << std::endl;
	}
	else {
		value = v;
	}
}

int FontSize::getSmallest() {
	return smallest;
}

int FontSize::getLargest() {
	return largest;
}

int FontSize::getValue() {
	return value;
}

FontSize::~FontSize() {
	
}