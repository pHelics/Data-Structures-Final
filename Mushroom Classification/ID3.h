
#ifndef ID3_H
#define ID3_H

#include "DecisionTree.h"
#include "dynamicArray.h"
#include "ID3DataEntry.h"

using namespace std;

class ID3
{
public:
	ID3(int numAttributes);
	~ID3();

	void addData(ID3DataEntry *data);
	void generate();
	void setNumAttributeValues(int attributeIndex, int numValues);

	DecisionTree& getTree();

private:
	bool isEntryMatchingScenario(ID3DataEntry *entry, int *scenario);
	double calculateEntropy(int numPositive, int numEntries);
	int getNextAttribute(double currentEntropy, int *scenario, int totalEntries);
	void generate(DecisionTree::Node* branch, double currentEntropy, int* scenario);

	int mNumAttributes;
	int *mNumAttributeValues;
	DynamicArray<ID3DataEntry*> mDataset;
	DecisionTree mTree;
};

#endif