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
#include <fstream>
#include <iostream>
using namespace std;


void main(int argc, char **argv) 
{
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
	
	cout << endl;
	system("pause");
}
