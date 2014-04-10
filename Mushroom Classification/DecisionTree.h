

#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <Windows.h>
#include <string>
using namespace std;

class ID3;

class DecisionTree
{
	friend class ID3;
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

		Node(int data)
		{
			mData     = data;
			mDecision = 0;
			mSibling  = NULL;
			mChild    = NULL;
		}
			
		Node(int data, Node *sibling, Node *child)
		{
			mData     = data;
			mDecision = 0;
			mSibling  = sibling;
			mChild    = child;
		}
	};

	Node* mRootNode;

	void displaySubtree(Node *node, string tab);
	
public:
	
	DecisionTree();
	~DecisionTree();
	
	void destroySubtree(Node *node);

	void display();
	
};



#endif