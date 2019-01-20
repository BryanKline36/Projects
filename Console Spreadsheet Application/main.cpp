
//File Name:	main.cpp
//Description:	Main driver for Console Spreadsheet Application
//Author:		Bryan Kline
//Date:			01/10/19

#include <iostream>
#include "Spreadsheet.h"

void printInstructions();

int main(int argc, char* argv[])
{
	printInstructions();

	Spreadsheet spreadsheet(argc, argv);

	spreadsheet.run();

	std::cout << "Exiting..." << std::endl;

	return 0;
}

void printInstructions()
{
	std::cout << std::endl;
	std::cout << "Console Spreadsheet Application" << std::endl;
	std::cout << "Author: Bryan Kline\t01/10/19" << std::endl << std::endl;
	std::cout << "Command line argument options:" << std::endl;
	std::cout << "Parameter 1: name of the input file" << std::endl;
	std::cout << "Parameter 2 (optional): name of the output file, if one is not provided then the output ";
	std::cout << "file takes the name \"_output.txt\"" << std::endl;
	std::cout << "Parameter 3 (optional): debugging flag, \"-D\" or \"-d\"" << std::endl;
	std::cout << "Parameter 4 (optional): verbose debugging flag, \"-V\" or \"-v\"" << std::endl << std::endl;
	std::cout << "Processing spreadsheet..." << std::endl;

}
