
//File Name:	Spreadsheet.h
//Description:	Spreadsheet class header
//Author:		Bryan Kline
//Date:			01/10/19

#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <string>
#include <vector>
#include <map>

struct Value
{
	unsigned int status;
	int numericValue;
	std::string stringValue;

	Value()
	{
		status = 0;
		numericValue = 0;
		stringValue = "";
	}
};		

struct Cell
{	
	unsigned int row;
	unsigned int column;
	std::string name;

	Value value;
	
	Cell()
	{
		row = 0;
		column = 0;
		name = "";
	}
};

class Spreadsheet
{
	public:

		const int ALPHABET_SIZE = 26;
		const char UPPERCASE_A = 'A';
		const char UPPERCASE_Z = 'Z';
		const char UPPERCASE_D = 'D';
		const char LOWERCASE_D = 'd';
		const char UPPERCASE_V = 'V';
		const char LOWERCASE_V = 'v';
		const char ZERO = '0';
		const char NINE = '9';
		const char TAB = '\t';
		const char CARRIAGE_RETURN = '\r';
		const char EMPTY = '_';
		const char EQUAL = '=';
		const char PLUS = '+';
		const char MINUS = '-';
		const char MULTIPLY = '*';
		const char DIVIDE = '/';
		const std::string EMPTY_STRING = "";
		const std::string NAN = "#NAN";
		const std::string ERROR = "#ERROR";

		enum Status
		{
			empty = 0,
			numeric = 1,
			string = 2,
			equation = 4,
			nan = 8,
			error = 16,
			operatorSymbol = 32
		};

		Spreadsheet(int argc, char* argv[]);
		~Spreadsheet();

		void run();

	private:

		void getSpreadsheetSize();
		unsigned int countColumns(std::string row);
		void constructSpreadsheet();
		std::string incrementColumn(std::string inputString);

		void populateSpreadsheet();
		void setSpreadsheetRow(std::string columnValues, int row);

		Status checkCellStatus(std::string inputString);
		void buildCellMapping();

		void runCalculations();
		Value jumpToCell(std::string cellEquationTerm);
		std::vector<std::string> processEquation(std::string cellEquation);
		Value evaluateEquation(std::vector<std::string> equationTerms);
		std::vector<std::string> applyNegatives(std::vector<std::string> equationTerms);
		std::vector<Value> convertToNumeric(std::vector<std::string> equationTerms);

		bool isOperator(char operatorChar);
		bool isOperator(std::string operatorString);		
		void writeSpreadsheetToFile();
		void parseCommandLineArguments(int argc, char* argv[]);
		void printSpreadsheet();
		void printMapping();
		void printCell(Cell cell);

		int rows;
	 	int columns;
		bool carriageReturn;
		bool debug;
		bool verbose;
		bool runProgram;

		std::string inputFileName;
		std::string outputFileName;	

		Cell** spreadsheet;

		std::map<std::string, Cell*> cellMap;
		std::map<std::string, int> cellReferenceMap;
};

#endif	