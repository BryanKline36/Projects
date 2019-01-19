File Name: 		README.txt
Author:			Bryan Kline
Date:			01/10/19

The Console Spreadsheet Application program was intended to be compiled and run in Linux and it assumes g++-7

As the project contains a makefile, the application can be built with the following command in the terminal:

	make

After building the executable, the program can be executed with the following command (assuming an input file to process named "inputFile.txt"):

	./ConsoleSpreadsheet inputFile.txt

If g++-7 is not installed on the local machine, the makefile can be edited to either replace "7" with a different version, or "-7" can be removed to use g++.

Alternately, each binary can be built separately with the following commands in terminal, in the specified order:

	g++-7 -c Spreadsheet.cpp
	g++-7 main.cpp Spreadsheet.o -o ConsoleSpreadsheet

Again, the version can be changed (replacing or removing the "7") and other compiler flags can be added as desired.	
