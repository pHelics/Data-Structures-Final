#include "mushroom.h"
#include <iostream>

using namespace std;


/*     Post:  A mushroom with default attributes is created
 *  Purpose:  To construct a default mushroom object
 *****************************************************************************/
Mushroom::Mushroom()
{
	mEdible = false;
	for (int i = 0; i < NUM_ATTRIBUTES; i++)
		mAttributes[i] = 0;
}


/*      Pre:  The array of attributes is instantiated with correct number
 *            of elements as attributes
 *     Post:  The mushroom is constructed with the given ediblity and attributes
 *  Purpose:  To construct a mushroom from given edibility and set of attributes
 *****************************************************************************/
Mushroom::Mushroom(bool edible, int attributes[]):
	mEdible(edible)
{
	for (int i = 0; i < NUM_ATTRIBUTES; i++)
		mAttributes[i] = attributes[i];
}


/*      Pre:  The given key index is valid
 *     Post:  The integer value held in the key index is returned
 *  Purpose:  To obtain an attribute value from the musroom
 *****************************************************************************/
int Mushroom::getAttribute(int key)
{
	return mAttributes[key];
}


/*     Post:  The edibiliity of the mushroom is returned (true=edible, false=poisnous)
 *  Purpose:  To obtain the edibility of the mushroom
 *****************************************************************************/
bool Mushroom::isEdible()
{
	return mEdible;
}

bool Mushroom::getState()
{
	return mEdible;
}


/*      Pre:  The given key is valid
 *     Post:  The integer value is stored in the key index
 *  Purpose:  To change an attribute value of the mushroom
 *****************************************************************************/
void Mushroom::setAttribute(int key, int value)
{
	mAttributes[key] = value;
}


/*     Post:  The mushroom is set as edible or posinous (based on the given parameter)
 *  Purpose:  To set the edibility of the mushroom
 *****************************************************************************/
void Mushroom::setEdible(bool edible)
{
	mEdible = edible;
}


void Mushroom::setState(bool newState)
{
	mEdible = newState;
}