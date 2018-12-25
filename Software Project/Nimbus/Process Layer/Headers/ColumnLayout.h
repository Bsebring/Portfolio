/*
 * ColumnLayout.h
 *
 *  Updated on: Oct 30, 2018
 *      Author: Matthew Yaswinski
 */

#if !defined COLUMNLAYOUT_H
#define COLUMNLAYOUT_H

#include "ICloudLayout.h"

class ColumnLayout: public ICloudLayout {

public:
	ColumnLayout();

	virtual void setLayout(WordMap* map);

	virtual ~ColumnLayout();
};

#endif /* COLUMNLAYOUT_H */
