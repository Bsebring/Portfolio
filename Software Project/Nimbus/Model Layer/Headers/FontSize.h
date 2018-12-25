/*
	Group 5
	Created 10/3/18
*/
#ifndef FONTSIZE_H
#define FONTSIZE_H

class FontSize {
private:
	int value;
	const static int smallest = 0;
	const static int largest = 9;

public:
	FontSize(int);
	virtual int getSmallest();
	virtual int getLargest();
	virtual int getValue();
	virtual ~FontSize();
};

#endif
