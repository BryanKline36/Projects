
// File name: 	Accumulator.h
// Author: 		Nathanael Fuller
// Author: 		Bryan Kline
// Class:		CS445
// Date:		May 3, 2018
// Description:	Accumulator class header file (C++)

#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <string>
#include <vector>

using namespace std;

struct KeyTerm
{
	string term;
	int score;
};

class Accumulator
{
	static const int INFINITY = 999999999;
	static const int DICTIONARY_TERM = -1;
	static const float THRESHOLD = 0.3;

	public:

		Accumulator();
		~Accumulator();

		void buildAccumulator(vector< vector<string> > parsedDatabase, vector<string> dictionary);
		void accumulate();
		int frequencyScore(string term);
		void thresholdAccumulator();
		bool termUpdated(string term);
		void updateDictionary();
		bool dictionaryCheck(vector<string> dictionary, string input);
		string toUpper(string input);
		void diagnosticPrint();

	private:

		int maxScore;
		int cutOffValue;
		float threshold;	

		vector<string> updatedTerms;
		vector< vector<KeyTerm> > keyTerms;
};

#endif
