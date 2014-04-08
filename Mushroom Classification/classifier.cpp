/* ***       Author:  David Jordan
     *  Last Update:  February 26, 2014
     *        Class:  CSI-281-01
     *     Filename:  classifier.cpp
     *
     *  Description:
     *      This is the definition for the classifier class.
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#include "classifier.h"
#include <fstream>
#include <iostream>



/*     Post:  The classifier is constructed with the attribute characters
 *            loaded by file
 *****************************************************************************/
Classifier::Classifier():
	mDataset(INITIAL_DATASET_CAPACITY)
{
	ifstream file(ATTRIBUTE_FILE_NAME);
	
	for (int i = 0; i < NUM_ATTRIBUTES; i++)
		getline(file, mAttributeChars[i]);	

	file.close();
}

/*     Post:  The memory from the dataset is freed
 *****************************************************************************/
Classifier::~Classifier()
{
	for (int i = 0; i < mDataset.size(); i++)
	{
		delete mDataset[i];
	}
}


/*      Pre:  The k-value is a positive, odd integer
 *     Post:  The accuracy is returned
 *  Purpose:  To calculate the accuracy of the system with the given k-value
 *****************************************************************************/
double Classifier::caclulateAccuracy(int kValue)
{
	double accuracy = 0;
	double foldAccuracy;
	cout << "Calculating system accuracy with a k-value of " << kValue << "...\n";

	for (int i = 0; i < NUM_FOLDS; i++)
	{
		foldAccuracy = getFoldAccuracy(i, NUM_FOLDS, kValue);
		cout << "Fold " << (i + 1) << ": " << (foldAccuracy * 100) << "%\n";
		accuracy += foldAccuracy;
	}

	accuracy /= NUM_FOLDS;
	cout << "Average Accuracy: " << (accuracy * 100) << "%\n";

	return accuracy;
}


/*      Pre:  The mushroom is instantiated and the k-value is a positive, odd integer
 *     Post:  A boolean of whether the mushroom is edible or not is returned
 *  Purpose:  To classify a mushroom as edible or not edible (poisonous)
 *****************************************************************************/
bool Classifier::classify(Mushroom *testMushroom, int kValue)
{
	double dist;
	double maxDistance = kValue * kValue;
	int edibility = 0;

	for (int i = 0; i < mDataset.size(); i++)
	{
		dist = distanceSquared(testMushroom, mDataset[i]);

		if (dist == 0)
		{
			edibility = 1;
			break;
		}
		else if (dist <= maxDistance)
		{
			if (mDataset[i]->isEdible())
				edibility++;
			else
				edibility--;
		}
	}

	return (edibility > 0);
}


/*      Pre:  The file contains correctly formatted mushroom data
 *     Post:  The dataset of known mushrooms is loaded into the system
 *  Purpose:  To load mushrooms from a file into the dataset (as a training set)
 *****************************************************************************/
void Classifier::loadDataset(string filename)
{
	ifstream file(filename);

	if (file.good())
	{
		int i, j;
		char c;
		int attributes[NUM_ATTRIBUTES];
		bool edible, valid;
		string data;

		while (!file.eof())
		{
			getline(file, data);

			if (data.length() == (2 * NUM_ATTRIBUTES) + 1)
			{
				valid  = true;
				edible = (data[0] == 'e');

				// Read each attribute character.
				for (i = 0; i < NUM_ATTRIBUTES; i++)
				{
					c = data[2 * (i + 1)];

					if (c == '?')
					{
						valid = false;
						break;
					}

					attributes[i] = 0;

					// Find the integer value for the character.
					for (j = 0; j < (int) mAttributeChars[i].length(); j++)
					{
						if (mAttributeChars[i][j] == c)
						{
							attributes[i] = j;
							break;
						}
					}
				}

				if (valid)
					mDataset.add(new Mushroom(edible, attributes));
			}
		}
	}

	file.close();
}


/*      Pre:  The string of data is formatted as characters seperated by commas,
 *            not including the initial p/e character determining edibility
 *     Post:  A mushroom represented by the string of data is returned
 *  Purpose:  To parse a mushroom from a string of data
 *****************************************************************************/
Mushroom* Classifier::parseTestMushroom(string mushroomData)
{
	int attributes[NUM_ATTRIBUTES];
	char c;
	int i, j;

	for (i = 0; i < NUM_ATTRIBUTES; i++)
	{
		c = mushroomData[2 * i];
		attributes[i] = 0;

		for (j = 0; j < (int) mAttributeChars[i].length(); j++)
		{
			if (mAttributeChars[i][j] == c)
			{
				attributes[i] = j;
				break;
			}
		}
	}

	return new Mushroom(false, attributes);
}


/*      Pre:  Both mushrooms are instantiated
 *     Post:  The squared distance between the two mushrooms is returned
 *  Purpose:  To calculate the distance between two mushrooms
 *****************************************************************************/
int Classifier::distanceSquared(Mushroom *m1, Mushroom *m2)
{
	int dist = 0;
	int x;

	for (int i = 0; i < NUM_ATTRIBUTES; i++)
	{
		x = m1->getAttribute(i) - m2->getAttribute(i);
		dist += (x * x);
	}

	return dist;
}


/*      Pre:  The fold index is valid, the number of folds is less than the
 *            number of dataset entries, and the k-value is positive and odd.
 *     Post:  The accuracy of the fold (portion of the dataset) is returned
 *  Purpose:  To calculate the accuracy of classifying a specific fold of the dataset
 *****************************************************************************/
double Classifier::getFoldAccuracy(int foldIndex, int numFolds, int kValue)
{
	int maxDistance = kValue * kValue;
	int foldSize = (mDataset.size() / numFolds);
	int start    = foldSize * foldIndex;
	int end      = start + foldSize;
	if (end >= mDataset.size())
		end = mDataset.size();
	
	int total      = 0;
	int numCorrect = 0;
	int edibility;

	for (int i = start; i < end; i++)
	{
		Mushroom* testMushroom = mDataset[i];
		total++;

		edibility  = getSetEdibility(testMushroom, maxDistance, 0, start);
		edibility += getSetEdibility(testMushroom, maxDistance, end, mDataset.size());

		if ((edibility > 0) == testMushroom->isEdible())
			numCorrect++;
	}

	return ((double) numCorrect / total);
}


/*      Pre:  The mushroom is instantiated, the max distance is the square of an even,
 *            positive integer, and the lower bound and upper bounds define a portion
 *            of the dataset
 *     Post:  The edibility index accumulated is returned
 *  Purpose:  To get the edibility index of the mushroom compared to the given portion
 *            of the dataset
 *****************************************************************************/
int Classifier::getSetEdibility(Mushroom* testMushroom, int maxDistance, int lowerBound, int upperBound)
{
	int edibility = 0;
	int dist;

	for (int i = lowerBound; i < upperBound; i++)
	{
		dist = distanceSquared(testMushroom, mDataset[i]);

		if (dist <= maxDistance)
		{
			if (mDataset[i]->isEdible())
				edibility++;
			else
				edibility--;
		}
	}

	return edibility;
}
