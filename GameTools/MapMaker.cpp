
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

	map = new char*[rows];

	for(outer = 0; outer < rows; outer++)
	{
		map[outer] = new char[columns];
	}

	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			map[outer][inner] = ' ';
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

	std::cout << "Char Map Making Utility" << std::endl;

	while(choice)
	{
		choice = promptAction();

		selectAction(choice);

		printMap();
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
	std::cout << "4) Fill line segment" << std::endl;
	std::cout << "0) To exit" << std::endl;


	std::cin >> choice;

	return (Selection) choice;

}

void MapMaker::selectAction(Selection choice)
{	
	Selection selectionType;
	Coordinate coordinate;

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
			coordinate = choosePosition(false);
			fillLines(selectionType, coordinate);

		break;

		case fillSegment:

			selectionType = chooseLineType();
			coordinate = choosePosition(true);
			fillLineSegment(selectionType, coordinate);

		break;

		default:

		break;	
	}
}

MapMaker::Selection MapMaker::chooseBorder()
{
	int choice;

	std::cout << "Choose a border to fill:" << std::endl;
	std::cout << "5) Fill all borders" << std::endl;
	std::cout << "6) Fill top border" << std::endl;
	std::cout << "7) Fill bottom border" << std::endl;
	std::cout << "8) Fill right border" << std::endl;
	std::cout << "9) Fill left border" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

MapMaker::Selection MapMaker::chooseLineType()
{
	int choice;

	std::cout << "Choose a type of line:" << std::endl;
	std::cout << "10) Vertical line" << std::endl;
	std::cout << "11) Horizontal line" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

MapMaker::Coordinate MapMaker::choosePosition(bool isCoordinate)
{
	Coordinate coordinate;

	if(isCoordinate)
	{
		std::cout << "Enter the x position:" << std::endl;
		std::cin >> coordinate.x;
		std::cout << "Enter the y position:" << std::endl;
		std::cin >> coordinate.y;
	}
	else
	{
		std::cout << "Enter the position:" << std::endl;
		std::cin >> coordinate.x;
		coordinate.y = -1;
	}

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
			map[outer][inner] = mapCharacter;
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
			for(inner = 0; inner < columns; inner++)
			{
				map[outer][inner] = mapCharacter;
			}
		}	

		if(borderChoice == all || borderChoice == right)
		{
			std::cout << outer << " : " << columns - 1 << std::endl;
			map[outer][columns - 1] = mapCharacter;
		} 
		if(borderChoice == all || borderChoice == left)
		{
			map[outer][0] = mapCharacter;	
		} 
		
	}
}

void MapMaker::fillLines(Selection lineType, Coordinate coordinate)
{
	int index, lineEnd, position = coordinate.x;
	char mapCharacter;

	if(lineType == null || coordinate.y != -1 || position < 0)
	{
		return;
	}

	std::cout << "Enter the character to fill:" << std::endl;
	std::cin >> mapCharacter; 

	if(lineType == vertical)
	{
		lineEnd = rows;
	}
	if(lineType == horizontal)
	{
		lineEnd = columns;
	}	

	for(index = 0; index < lineEnd; index++)
	{
		if(lineType == vertical && position < columns)
		{
			map[index][position] = mapCharacter;
		}
		if(lineType == horizontal && position < rows)
		{

			map[position][index] = mapCharacter;
		}
	}	
}


void MapMaker::fillLineSegment(Selection lineType, Coordinate coordinate)
{
	int index, lineSize;
	char mapCharacter;

	if(lineType == null || coordinate.x < 0 || coordinate.x > rows || coordinate.y < 0 || coordinate.y > columns)
	{
		return;
	}

	std::cout << "Enter the character to fill:" << std::endl;
	std::cin >> mapCharacter; 

	std::cout << "Enter the size of the line segment:" << std::endl;
	std::cin >> lineSize; 
	
	for(index = 0; index < lineSize; index++)
	{
		if(lineType == vertical && (coordinate.y + index) < rows)
		{
			map[coordinate.y + index][coordinate.x] = mapCharacter;
		}
		if(lineType == horizontal && (coordinate.x + index) < columns)
		{
			map[coordinate.y][coordinate.x + index] = mapCharacter;
		}
	}	

}

void MapMaker::printMap()
{
	int inner, outer;

	std::cout << std::endl;	
	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			std::cout << map[outer][inner] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	
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
			outFile << map[outer][inner] << " ";
		}
		outFile << '\n';
	}
}

#endif