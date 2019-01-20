
//File Name:	Spreadsheet.cpp
//Description:	Spreadsheet class implementation
//Author:		Bryan Kline
//Date:			01/10/19

#ifndef SPREADSHEET_CPP
#define SPREADSHEET_CPP

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Spreadsheet.h"


// Name:		Spreadsheet
// Description:	Spreadsheet class parameterized constructor which builds the spreadsheet
// Parameters:	Takes in the argument count and the arguments as strings in an array	
// Return:		None
Spreadsheet::Spreadsheet(int argc, char* argv[])
{
	carriageReturn = false;
	verbose = false;
	debug = false;
	runProgram = false;

	parseCommandLineArguments(argc, argv);

	if(runProgram)
	{
		getSpreadsheetSize();
		constructSpreadsheet();
	}
}

// Name:		~Spreadsheet
// Description:	Spreadsheet class destructor
// Parameters:	None
// Return:		None
Spreadsheet::~Spreadsheet()
{
	unsigned int index;

	if(spreadsheet != NULL && runProgram)
	{

		for(index = 0; index < rows; ++index)
		{
			delete [] spreadsheet[index];
		}

		delete [] spreadsheet;

		cellMap.clear();
		cellReferenceMap.clear();

	}
}

// Name:		run
// Description:	High level Spreadsheeet class method which reads from the input file, fills in the
//				spreadsheet, builds the cell mapping, runs the calculations, and prints the data
//				structures to the terminal if debug and verbose flags are set	
// Parameters:	None
// Return:		Void
void Spreadsheet::run()
{
	if(runProgram)
	{
		populateSpreadsheet();
		buildCellMapping();

		if(debug)
		{
			std::cout << "Spreadsheet before calculations:" << std::endl;	
			printSpreadsheet();	

			if(verbose)
			{
				std::cout << "Mapping:" << std::endl;	
				printMapping();
			}
		}

		runCalculations();
		writeSpreadsheetToFile();

		if(debug)
		{
			std::cout << "Spreadsheet after calculations:"<< std::endl;
			printSpreadsheet();	
		}
	}
}

// Name:		getSpreadsheetSize
// Description:	Spreadsheeet class method which opens and reads the input file to determine the max
//				rows and columns needed for the spreadsheet
// Parameters:	None
// Return:		Void
void Spreadsheet::getSpreadsheetSize()
{
	unsigned int rowCount = 0, columnCount, totalColumns = 0;
	std::string inputString;
	std::ifstream inFile;

	inFile.open(inputFileName);

	while(inFile.good() && !inFile.eof())
	{
		std::getline(inFile, inputString);

		if(inputString.size() > 0)
		{
			columnCount = countColumns(inputString);
			if(columnCount > totalColumns)
			{
				totalColumns = columnCount;
			}	

			rowCount++;
		}
	}	

	rows = rowCount;
	columns = totalColumns;

	inFile.close();
}

// Name:		countColumns
// Description:	Spreadsheeet class method which takes in a row from the input file and determines
//				the number of columns in it
// Parameters:	Takes in an entire row from the input file as a string
// Return:		Returns an unsigned int which is the column count
unsigned int Spreadsheet::countColumns(std::string row)
{
	unsigned int index, columnCount = 1, size = row.size();

	for(index = 0; index < size; ++index)
	{
		if(row[index] == TAB)
		{
			columnCount++;
		}
	}

	return columnCount;
}

// Name:		constructSpreadsheet
// Description:	Spreadsheeet class method which builds a two dimensional array of Cell structs which
//				will hold the data from the input file 
// Parameters:	None
// Return:		Void
void Spreadsheet::constructSpreadsheet()
{
	int innerIndex, outerIndex;
	char letter;
	std::string cellName;

	spreadsheet = new Cell*[rows];

	for(outerIndex = 0; outerIndex < rows; ++outerIndex)
	{
		spreadsheet[outerIndex] = new Cell[columns];

		cellName = EMPTY_STRING;
		for(innerIndex = 0; innerIndex < columns; ++innerIndex)
		{
			cellName = incrementColumn(cellName);

			spreadsheet[outerIndex][innerIndex].row = outerIndex;
			spreadsheet[outerIndex][innerIndex].column = innerIndex;
			spreadsheet[outerIndex][innerIndex].name = cellName + std::to_string(outerIndex + 1);
		}
	}
}

// Name:		incrementColumn
// Description:	Spreadsheeet class method which takes in a column label and increments it to produce the
//				next column label
// Parameters:	Takes in the label of the previous column as a string
// Return:		Returns the proper label for the current column by incrementing the previous one
std::string Spreadsheet::incrementColumn(std::string inputString)
{
	int index, size = inputString.size();

	index = size - 1;

	while(index >= 0 && inputString[index] == UPPERCASE_Z)
	{

		inputString[index] = UPPERCASE_A;
		index--;
	}

	if(index == -1)
	{
		inputString += UPPERCASE_A;
	}
	else
	{
		inputString[index] = (char) (((inputString[index] - UPPERCASE_A) + 1) % ALPHABET_SIZE) + UPPERCASE_A;	
	}

	return inputString;
}

// Name:		populateSpreadsheet
// Description:	Spreadsheeet class method which opens the input file, reads its contents, and populates the
//				spreadsheet with its values
// Parameters:	None
// Return:		Void
void Spreadsheet::populateSpreadsheet()
{
	int currentRow = 0;
	std::string inputString;
	std::ifstream inFile;

	inFile.open(inputFileName);

	while(currentRow < rows && inFile.good() && !inFile.eof())
	{
		std::getline(inFile, inputString);

		setSpreadsheetRow(inputString, currentRow);
		
		currentRow++;
	}	

	inFile.close();
}

// Name:		setSpreadsheetRow
// Description:	Spreadsheeet class method which takes in a row from the input file, moves through it,
//				extracts the contents of a cell, and adds it to the spreadsheet
// Parameters:	Takes in an entire row from the input file as a string and the row number as an int
// Return:		Void
void Spreadsheet::setSpreadsheetRow(std::string columnValues, int row)
{
	int index, column = 0, size = columnValues.size(), cellNumber, cellStatus;
	std::string cellString;

	if(columnValues[size - 1] == CARRIAGE_RETURN)
	{
		columnValues.erase(size - 1, 1);
		carriageReturn = true;
		size = columnValues.size();
	}

	for(index = 0; index < size; ++index)
	{
		cellNumber = 0;
		cellString = EMPTY_STRING;
		if(columnValues[index] == TAB)
		{
			cellStatus = empty;
		}
		else
		{	
			while(index < size && columnValues[index] != TAB)
			{
				cellString += columnValues[index];
				index++;
			}

			cellStatus = checkCellStatus(cellString);

			if(cellStatus == numeric)
			{
				cellNumber = std::atoi(cellString.c_str());
			}
		}

		spreadsheet[row][column].value.status = cellStatus;
		spreadsheet[row][column].value.numericValue = cellNumber;
		spreadsheet[row][column].value.stringValue = cellString;
		column++;
	}
}

// Name:		checkCellStatus
// Description:	Spreadsheeet class method which takes in the contents of a cell and determines its
//				status, i.e. whether it is empty, numeric, an equation, etc.
// Parameters:	Takes in the contents of a cell
// Return:		Returns a Status enum which is the status of the current cell
Spreadsheet::Status Spreadsheet::checkCellStatus(std::string inputString)
{
	int index = 0, size = inputString.size(), cellStatus = 0;

	if(index < size && inputString[index] == EQUAL)
	{
		cellStatus |= (int) equation;
	}
	if(index < size && (inputString[index] == MINUS || 
		(inputString[index] >= ZERO && inputString[index] <= NINE)))
	{
		cellStatus |= (int) numeric;
	}
	else if(inputString == NAN)
	{
		cellStatus |= (int) nan;
	}
	else if(inputString == ERROR)
	{
		cellStatus |= (int) error;
	}

	return (Status) cellStatus;
}

// Name:		buildCellMapping
// Description:	Spreadsheeet class method which iterates through the spreadsheet and hashes the cell
//				labels and maps them to pointers to those cells for constant time lookup 
// Parameters:	None
// Return:		Void
void Spreadsheet::buildCellMapping()
{
	int innerIndex, outerIndex;

	for(outerIndex = 0; outerIndex < rows; ++ outerIndex)
	{
		for(innerIndex = 0; innerIndex < columns; ++innerIndex)
		{
			cellMap[spreadsheet[outerIndex][innerIndex].name] = &spreadsheet[outerIndex][innerIndex];
		}
	}
}

// Name:		runCalculations
// Description:	Spreadsheeet class method which iterates through the spreadsheet and resolve the value
//				of each cell by jumping to other cells for their values if necessary and by evalutation
//				of equations if present
// Parameters:	None
// Return:		Void
void Spreadsheet::runCalculations()
{
	int equationResult, cellStatus, innerIndex, outerIndex, termIndex, termCount;
	bool nanEncountered, errorEncountered;
	std::string stringValue;
	std::vector<std::string> equationTerms;
	Value value;

	for(outerIndex = 0; outerIndex < rows; ++outerIndex)
	{
		for(innerIndex = 0; innerIndex < columns; ++innerIndex)
		{
			if(spreadsheet[outerIndex][innerIndex].value.status == equation)
			{
				equationTerms = processEquation(spreadsheet[outerIndex][innerIndex].value.stringValue);

				termCount = equationTerms.size();

				cellReferenceMap[spreadsheet[outerIndex][innerIndex].name]++;

				nanEncountered = false; 				
				errorEncountered = false; 
				for(termIndex = 0; termIndex < termCount; ++termIndex)
				{
					if(!isOperator(equationTerms[termIndex]))
					{

						value = jumpToCell(equationTerms[termIndex]);

						if(value.status == numeric)
						{
							equationTerms[termIndex] = std::to_string(value.numericValue);
						}
						else if(value.status == nan)
						{
							nanEncountered = true;
							equationResult = 0;
							stringValue = NAN;
							cellStatus = (int) nan;
							break;
						}
						else if(value.status == error)
						{
							errorEncountered = true;
							equationResult = 0;
							stringValue = ERROR;
							cellStatus = (int) error;
							break;
						}
					}
				}
				
				if(!nanEncountered && !errorEncountered)
				{
					value = evaluateEquation(equationTerms);
					equationResult = value.numericValue;
					stringValue = value.stringValue;
					cellStatus = (int) numeric;	
				}

				spreadsheet[outerIndex][innerIndex].value.numericValue = equationResult;
				spreadsheet[outerIndex][innerIndex].value.stringValue = stringValue;
				spreadsheet[outerIndex][innerIndex].value.status = cellStatus;
				
				cellReferenceMap.clear();
			}
		}
	}
}

// Name:		jumpToCell
// Description:	Spreadsheeet class method which recursively jumps from cells in the spreadsheet as it
//				encounters references to other cells; returns a Value struct containing numeric data as
//				the base case, or if a circular reference is detected by checking a map of cells visited
//				so far in the recursive call stack
// Parameters:	Takes in a string which is the label of the cell to jump to
// Return:		Returns a Value struct which contains information from the cell that was jumped to		
Value Spreadsheet::jumpToCell(std::string cellEquationTerm)
{
	Cell* cell;
	Value value;

	cell = cellMap[cellEquationTerm];

	if(cell != NULL)
	{
		cellReferenceMap[cell->name]++;

		if(cellReferenceMap[cell->name] > 1)
		{
			value.status = error;
			value.stringValue = ERROR;

			cell->value.status = value.status;
			cell->value.numericValue = value.numericValue;
			cell->value.stringValue = value.stringValue;

			cellReferenceMap[cell->name]--;

			return value;
		}

		if(cell->value.status == numeric)
		{
			value.status = numeric;
			value.numericValue = cell->value.numericValue;
			value.stringValue = std::to_string(cell->value.numericValue);
		}
		else if(cell->value.status == empty || cell->value.status == nan)
		{
			value.status = nan;
			value.stringValue = NAN;
		}
		else if(cell->value.status == error)
		{
			value.status = error;	
			value.stringValue = ERROR;
		}
		else if(cell->value.status == equation)
		{
			value = jumpToCell(cell->name);
			cell->value.status = value.status;
			cell->value.numericValue = value.numericValue;
			cell->value.stringValue = value.stringValue;
		}
		
		cellReferenceMap[cell->name]--;
	}

	return value;
}

// Name:		processEquation
// Description:	Spreadsheeet class method which takes in a string containing the equation at
//				the cell to be processed, strips off the equals sign, parses the terms and 
//				creates a vector containing each term
// Parameters:	Takes in the equation to be processed as a string
// Return:		Returns a vector of strings which contains the equation
std::vector<std::string> Spreadsheet::processEquation(std::string cellEquation)
{
	int index, size; 
	std::string equationTerm;
	std::string equationOperator;	
	std::vector<std::string> equationTerms;

	cellEquation.erase(0, 1);

	size = cellEquation.size();

	for(index = 0; index < size; ++index)
	{
		equationTerm = EMPTY_STRING;
		while(index < size && !isOperator(cellEquation[index]))
		{
			equationTerm += cellEquation[index];
			index++;
		}

		if(equationTerm != EMPTY_STRING)
		{
			equationTerms.push_back(equationTerm);
		}

		if(index < size)
		{
			equationOperator = EMPTY_STRING;
			equationOperator += cellEquation[index];
			equationTerms.push_back(equationOperator);
		}
	}

	return equationTerms;
}

// Name:		evaluateEquation
// Description:	Spreadsheeet class method which
// Parameters:	Takes in a vector of strings which holds the terms of the equation
// Return:		Returns a Value struct which holds the numeric value, along with status information,
//				which resulted from the evaluation of the equation
Value Spreadsheet::evaluateEquation(std::vector<std::string> equationTerms)
{
	int index, size, result;
	std::vector<Value> values;
	Value value;

	equationTerms = applyNegatives(equationTerms);
	values = convertToNumeric(equationTerms);

	size = values.size();

	if(size == 1 && values[0].status == numeric)
	{
		return values[0];
	}

	for(index = 1; index < size; ++index)
	{
		if(index + 1 < size && values[index].status == operatorSymbol && 
			values[index].stringValue[0] != PLUS && values[index].stringValue[0] != MINUS)
		{
			if(values[index].stringValue[0] == DIVIDE)
			{
				if(values[index + 1].numericValue == 0)
				{
					value.numericValue = 0;
					value.stringValue = NAN;
					value.status == nan;
					return value;
				}

				result = values[index - 1].numericValue / values[index + 1].numericValue;

			}
			else if(values[index].stringValue[0] == MULTIPLY)
			{
				result = values[index - 1].numericValue * values[index + 1].numericValue;
			}

			values[index - 1].numericValue = result;
			values[index - 1].stringValue = std::to_string(result);			
			values.erase(values.begin() + index, values.begin() + (index + 2));
			size = values.size();
			index--;
		}
	}

	for(index = 1; index < size; ++index)
	{
		if(index + 1 < size && values[index].status == operatorSymbol)
		{
			if(values[index].stringValue[0] == PLUS)
			{
				result = values[index - 1].numericValue + values[index + 1].numericValue;
			}
			else if(values[index].stringValue[0] == MINUS)
			{
				result = values[index - 1].numericValue - values[index + 1].numericValue;
			}

			values[index - 1].numericValue = result;
			values[index - 1].stringValue = std::to_string(result);			
			values.erase(values.begin() + index, values.begin() + (index + 2));
			size = values.size();
			index--;
		}
	}

	if(values.size() == 1)
	{
		return values[0];
	}
	else
	{
		value.status = error;
		value.numericValue = 0;
		value.stringValue = ERROR;

		return value;
	}
}

// Name:		applyNegatives
// Description:	Spreadsheeet class method which differentiates between minus operators and negative signs
//				by iterating through the equation and applying the negative sign to operands
// Parameters:	Takes in a vector of strings which holds the terms of the equation
// Return:		Returns a vector of strings which is the same as the input string vector
//				except negative signs have been applied to their operands
std::vector<std::string> Spreadsheet::applyNegatives(std::vector<std::string> equationTerms)
{
	int index, size = equationTerms.size();

	if(size > 1 && equationTerms[0].size() > 0 && equationTerms[0][0] == MINUS)
	{
		equationTerms[1] = MINUS + equationTerms[1];
		equationTerms.erase(equationTerms.begin());

		size = equationTerms.size();
	}

	for(index = 0; index < size - 2; ++index)
	{
		if(isOperator(equationTerms[index]) && equationTerms[index + 1].size() == 1 
			&& equationTerms[index + 1][0] == MINUS && index + 2 < size)
		{
			equationTerms[index + 2] = MINUS + equationTerms[index + 2];
			equationTerms.erase(equationTerms.begin() + (index + 1));
			size = equationTerms.size();
			index--;
		}
	}

	return equationTerms;
}

// Name:		convertToNumeric
// Description:	Spreadsheeet class method which iterates through the equation, as a vector of
//				strings, and converts it to a vector of Value structs, which contain numeric
//				values and status information
// Parameters:	Takes in a vector of strings which holds the terms of the equation
// Return:		Returns a vector of Value structs which hold the numeric values of the terms
//				in the equation
std::vector<Value> Spreadsheet::convertToNumeric(std::vector<std::string> equationTerms)
{
	int index, size = equationTerms.size(); 
	std::vector<Value> values;
	Value value;

	for(index = 0; index < size; ++index)
	{
		if(isOperator(equationTerms[index]))
		{
			value.status = operatorSymbol;
			value.numericValue = 0;
			value.stringValue = equationTerms[index];
		}
		else
		{
			value.status = numeric;
			value.numericValue = std::atoi(equationTerms[index].c_str());
			value.stringValue = equationTerms[index];
		}

		values.push_back(value);
	}

	return values;
}

// Name:		isOperator
// Description: Overloaded Spreadsheeet class method which determines whether or not a char is
//				an operator
// Parameters:	Takes in a char which is inspected to determine whether or not its an operator
// Return:		Returns a bool corresponding to whether or not the input char is an operator
bool Spreadsheet::isOperator(char operatorChar)
{
	if(operatorChar == PLUS || operatorChar == MINUS || operatorChar == MULTIPLY || operatorChar == DIVIDE)
	{
		return true;
	}
	
	return false;
}

// Name:		isOperator
// Description:	Overloaded Spreadsheeet class method which determines whether or not a string is
//				an operator
// Parameters:	Takes in a string which is inspected to determine whether or not its an operator
// Return:		Returns a bool corresponding to whether or not the input char is an operator
bool Spreadsheet::isOperator(std::string operatorString)
{
	if(operatorString.size() == 1 && (operatorString[0] == PLUS || operatorString[0] == MINUS || 
		operatorString[0] == MULTIPLY || operatorString[0] == DIVIDE))
	{
		return true;
	}
	
	return false;
}

// Name:		writeSpreadsheetToFile
// Description:	Spreadsheeet class method which iterates through the spreadsheet and outputs the results
//				of the calculations processed to a file
// Parameters:	None
// Return:		Void
void Spreadsheet::writeSpreadsheetToFile()
{
	int innerIndex, outerIndex;
	std::string newLine = "\n";
	std::ofstream outFile;
	outFile.open(outputFileName);

	if(carriageReturn)
	{
		newLine = CARRIAGE_RETURN + newLine;
	}

	for(outerIndex = 0; outerIndex < rows; ++outerIndex)
	{
		for(innerIndex = 0; innerIndex < columns; ++innerIndex)
		{
			if(spreadsheet[outerIndex][innerIndex].value.status != empty)
			{
				outFile << spreadsheet[outerIndex][innerIndex].value.stringValue;
			}
			if(innerIndex < columns - 1)
			{
				outFile << TAB;
			}
		}	
		outFile << newLine;
	}

	outFile.close();
}

// Name:		parseCommandLineArguments
// Description:	Spreadsheeet class method which iterates through the command line arguments
//				and extracts the input file name, the name of the file to output the spreadsheet to,
//				if present, as well as flags for debugging and verbose if they are present	
// Parameters:	Takes in the argument count and the arguments as strings in an array
// Return:		Void
void Spreadsheet::parseCommandLineArguments(int argc, char* argv[])
{
	int currentIndex = 1;
	std::ifstream inFile;

	if(argc > 1)
	{
		inputFileName = argv[currentIndex];

		inFile.open(inputFileName);

		if(inFile.is_open() && !inFile.fail())
		{
			runProgram = true;
			inFile.close();
		}
		else
		{
			std::cout << "Error: input file not found" << std::endl;
		}
		
		currentIndex++;
		if(argc > currentIndex && argv[currentIndex][0] != MINUS)
		{
			outputFileName = argv[currentIndex];
			currentIndex++;
		}
		else
		{
			outputFileName = "output.txt";
		}

		if(argc > currentIndex && (sizeof(argv[currentIndex]) / sizeof(char)) > 2 && argv[currentIndex][0] == MINUS && 
			((argv[currentIndex][1] == UPPERCASE_D) || (argv[currentIndex][1] == LOWERCASE_D)))
		{
			std::cout << "Debug mode" << std::endl;
			debug = true;
		}

		currentIndex++;
		if(argc > currentIndex && (sizeof(argv[currentIndex]) / sizeof(char)) > 2 && argv[currentIndex][0] == MINUS && 
			((argv[currentIndex][1] == UPPERCASE_V) || (argv[currentIndex][1] == LOWERCASE_V)))
		{
			std::cout << "Verbose debugging" << std::endl;

			verbose = true;
		}
	}
	else
	{
		std::cout << "Please enter the input file name as the first command line argument." << std::endl;
	}
}

// Name:		printSpreadsheet
// Description:	Spreadsheeet class method which	iterates through the spreadsheet and prints the contents
//				of each cell to the terminal for debugging purposes 
// Parameters:	None
// Return:		Void
void Spreadsheet::printSpreadsheet()
{
	int innerIndex, outerIndex;

	std::cout << "Rows: "<< rows << " Columns: " << columns << std::endl;

	for(outerIndex = 0; outerIndex < rows; ++outerIndex)
	{
		for(innerIndex = 0; innerIndex < columns; ++innerIndex)
		{
			printCell(spreadsheet[outerIndex][innerIndex]);
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

// Name:		printMapping
// Description:	Spreadsheeet class method which iterates through the cell mapping and prints the contents
//				of each cell to the terminal for debugging purposes
// Parameters:	None
// Return:		Void
void Spreadsheet::printMapping()
{
	std::map<std::string, Cell*>::iterator mapIterator;

	for(mapIterator = cellMap.begin(); mapIterator != cellMap.end(); ++mapIterator)
	{
		printCell(*(mapIterator->second));
	}
}

// Name:		printCell
// Description:	Spreadsheeet class method which takes in a Cell struct and prints its contents
//				to the terminal for debugging purposes
// Parameters:	Takes in a Cell struct which is the current cell to output to the terminal
// Return:		Void
void Spreadsheet::printCell(Cell cell)
{
	if(verbose)
	{
		std::cout << "status: " << cell.value.status << " row: " << cell.row;
		std::cout << " column: " << cell.column << " ";
	}

	std::cout << cell.name << ":" << cell.value.numericValue << ":" << cell.value.stringValue << "\t";   

	if(verbose)
	{
		std::cout << std::endl;
	}
}

#endif	