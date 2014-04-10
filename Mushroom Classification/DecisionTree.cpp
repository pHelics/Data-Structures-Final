
#include "DecisionTree.h"
#include <string>
#include <iostream>

DecisionTree::DecisionTree()
{
	mRootNode = NULL;
}

DecisionTree::~DecisionTree()
{
	destroySubtree(mRootNode);
}


void DecisionTree::destroySubtree(Node *node)
{
	if (node == NULL)
		return;

	destroySubtree(node->mSibling);
	destroySubtree(node->mChild);

	delete node;
}

void DecisionTree::displaySubtree(Node *node, string tab)
{
	if (node != NULL)
	{
		cout << tab << node->mDecision << " = ";
		if (node->mChild == NULL)
			cout << (node->mData == 1 ? "[+]" : "[-]");
		else
			cout << "(" << node->mData << ")";
		cout << endl;

		displaySubtree(node->mChild, tab + "     ");
		displaySubtree(node->mSibling, tab);
	}
}

void DecisionTree::display()
{
	displaySubtree(mRootNode, "");
}