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

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>
#include "dynamicArray.h"
#include "mushroom.h"
using namespace std;

const int INITIAL_DATASET_CAPACITY = 5000;
const int NUM_FOLDS                = 10;
const string ATTRIBUTE_FILE_NAME   = "attributes.txt";

class Classifier
{
public:
	Classifier();
	~Classifier();
	
	double caclulateAccuracy(int kValue);
	bool classify(Mushroom *testMushroom, int kValue);
	void loadDataset(string filename);
	Mushroom* parseTestMushroom(string mushroomData);

private:
	int distanceSquared(Mushroom *m1, Mushroom *m2);
	double getFoldAccuracy(int foldIndex, int numFolds, int kValue);
	int getSetEdibility(Mushroom* testMushroom, int maxDistance, int lowerBound, int upperBound);
	
	string mAttributeChars[NUM_ATTRIBUTES];
	DynamicArray<Mushroom*> mDataset;
};

#endif