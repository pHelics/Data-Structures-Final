
#ifndef ID3_H
#define ID3_H

#include "decisionTree.h"
#include "dynamicArray.h"
#include "id3DataEntry.h"

using namespace std;

class ID3Algorithm
{
public:
	ID3Algorithm(int numAttributes);
	~ID3Algorithm();

	void addData(ID3DataEntry *data);
	void generate();
	void setNumAttributeValues(int attributeIndex, int numValues);

	DecisionTree& getDecisionTree();

private:
	bool isEntryMatchingScenario(ID3DataEntry *entry, int *scenario);
	void countEntriesMatchingScenario(int &countPositive, int &countTotal, int *scenario);
	double calculateEntropy(int numPositive, int numEntries);
	int getNextAttribute(double currentEntropy, int *scenario, int totalEntries);
	void generate(DecisionTree::Node* branch, double currentEntropy, int* scenario);

	int mNumAttributes;
	int *mNumAttributeValues;
	DynamicArray<ID3DataEntry*> mDataset;
	DecisionTree mTree;
};

#endif