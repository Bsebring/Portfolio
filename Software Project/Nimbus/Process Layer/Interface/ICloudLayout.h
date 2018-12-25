/*
 * ICloudLayout.h
 *
 *  Updated on: Oct 30, 2018
 *      Author: Matthew Yaswinski
 */

#if !defined ICLOUDLAYOUT_H
#define ICLOUDLAYOUT_H

class WordMap;

class ICloudLayout {
public:

	virtual void setLayout(WordMap* map) = 0;

	virtual ~ICloudLayout() {};
};

ICloudLayout* NewLayout();

#endif /* ICLOUDLAYOUT_H */
