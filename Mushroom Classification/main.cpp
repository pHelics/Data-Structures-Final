/* ***       Author:  David Jordan
     *  Last Update:  February 26, 2014
     *        Class:  CSI-281-01
     *     Filename:  pa6.cpp
     *
     *  Description:
     *      This is main function of the program
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#include "mushroomLoader.h"
#include "id3Algorithm.h"
#include <fstream>
#include <iostream>
using namespace std;


void main() 
{

	//// TESTING PURPOSES ////
	MushroomLoader loader;
	ID3Algorithm algorithm(NUM_ATTRIBUTES);

	// Load the mushroom dataset into the algorithm.
	cout << "Loading Dataset.\n";
	loader.loadMushroomSetIntoID3(algorithm, "dataset.txt");

	// Run the algorithm, generating the decision tree.
	cout << "Creating Decision Tree.\n\n";
	algorithm.generate();
	algorithm.getDecisionTree().display();

	// Save the decision tree to a file.
	cout << "\nSaving decision tree to file.\n";
	algorithm.getDecisionTree().save("treeData.txt");

	// Classify a test mushroom.
	Mushroom *test = loader.loadMushroom("input1.txt", false);
	if (algorithm.getDecisionTree().classify(test))
		cout << "Test = Edible\n";
	else
		cout << "Test = Poisonous\n";
	delete test;
	///////////////////////////



	cout << "\n\n";
	system("pause");
}
