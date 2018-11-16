
// File name: 	Accumulator.cpp
// Author: 		Nathanael Fuller
// Author: 		Bryan Kline
// Class:		CS445
// Date:		May 3, 2018
// Description:	Accumulator class implementation file (C++)

#ifndef ACCUMULATOR_CPP
#define ACCUMULATOR_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Accumulator.h"

using namespace std;	

#define MAX_SIZE 1000

// Name:		Accumulator				
// Description:	Accumulator class default constructor
// Parameters:	None
// Return:		None	
Accumulator:: Accumulator()
{
	maxScore = 0;
	cutOffValue = INFINITY;
	threshold = THRESHOLD;
}

// Name:		~Accumulator				
// Description:	Accumulator class destructor
// Parameters:	None
// Return:		None	
Accumulator:: ~Accumulator()
{
	updatedTerms.clear();
	keyTerms.clear();
}

// Name:		buildAccumulator					
// Description:	Accumulator class method which takes in the parsedDatabase and the dictionary and builds a
//				a data structure containing KeyTerm structs which hold all the terms in the scraped content,
//				if content in the data structure is found in the dictionary then it is assigned a score signifying
//				it is a dictionary term, otherwise it gets initialized to a score of zero
// Parameters:	Takes in a two dimensional vector of string which holds the parsed content from the sites 
//				scraped and a vector of strings which is the dictionary
// Return:		Void	
void Accumulator:: buildAccumulator(vector< vector<string> > parsedDatabase, vector<string> dictionary)
{
	int row, column, rowSize, columnSize;
	KeyTerm tempKeyTerm;
	vector<KeyTerm> tempKeyTermVector;

	rowSize = parsedDatabase.size();
	for(row = 0; row < rowSize; row++)
	{
		columnSize = parsedDatabase[row].size();
		for(column = 0; column < columnSize; column++)
		{
			tempKeyTerm.term = "";
			tempKeyTerm.score = 0;
			tempKeyTerm.term = parsedDatabase[row][column];

			if(dictionaryCheck(dictionary, parsedDatabase[row][column]))
			{
				tempKeyTerm.score = DICTIONARY_TERM;
			}

			tempKeyTermVector.push_back(tempKeyTerm);
		}

		keyTerms.push_back(tempKeyTermVector);
		tempKeyTermVector.clear();
	} 
}

// Name:		accumulate					
// Description:	Accumulator class method which moves through the data structure containing KeyTerm structs
//				holding the parsed content from the sites scraped and accumulates each item's score by determining
//				whether there are dictionary terms proximal to it and whether the item is found elsewhere in the 
//				structure
// Parameters:	None
// Return:		Void	
void Accumulator:: accumulate()
{
	int row, column, rowSize, columnSize;

	rowSize = keyTerms.size();
	for(row = 0; row < rowSize; row++)
	{
		columnSize = keyTerms[row].size();
		for(column = 0; column < columnSize; column++)
		{
			if((column > 0 && keyTerms[row][column - 1].score == DICTIONARY_TERM) || 
				(column < columnSize - 1 && keyTerms[row][column + 1].score == DICTIONARY_TERM))
			{
				keyTerms[row][column].score++;
			}

			keyTerms[row][column].score += frequencyScore(keyTerms[row][column].term);
		}
	}		
}

// Name:		frequencyScore				
// Description:	Accumulator class method which moves through the data structure containing the scraped content
//				and enumerates a score based on the frequency with which that item has occured
// Parameters:	None
// Return:		None	
int Accumulator:: frequencyScore(string term)
{
	int row, column, rowSize, columnSize, score = 0;

	rowSize = keyTerms.size();
	for(row = 0; row < rowSize; row++)
	{
		columnSize = keyTerms[row].size();
		for(column = 0; column < columnSize; column++)
		{
			if(term == keyTerms[row][column].term && keyTerms[row][column].score != DICTIONARY_TERM)
			{
				score++;
			}
		}
	}	

	return score;	
}

// Name:		thresholdAccumulator				
// Description:	Accumulator class method which moves through the accumulator and removes all values which
//				are some threshold proportion of the highest scored item in the accumulator
// Parameters:	None
// Return:		Void	
void Accumulator:: thresholdAccumulator()
{
	int row, column, rowSize, columnSize;

	rowSize = keyTerms.size();
	for(row = 0; row < rowSize; row++)
	{
		columnSize = keyTerms[row].size();
		for(column = 0; column < columnSize; column++)
		{
			if(keyTerms[row][column].score > maxScore)
			{
				maxScore = keyTerms[row][column].score;
			}
		}
	}		

	cutOffValue = maxScore * threshold;

	for(row = 0; row < rowSize; row++)
	{
		columnSize = keyTerms[row].size();
		for(column = 0; column < columnSize; column++)
		{
			if(keyTerms[row][column].score > cutOffValue && !termUpdated(keyTerms[row][column].term))
			{
				updatedTerms.push_back(keyTerms[row][column].term);
			}
		}
	}
}

// Name:		termUpdated				
// Description:	Accumulator class method which takes in a candidate term for addtion to the dictionary and moves 
//				through the terms to be added to the dictionary and checks if the candidate is already to be added
//				so as to avoid adding duplicates
// Parameters:	Takes in a string which is a candidate addition to the dictionary
// Return:		Returns a bool corresponding to whether or not the input string has already been added to the
//				structure which holds the new additions to the dictionary	
bool Accumulator:: termUpdated(string term)
{
	int index, size;

	size = updatedTerms.size();
	for(index = 0; index < size; index++)
	{
		if(term == updatedTerms[index])
		{
			return true;
		}
	}	

	return false;
}

// Name:		updateDictionary				
// Description:	Accumulator class method which writes the terms to be added to the dictionary to the dictionary
//				file
// Parameters:	None
// Return:		Void	
void Accumulator:: updateDictionary()
{
	int index, size;
	string tempString;
	ofstream outFile;

	outFile.open("dictionary.txt", ofstream::app); 

	size = updatedTerms.size();
	for(index = 0; index < size; index++)
	{
		tempString = toUpper(updatedTerms[index]);
		outFile << tempString;
		outFile << "\n";
	}	

	outFile.close();
}

// Name:		dictionaryCheck				
// Description:	Accumulator class method which takes in the dictionary and a string and returns a bool signaling
//				whether or not the string is found so that the items in the accumulator can be assigned proper scores
// Parameters:	Takes in a vector of strings which is the dictionary and an input string which is being sought
//				in the dictionary
// Return:		Returns a bool corresponding to whether or not the input string is found in the dictionary	
bool Accumulator:: dictionaryCheck(vector<string> dictionary, string input)
{
	int index, size;

	size = dictionary.size();
	for(index = 0; index < size; index++)
	{
		if(input == dictionary[index])
		{
			return true;
		}
	}
	
	return false;
}

// Name:		toUpper				
// Description:	Accumulator class method which takes in a string and converts all lower case chars in
//				the string to upper case so that new dictionary entries are upper case for tracking purposes
// Parameters:	Takes in a string to be converted to upper case
// Return:		Returns a string which is the input string in upper case	
string Accumulator:: toUpper(string input)
{
	int index, size;
	char buffer[MAX_SIZE];

	strcpy(buffer, input.c_str());

	size = input.size();
	for(index = 0; index < size; index++)	
	{
		if(buffer[index] >= 'a' && buffer[index] <= 'z')
		{
			buffer[index] -= ('a' - 'A');
		}
	}

	return buffer;
}

// Name:		diagnosticPrint					
// Description:	Accumulator class method which prints the screen the various data members and structures in the
//				class for diagnositc purposes
// Parameters:	None
// Return:		Void	
void Accumulator:: diagnosticPrint()
{
	int row, column, rowSize, columnSize;

	cout << "Max Score: " << maxScore << endl;
	cout << "Cut Off Value: " << cutOffValue << endl;

	cout << "Key Terms:" << endl;
	rowSize = keyTerms.size();
	for(row = 0; row < rowSize; row++)
	{
		cout << "Row " << row << ":" << endl;
		columnSize = keyTerms[row].size();
		for(column = 0; column < columnSize; column++)
		{
			cout << keyTerms[row][column].term << ":" << keyTerms[row][column].score << ", ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Updated Terms:" << endl;
	rowSize = updatedTerms.size();
	for(row = 0; row < rowSize; row++)
	{
		cout << updatedTerms[row]<< endl;
	}
	cout << endl;
}

#endif
