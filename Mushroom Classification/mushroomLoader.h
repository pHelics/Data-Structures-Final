/* ***       Author:  David Jordan
     *  Last Update:  February 27, 2014
     *        Class:  CSI-281-01
     *     Filename:  classifier.h
     *
     *  Description:
     *      This is the header for the classifier class, which
	 *      uses the k-NN algorithm in order to classify
	 *      mushrooms based on known mushroom data loaded from
	 *      a file.
     *		
	 *  Accuracy:
	 *     With a k-value of 9, the system has an accuracy of 75.71%
	 *
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef MUSHROOM_LOADER_H
#define MUSHROOM_LOADER_H

#include <string>
#include "id3Algorithm.h"
#include "mushroom.h"
using namespace std;

const string ATTRIBUTES_FILE_NAME   = "attributes.txt";

class MushroomLoader
{
public:
	MushroomLoader();
	
	int getNumAttributeValues(int attribute);
	void loadMushroomSetIntoID3(ID3Algorithm &algorithm, string filename);
	Mushroom* loadMushroom(string filename, bool includesEdibility);
	Mushroom* parseMushroom(string data, bool includesEdibility);

private:

	string mAttributeChars[NUM_ATTRIBUTES];
};

#endif