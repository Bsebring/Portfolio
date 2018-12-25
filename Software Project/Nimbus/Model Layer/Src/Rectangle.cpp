/*
Group 5
Created 10/3/18
*/
#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(float _x, float _y, float _width, float _height) {
	setX(_x);
	setY(_y);
	setWidth(_width);
	setHeight(_height);
}

 float Rectangle::getX() {
	return x;
}

void Rectangle::setX(float _x) {
	if (_x < 0) {
		std::cout << "Error: x coordinate must be 0 or greater" << std::endl;
	}
	else {
		x = _x;
	}
}

float Rectangle::getY() {
	return y;
}

void Rectangle::setY(float _y) {
	if (_y < 0) {
		std::cout << "Error: y coordinate must be 0 or greater" << std::endl;
	}
	else {
		y = _y;
	}
}

float Rectangle::getHeight() {
	return height;
}

void Rectangle::setHeight(float _height) {
	if (_height < 0) {
		std::cout << "Error: height must be greater than 0" << std::endl;
	}
	else {
		height = _height;
	}
}

float Rectangle::getWidth() {
	return width;
}

void Rectangle::setWidth(float _width) {
	if (_width < 0) {
		std::cout << "Error: width must be greater than 0" << std::endl;
	}
	else {
		width = _width;
	}
}

Rectangle::~Rectangle() {

}