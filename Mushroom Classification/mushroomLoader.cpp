/* ***       Author:  David Jordan
     *  Last Update:  February 26, 2014
     *        Class:  CSI-281-01
     *     Filename:  mushroomLoader.cpp
     *
     *  Description:
     *      This is the definition for the classifier class.
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#include "mushroomLoader.h"
#include <fstream>
#include <iostream>



MushroomLoader::MushroomLoader()
{
	ifstream file(ATTRIBUTES_FILE_NAME);
	
	for (int i = 0; i < NUM_ATTRIBUTES; i++)
		getline(file, mAttributeChars[i]);	

	file.close();
}


int MushroomLoader::getNumAttributeValues(int attribute)
{
	return mAttributeChars[attribute].length();
}


void MushroomLoader::loadMushroomSetIntoID3(ID3Algorithm &algorithm, string filename)
{
	// Link the number of values per attribute.
	for (int i = 0; i < NUM_ATTRIBUTES; i++)
		algorithm.setNumAttributeValues(i, getNumAttributeValues(i));

	// Load valid mushroom entries into the algorithm.
	ifstream file(filename);

	if (file.good())
	{
		string data;
		Mushroom *entry;

		while (!file.eof())
		{
			getline(file, data);
			entry = parseMushroom(data, true);
			if (entry != NULL)
				algorithm.addData(entry);
		}
	}

	file.close();
}


Mushroom* MushroomLoader::loadMushroom(string filename, bool includesEdibility)
{
	
	ifstream file(filename);
	Mushroom *result = NULL;

	if (file.good() && !file.eof())
	{
		string data;
		getline(file, data);
		result = parseMushroom(data, includesEdibility);
	}

	file.close();
	return result;
}

Mushroom* MushroomLoader::parseMushroom(string data, bool includesEdibility)
{
	int offset = 0;
	if (includesEdibility)
		offset = 1;

	// Check if the data length is valid.
	if (data.length() != (2 * (NUM_ATTRIBUTES + offset)) - 1)
		return NULL;

	int attributes[NUM_ATTRIBUTES];
	char c;
	int i, j;
	bool edible = false;
	if (includesEdibility)
		edible = (data[0] == 'e');

	// Read the characters for each attribute.
	for (i = 0; i < NUM_ATTRIBUTES; i++)
	{
		c = data[2 * (i + offset)];
		attributes[i] = 0;

		// Ignore mushrooms with unknown attributes.
		if (c == '?')
			return NULL;

		// Find the index of the attribute character.
		for (j = 0; j < (int) mAttributeChars[i].length(); j++)
		{
			if (mAttributeChars[i][j] == c)
			{
				attributes[i] = j;
				break;
			}
		}
	}

	return new Mushroom(edible, attributes);
}