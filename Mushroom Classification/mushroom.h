/* ***       Author:  David Jordan
     *  Last Update:  February 27, 2014
     *        Class:  CSI-281-01
     *     Filename:  classifier.h
     *
     *  Description:
     *      This is the header for the mushroom class. A mushroom
	 *      has a set of attributes stored as a list of integers.
	 *      
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "ID3DataEntry.h"
#include <string>
using namespace std;

const int NUM_ATTRIBUTES = 22;


class Mushroom: public ID3DataEntry
{
public:
	Mushroom();
	Mushroom(bool edible, int attributes[]);
	
	bool isEdible();
	virtual int getAttribute(int key);
	virtual bool getState();

	void setAttribute(int key, int value);
	void setEdible(bool edible);

private:
	int mAttributes[NUM_ATTRIBUTES];
	bool mEdible;
};

#endif