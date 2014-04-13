
#include <fstream>
#include <iostream>
#include "id3Algorithm.h"
#include <string>
using namespace std;


ID3Algorithm::ID3Algorithm(int numAttributes):
	mNumAttributes(numAttributes),
	mTree(),
	mDataset()
{
	mNumAttributeValues = new int[numAttributes];
}

ID3Algorithm::~ID3Algorithm()
{
	for (int i = 0; i < mDataset.size(); i++)
	{
		delete mDataset[i];
	}

	delete [] mNumAttributeValues;
}

void ID3Algorithm::addData(ID3DataEntry *data)
{
	mDataset.add(data);
}

void ID3Algorithm::setNumAttributeValues(int attributeIndex, int numValues)
{
	mNumAttributeValues[attributeIndex] = numValues;
}

double ID3Algorithm::calculateEntropy(int numPositive, int numEntries)
{
	if (numPositive == 0 || numPositive == numEntries)
		return 0;
	double pos = numPositive / (double) numEntries;
	double neg = 1 - pos;
	return (-pos * (log(pos) / log(2))) - (neg * (log(neg) / log(2)));
}

bool ID3Algorithm::isEntryMatchingScenario(ID3DataEntry *entry, int *scenario)
{
	for (int i = 0; i < mNumAttributes; i++)
	{
		if (scenario[i] >= 0 && entry->getAttribute(i) != scenario[i])
			return false;
	}
	return true;
}

void ID3Algorithm::countEntriesMatchingScenario(int &countPositive, int &countTotal, int *scenario)
{
	countPositive = 0;
	countTotal    = 0;
	for (int i = 0; i < mDataset.size(); i++)
	{
		if (isEntryMatchingScenario(mDataset[i], scenario))
		{
			countTotal++;
			if (mDataset[i]->getState())
				countPositive++;
		}
	}
}

int ID3Algorithm::getNextAttribute(double currentEntropy, int *scenario, int totalEntries)
{
	int j;
	double atrEntropy;
	double atrValueEntropy;
	double maxInfoGain = -1;
	int nextAtrIndex   = 0;
	int *atrValueCountTotal;
	int *atrValueCountPositive;

	// Find the next most informative attribute.
	for (int i = 0; i < mNumAttributes; i++)
	{
		// Check if this attribute has been used already.
		if (scenario[i] < 0)
		{
			atrValueCountTotal    = new int[mNumAttributeValues[i]];
			atrValueCountPositive = new int[mNumAttributeValues[i]];
			atrEntropy    = 0;

			// Calculate the total entropy of the atribute
			for (j = 0; j < mNumAttributeValues[i]; j++)
			{
				// Count up the total number and number of positive entries.		
				scenario[i] = j;
				countEntriesMatchingScenario(atrValueCountPositive[j], atrValueCountTotal[j], scenario);
				scenario[i] = -1;

				// Calculate the entropy of this attribute value.
				atrValueEntropy = calculateEntropy(atrValueCountPositive[j], atrValueCountTotal[j]);
				atrEntropy += (atrValueCountTotal[j] / (double) totalEntries) * atrValueEntropy;
			}
		
			// Remember the attribute with the most information gain.
			if (currentEntropy - atrEntropy > maxInfoGain)
			{
				maxInfoGain  = currentEntropy - atrEntropy;
				nextAtrIndex = i;
			}

			delete [] atrValueCountTotal;
			delete [] atrValueCountPositive;
		}
	}

	return nextAtrIndex;
}

void ID3Algorithm::generate()
{
	int *scenario = new int[mNumAttributes];
	for (int i = 0; i < mNumAttributes; i++)
		scenario[i] = -1;
	
	mTree.destroySubtree(mTree.mRootNode);
	mTree.mRootNode = new DecisionTree::Node;

	generate(mTree.mRootNode, 0, scenario);

	delete scenario;
}

void ID3Algorithm::generate(DecisionTree::Node* branch, double currentEntropy, int* scenario)
{
	// Count the number of entries fitting this scenario.
	int countTotal, countPositive;
	countEntriesMatchingScenario(countPositive, countTotal, scenario);

	if (countPositive == 0)
	{
		// Negative Leaf Node
		branch->mData = 0;
	}
	else if (countPositive == countTotal)
	{
		// Positive Leaf Node
		branch->mData = 1;
	}
	else
	{
		// Calculate entropy, create a new branch, and find the next attribute.
		currentEntropy    = calculateEntropy(countPositive, countTotal);
		int nextAttribute = getNextAttribute(currentEntropy, scenario, countTotal);
		branch->mData     = nextAttribute;

		// Branch off into the next attribute decisions.
		DecisionTree::Node *nextBranch = new DecisionTree::Node;
		branch->mChild = nextBranch;

		for (int i = 0; i < mNumAttributeValues[nextAttribute]; i++)
		{
			if (i > 0)
			{
				nextBranch->mSibling = new DecisionTree::Node;
				nextBranch = nextBranch->mSibling;
			}
			nextBranch->mDecision   = i;
			scenario[nextAttribute] = i;
			generate(nextBranch, 0, scenario);
			
		}
		scenario[nextAttribute] = -1;
	}
}

DecisionTree& ID3Algorithm::getDecisionTree()
{
	return mTree;
}