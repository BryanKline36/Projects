
// File name: 	Dictionary.h
// Author: 		Nathanael Fuller
// Author: 		Bryan Kline
// Class:		CS445
// Date:		May 3, 2018
// Description:	Dictionary class header file (C++)

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include "Accumulator.h"

using namespace std;

class Dictionary
{
	public:

		Dictionary(bool verboseFlag);
		~Dictionary();

		void readInDatabase();
		void readInDictionary();
		void readInExclusionDictionary();
		void run();
		void parseDatabase();
		void excludeTerms();
		bool searchExclusionDictionary(string input);
		void diagnosticPrint();

	private:

		bool verbose;

		vector<string> rawDatabase;
	 	vector<string> dictionary;
		vector<string> exclusionDictionary;
		vector< vector<string> > parsedDatabase;

		Accumulator accumulator;
};

#endif
