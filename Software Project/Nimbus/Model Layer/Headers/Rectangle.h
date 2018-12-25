/*
	Group 5
	Created 10/3/18
*/
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
	float x;
	float y;
	float height;
	float width;

public:
	Rectangle(float, float, float, float);
	virtual float getX();
	virtual void setX(float);
	virtual float getY();
	virtual void setY(float);
	virtual float getHeight();
	virtual void setHeight(float);
	virtual float getWidth();
	virtual void setWidth(float);
	virtual ~Rectangle();
};

#endif