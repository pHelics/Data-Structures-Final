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

#include "classifier.h"
#include "timerSystem.h"
#include "TestEntry.h"
#include "ID3.h"
#include <fstream>
#include <iostream>
using namespace std;


void testAlgorithm()
{
	/////////////////////////////////////
	// Testing Purposes:
	// Using the Example dataset from the ID3 pdf.

	ifstream file("testData.txt");
	ID3 algorithm(3);
	algorithm.setNumAttributeValues(0, 2);
	algorithm.setNumAttributeValues(1, 3);
	algorithm.setNumAttributeValues(2, 2);

	if (file.good())
	{
		string datastr;
		int i, state, temp;
		TestEntry* entry;

		while (!file.eof())
		{
			file >> state;
			entry = new TestEntry(state == 1);

			for (i = 0; i < 3; i++)
			{
				file >> temp;
				entry->setAttribute(i, temp);
			}

			algorithm.addData(entry);
		}
	}
	file.close();

	// Run the ID3 algorithm, creating the decision tree
	algorithm.generate();
	
	//////////////////////////////////////
}

void main() 
{
	// Test the ID3 Algorithm.
	// Feel free to comment this out.
	testAlgorithm();



	// OLD CODE from PA 6:
	/*
	TimerSystem timer;
	timer.startClock();
	
	Classifier classifier;
	classifier.loadDataset("dataset.txt");
	
	ifstream file(argv[1]);
	
	if (file.good())
	{
		int kValue;
		string mushroomData;
		file >> kValue;
		getline(file, mushroomData);
		getline(file, mushroomData);

		cout << "Classifying mushroom from the file \"" << argv[1] << "\"\n";
		Mushroom *test = classifier.parseTestMushroom(mushroomData);
		bool edible    = classifier.classify(test, kValue);
		double time    = timer.getTime();
		cout << "The Mushroom is " << (edible ? "edible" : "poisonous") << ".\n";
		cout << "Took " << time << " seconds.\n";
		
		delete test;
	}
	else
		cout << "The file \"" << argv[1] << "\"does not exist.\n";
	
	file.close();
	*/


	cout << "\n\n";
	system("pause");
}
