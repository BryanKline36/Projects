
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
	Selection choice = all;

	while(choice)
	{
		choice = promptAction();

		selectAction(choice);



	}

	createMap(fileName);
}

MapMaker::Selection MapMaker::promptAction()
{
	int choice;

	std::cout << "Choose an action:" << std::endl;
	std::cout << "1) Fill entire map" << std::endl;
	std::cout << "2) Fill borders" << std::endl;
	std::cout << "3) Fill line" << std::endl;
	std::cout << "0) To exit" << std::endl;


	std::cin >> choice;

	return (Selection) choice;

}

void MapMaker::selectAction(Selection choice)
{	
	Selection selectionType;
	Coordinate position;

	switch(choice)
	{

		case fillAll:

			fillEntire();

		break;

		case fillBorder:

			selectionType = chooseBorder();
			fillBorders(selectionType);

		break;

		case fillLine:

			selectionType = chooseLineType();
			position = choosePosition();
			fillLines(selectionType, position);

		break;

		default:

		break;	
	}
}

MapMaker::Selection MapMaker::chooseBorder()
{
	int choice;

	std::cout << "Choose a border to fill:" << std::endl;
	std::cout << "9) Fill all borders" << std::endl;
	std::cout << "10) Fill top border" << std::endl;
	std::cout << "6) Fill bottom border" << std::endl;
	std::cout << "7) Fill right border" << std::endl;
	std::cout << "8) Fill left border" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

MapMaker::Selection MapMaker::chooseLineType()
{
	int choice;

	std::cout << "Choose a type of line:" << std::endl;
	std::cout << "9) Vertical line" << std::endl;
	std::cout << "10) Horizontal line" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

MapMaker::Coordinate MapMaker::choosePosition()
{
	Coordinate coordinate;

	std::cout << "Enter the x position:" << std::endl;
	std::cin >> coordinate.x;
	std::cout << "Enter the y position:" << std::endl;
	std::cin >> coordinate.y;

	return coordinate;
}

void MapMaker::fillEntire()
{
	int inner, outer;
	char mapCharacter;

	std::cout << "Enter the character to fill:" << std::endl;
	std::cin >> mapCharacter; 

	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			map[outer][outer] = mapCharacter;
		}
	}
}

void MapMaker::fillBorders(Selection borderChoice)
{
	int outer, inner;
	char mapCharacter;

	if(borderChoice == null)
	{
		return;
	}

	std::cout << "Enter the character to fill:" << std::endl;
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
		else 
		{
			if(borderChoice == all || borderChoice == right)
			{
				map[outer][columns - 1] = mapCharacter;
			} 
			if(borderChoice == all || borderChoice == left)
			{
				map[outer][0] = mapCharacter;	
			} 
		}
	}
}

void MapMaker::fillLines(Selection lineType, int position)
{
	int choice;

	if(lineType == null)
	{
		return;
	}

	if(lineType == vertical)
	{
		std::cout << "Enter the column:" << std::endl;
		std::cin >> choice;
	}
	if(lineType == horizontal)
	{
		std::cout << "Enter the row:" << std::endl;
		std::cin >> choice;
	}



}

void MapMaker::fillLineSegment(Selection lineType, Coordinate position)
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