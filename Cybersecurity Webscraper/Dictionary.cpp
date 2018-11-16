
// File name: 	Dictionary.cpp
// Author: 		Nathanael Fuller
// Author: 		Bryan Kline
// Class:		CS445
// Date:		May 3, 2018
// Description:	Dictionary class implementation file (C++)

#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Accumulator.h"
#include "Dictionary.h"

using namespace std;	

#define MAX_SIZE 10000

// Name:		Dictionary				
// Description:	Dictionary class parameterized constructor
// Parameters:	None
// Return:		None	
Dictionary:: Dictionary(bool verboseFlag)
{
	verbose = verboseFlag;
}

// Name:		~Dictionary				
// Description:	Dictionary class destructor
// Parameters:	None
// Return:		None	
Dictionary:: ~Dictionary()
{
	rawDatabase.clear();
	parsedDatabase.clear();
	dictionary.clear();
	exclusionDictionary.clear();
}


// Name:		readInDatabase				
// Description:	Dictionary class method which opens and reads in the database into a local data structure
// Parameters:	None
// Return:		Void	
void Dictionary:: readInDatabase()
{
	string tempString;
	ifstream inFile;

	inFile.open("tempDatabase.txt");

	while(getline(inFile, tempString))
	{
		rawDatabase.push_back(tempString);
	} 

	inFile.close();
}


// Name:		readInDictionary				
// Description:	Dictionary class method which opens and reads in the dictionary into a local data structure
// Parameters:	None
// Return:		Void	
void Dictionary:: readInDictionary()
{
	string tempString;
	ifstream inFile;

	inFile.open("dictionary.txt");

	while(inFile >> tempString)
	{
		dictionary.push_back(tempString);
	} 

	inFile.close();
}

// Name:		readInExclusionDictionary				
// Description:	Dictionary class method which opens and reads in the exculsion dictionary into a local data structure 
// Parameters:	None
// Return:		Void	
void Dictionary:: readInExclusionDictionary()
{
	string tempString;
	ifstream inFile;

	inFile.open("exclusionDictionary.txt");

	while(inFile >> tempString)
	{
		exclusionDictionary.push_back(tempString);
	} 

	inFile.close();
}

// Name:		run				
// Description:	Dictionary class method which acts as the primary interface through which the program is accessed,
//				it calls the necessary Dictionary and Accumulator class methods in order to read in the data
//				from files, to parse and filter the data, to push the data into the accumulator data structure
//				and the then assign scores to the terms, and finally to update the dictionary
// Parameters:	None
// Return:		Void	
void Dictionary:: run()
{
	readInDatabase();
	readInDictionary();
	readInExclusionDictionary();
	parseDatabase();
	excludeTerms();

	if(verbose)
	{
		diagnosticPrint();
	}

	accumulator.buildAccumulator(parsedDatabase, dictionary);
	accumulator.accumulate();
	accumulator.thresholdAccumulator();
	accumulator.updateDictionary();

	if(verbose)
	{
		accumulator.diagnosticPrint();
	}
}

// Name:		parseDatabase				
// Description:	Dictionary class method which moves through the content scraped as several long strings and
//				breaks them down into words and removes whitespace and punctuation and pushes them into the 
//				data structure which holds the parsed content from the database
// Parameters:	None
// Return:		Void	
void Dictionary:: parseDatabase()
{
	int index, size;
	char buffer[MAX_SIZE];
	char* token;
	string tempString;
	string delimiters = " ,.;:-_?!@#$%^&*()=+[]{}";
	vector<string> tempStringVector;

	size = rawDatabase.size();
	for(index = 0; index < size; index++)
	{
		strcpy(buffer, rawDatabase[index].c_str());
		token = strtok(buffer, delimiters.c_str());

		while(token != NULL)
		{
			tempString = token;
			tempStringVector.push_back(tempString);
			token = strtok(NULL, delimiters.c_str());
		}	

		parsedDatabase.push_back(tempStringVector);
		tempStringVector.clear();
	}
}

// Name:		excludeTerms				
// Description:	Dictionary class method which steps through the parsed database data structure and removes
//				terms if they are found in the exluscion dictionary
// Parameters:	None
// Return:		Void	
void Dictionary:: excludeTerms()
{
	int row, column, rowSize, columnSize;

	rowSize = parsedDatabase.size();
	for(row = 0; row < rowSize; row++)
	{
		columnSize = parsedDatabase[row].size(); 	
		for(column = 0; column < columnSize; column++)
		{
			if(searchExclusionDictionary(parsedDatabase[row][column]))
			{
				parsedDatabase[row].erase(parsedDatabase[row].begin() + column);
				columnSize--;
				column--;
			}	
		}
	}	
}

// Name:		searchExclusionDictionary				
// Description:	Dictionary class method which takes in a term as a parameter and steps through the 
//				exclusion dictionary to check whether it is a term which should be excluded
// Parameters:	Takes in a string which search for in the exclusion dictionary
// Return:		Returns a bool corresponding to whether or not the input string is found in the exclusion
//				dictionary	
bool Dictionary:: searchExclusionDictionary(string input)
{
	int index, size;

	size = exclusionDictionary.size();
	for(index = 0; index < size; index++)
	{
		if(input == exclusionDictionary[index])
		{
			return true;
		}	
	}
	
	return false;	
}

// Name:		diagnosticPrint					
// Description:	Dictionary class method which prints to the screen all class data structures for diagnostic 
//				purposes
// Parameters:	None
// Return:		Void	
void Dictionary:: diagnosticPrint()
{
	int index, size, row, column, rowSize, columnSize;

	size = rawDatabase.size();
	cout << "Database:" << endl;
	for(index = 0; index < size; index++)
	{
		cout << rawDatabase[index]<< endl;
	}	
	cout << endl;

	size = dictionary.size();
	cout << "Dictionary:" << endl;
	for(index = 0; index < size; index++)
	{
		cout << dictionary[index] << endl;
	}	
	cout << endl;

	size = exclusionDictionary.size();
	cout << "Exclusion Dictionary:" << endl;
	for(index = 0; index < size; index++)
	{
		cout << exclusionDictionary[index] << endl;
	}	
	cout << endl;

	cout << "Parsed Database:" << endl;
	rowSize = parsedDatabase.size();
	for(row = 0; row < rowSize; row++)
	{
		columnSize = parsedDatabase[row].size(); 	
		for(column = 0; column < columnSize; column++)
		{
			cout << parsedDatabase[row][column] << " ";
		}
		cout << endl;
	}	
	cout << endl;
}

#endif
