
#include "DecisionTree.h"
#include <string>
#include <iostream>
#include <fstream>

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

void DecisionTree::saveBranch(ofstream &file, Node *branch)
{
	if (branch != NULL)
	{
		file << branch->mDecision << " ";
		file << branch->mData << " ";
	
		// Count the number of children.
		int children = 0;
		Node *temp   = branch->mChild;
		while (temp != NULL)
		{
			temp = temp->mSibling;
			children++;
		}
		file << children << " ";

		// Save the children
		temp = branch->mChild;
		while (temp != NULL)
		{
			saveBranch(file, temp);
			temp = temp->mSibling;
		}
	}
}

void DecisionTree::loadBranch(ifstream &file, Node *branch)
{
	int numChildren;
	
	if (file.eof())
		return;

	file >> branch->mDecision;
	if (file.eof())
		return;

	file >> branch->mData;
	if (file.eof())
		return;

	file >> numChildren;
	if (file.eof())
		return;

	if (numChildren > 0)
	{
		Node *temp     = new Node;
		branch->mChild = temp;
		branch         = temp;

		for (int i = 0; i < numChildren; i++)
		{
			loadBranch(file, branch);

			if (i + 1 < numChildren)
			{
				temp             = new Node;
				branch->mSibling = temp;
				branch           = temp;
			}
		}
	}
}

bool DecisionTree::classify(ID3DataEntry *object)
{
	Node *temp = mRootNode;
	int attribute;

	while (temp != NULL)
	{
		if (temp->mChild == NULL)
		{
			// Leaf Node Found
			return (temp->mData == 1);
		}
		else
		{
			// Find the value of this attribute
			attribute = temp->mData;
			temp = temp->mChild;
			
			while (object->getAttribute(attribute) != temp->mDecision)
			{
				temp = temp->mSibling;

				if (temp == NULL)
				{
					// Error, no matching value found.
					cout << "No match found.\n";
					return false;
				}
			}
		}
	}

	cout << "Decision tree is not constructed.\n";
	return false;
}

void DecisionTree::save(string filename)
{
	ofstream file(filename);
	
	if (file.good())
	{
		saveBranch(file, mRootNode);
	}

	file.close();
}

void DecisionTree::load(string filename)
{
	destroySubtree(mRootNode);

	ifstream file(filename);
	
	if (file.good() && !file.eof())
	{
		mRootNode = new Node;
		loadBranch(file, mRootNode);
	}

	file.close();
}
