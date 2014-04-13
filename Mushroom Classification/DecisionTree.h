

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <Windows.h>
#include <string>
#include "ID3DataEntry.h"
using namespace std;

class ID3;

class DecisionTree
{
	friend class ID3Algorithm;
private:
	struct Node
	{
		int mData;
		int mDecision;
		Node *mSibling, *mChild;
		
		Node()
		{
			mData     = 0;
			mDecision = 0;
			mSibling  = NULL;
			mChild    = NULL;
		}
	};

	Node* mRootNode;

	void displaySubtree(Node *node, string tab);
	void loadBranch(ifstream &file, Node *branch);
	void saveBranch(ofstream &file, Node *branch);
	
public:
	
	DecisionTree();
	~DecisionTree();
	
	void destroySubtree(Node *node);

	void display();
	
	bool classify(ID3DataEntry *object);
	void save(string filename);
	void load(string filename);
	
};



#endif