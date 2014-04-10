
#include <fstream>
#include <iostream>
#include "ID3.h"
#include <string>
using namespace std;


ID3::ID3(int numAttributes):
	mNumAttributes(numAttributes),
	mTree(),
	mDataset()
{
	mNumAttributeValues = new int[numAttributes];
}

ID3::~ID3()
{
	for (int i = 0; i < mDataset.size(); i++)
	{
		delete mDataset[i];
	}

	delete [] mNumAttributeValues;
}

void ID3::addData(ID3DataEntry *data)
{
	mDataset.add(data);
}

void ID3::setNumAttributeValues(int attributeIndex, int numValues)
{
	mNumAttributeValues[attributeIndex] = numValues;
}

double ID3::calculateEntropy(int numPositive, int numEntries)
{
	if (numPositive == 0 || numPositive == numEntries)
		return 0;
	double pos = numPositive / (double) numEntries;
	double neg = 1 - pos;
	return (-pos * (log(pos) / log(2))) - (neg * (log(neg) / log(2)));
}

bool ID3::isEntryMatchingScenario(ID3DataEntry *entry, int *scenario)
{
	for (int i = 0; i < mNumAttributes; i++)
	{
		if (scenario[i] >= 0 && entry->getAttribute(i) != scenario[i])
			return false;
	}
	return true;
}

int ID3::getNextAttribute(double currentEntropy, int *scenario, int totalEntries)
{
	int j, k, l;
	double atrEntropy;
	double atrValueEntropy;
	double maxInfoGain = -1;
	int nextAtrIndex   = 0;
	int *atrValueTotal;
	int *atrValueCount;

	// Find the next most informative attribute.
	for (int i = 0; i < mNumAttributes; i++)
	{
		// Check if this attribute has been used already.
		if (scenario[i] >= 0)
			continue;

		atrValueTotal = new int[mNumAttributeValues[i]];
		atrValueCount = new int[mNumAttributeValues[i]];
		atrEntropy    = 0;

		// Calculate the total entropy of the atribute
		for (j = 0; j < mNumAttributeValues[i]; j++)
		{
			atrValueTotal[j] = 0;
			atrValueCount[j] = 0;

			// Count up the total number and number of positive entries.
			for (k = 0; k < mDataset.size(); k++)
			{
				// Check if this entry matches the current situation
				if (mDataset[k]->getAttribute(i) == j && isEntryMatchingScenario(mDataset[k], scenario))
				{
					atrValueTotal[j]++;
					if (mDataset[k]->getState())
						atrValueCount[j]++;
				}
			}

			// Calculate the entropy of this attribute value.
			atrValueEntropy = calculateEntropy(atrValueCount[j], atrValueTotal[j]);
			atrEntropy += (atrValueTotal[j] / (double) totalEntries) * atrValueEntropy;
			cout << "H(" << i << ">" << j << ") = " << atrValueEntropy << " (" << atrValueCount[j] << " / " << atrValueTotal[j] << ")\n";
		}
		
		// Remember the attribute with the most information gain.
		if (currentEntropy - atrEntropy > maxInfoGain)
		{
			maxInfoGain = currentEntropy - atrEntropy;
			nextAtrIndex = i;
		}
		
		cout << "H(" << i << ") = " << atrEntropy << "\n\n";

		delete [] atrValueTotal;
		delete [] atrValueCount;
	}

	return nextAtrIndex;
}

void ID3::generate()
{
	int numAttributes = 3;
	int *scenario = new int[numAttributes];
	for (int i = 0; i < numAttributes; i++)
		scenario[i] = -1;

	mTree.mRootNode = new DecisionTree::Node;

	generate(mTree.mRootNode, 0, scenario);

	mTree.display();

	delete scenario;
}

void ID3::generate(DecisionTree::Node* branch, double currentEntropy, int* scenario)
{
	// Compute the number of entries fitting this scenario.
	int total = 0;
	int count = 0;
	for (int i = 0; i < mDataset.size(); i++)
	{
		if (isEntryMatchingScenario(mDataset[i], scenario))
		{
			total++;
			if (mDataset[i]->getState())
				count++;
		}
	}


	if (count == 0)
	{
		// Negative Leaf Node
		branch->mData = 0;
		cout << "Leaf Node: Negative\n\n";
	}
	else if (count == total)
	{
		// Positive Leaf Node
		branch->mData = 1;
		cout << "Leaf Node: Positive\n\n";
	}
	else
	{
		// Calculate entropy, create a new branch, and find the next attribute.
		currentEntropy    = calculateEntropy(count, total);
		int nextAttribute = getNextAttribute(currentEntropy, scenario, total);
		branch->mData     = nextAttribute;
		cout << "Selecting Attribute " << nextAttribute << "\n\n";

		
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
			nextBranch->mDecision = i;

			scenario[nextAttribute] = i;
			generate(nextBranch, 0, scenario);
			
		}
		scenario[nextAttribute] = -1;
	}
}

DecisionTree& ID3::getTree()
{
	return mTree;
}