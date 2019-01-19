all: ConsoleSpreadsheet

ConsoleSpreadsheet: main.cpp Spreadsheet.o
	g++-7 main.cpp Spreadsheet.o -o ConsoleSpreadsheet

Spreadsheet.o: Spreadsheet.cpp
	g++-7 -c Spreadsheet.cpp

clean:
	rm -f *.o Spreadsheet
