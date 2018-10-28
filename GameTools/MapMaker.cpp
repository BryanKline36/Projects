
#include <iostream>
#include <fstream>
#include <string>
#include "MapMaker.h"

#ifndef MAP_MAKER_CPP
#define MAP_MAKER_CPP

MapMaker::MapMaker()
{
	int inner, outer;

	rows = 8;
	columns = 8;
	currentSymbol = ' ';

	map = new char*[rows];

	for(outer = 0; outer < rows; outer++)
	{
		map[outer] = new char[columns];
	}

	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			map[outer][outer] = '.';
		}
	}
}

MapMaker::~MapMaker() 
{
	int index;

	if(map != NULL)
	{	
		for(index = 0; index < rows; index++)
		{
			delete [] map[index];
		}

		delete [] map;
	}	
} 

void MapMaker::run(std::string fileName)
{
	Selection choice = 1;

	while(choice)
	{
		choice = promptAction();

		selectAction(choice);



	}

	createMap(fileName);
}

Selection MapMaker::promptAction()
{
	int choice;

	std::cout << "Choose an action:" << std::endl;
	std::cout << "1) Fill entire map" << std::endl;
	std::cout << "2) Fill borders" << std::endl;
	std::cout << "3) Fill line" << std::endl;

	std::cin >> choice;

	return choice;

}

void MapMaker::selectAction(Selection choice)
{	
	int position;
	Selection selectionType;

	switch(choice)
	{

		case fillAll:

			fillAll();

		break;

		case fillBorder:

			selectionType = chooseBorder();
			fillBorder(selectionType);

		break;

		case fillLine:

			fillLine();

		break;

		default:

		break;	
	}
}

Selection MapMaker::chooseBorder()
{
	Selection choice;

	std::cout << "Choose a border to fill:" << std::endl;
	std::cout << "1) Fill all borders" << std::endl;
	std::cout << "2) Fill top border" << std::endl;
	std::cout << "3) Fill bottom border" << std::endl;
	std::cout << "4) Fill right border" << std::endl;
	std::cout << "5) Fill left border" << std::endl;

	std::cin >> choice;

	return choice;
}


void MapMaker::fillAll()
{


}

void MapMaker::fillBorder(Selection borderChoice)
{
	int outer, inner;
	char mapCharacter;

	std::out << "Enter the character to fill:" << std::endl;
	std::cin >> mapCharacter; 

	for(outer = 0; outer < rows; outer++)
	{
		if(((borderChoice == all || borderChoice == top) && outer == 0) || 
			((borderChoice == all || borderChoice == bottom)) && outer == rows - 1)
		{
			for(inner = 0; inner < columns; outer++)
			{
				map[outer][inner] = mapCharacter;
			}
		}	
		
	}

}

void MapMaker::fillLine(Selection lineType, int position)
{


}

void MapMaker::createMap(std::string fileName)
{
	int inner, outer;
	std::ofstream outFile;

	outFile.open(fileName);

	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			outFile << map[outer][outer];
		}
		outFile << '\n';
	}
}

#endif