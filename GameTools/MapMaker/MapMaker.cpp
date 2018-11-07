
#include <iostream>
#include <fstream>
#include <string>
#include "MapMaker.h"

#ifndef MAP_MAKER_CPP
#define MAP_MAKER_CPP

//Name:			MapMaker
//Description:	MapMaker class constructor
//Parameters:	None
//Return:		None
MapMaker::MapMaker()
{
	int inner, outer;

	rows = MAX_ROWS;
	columns = MAX_COLUMNS;

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

//Name:			~MapMaker
//Description:	MapMaker class destructor
//Parameters:	None
//Return:		None
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

//Name:			run
//Description:	MapMaker class which continually prompts the user to fill the char map and take
//				action accordingly
//Parameters:	None
//Return:		Void
void MapMaker::run()
{
	Selection choice = all;

	std::cout << std::endl << "Char Map Making Utility" << std::endl;

	while(choice)
	{
		printMap();

		choice = promptAction();

		selectAction(choice);
	}
}

//Name:			promptAction
//Description:	MapMaker class which prompts the user to choose how to fill the char map and returns the
//				Selection enum which corresponds to the fill type
//Parameters:	None
//Return:		Returns a Selection enum which is 
MapMaker::Selection MapMaker::promptAction()
{
	int choice;

	std::cout << "Choose an action:" << std::endl;
	std::cout << fillAll << ") Fill entire map" << std::endl;
	std::cout << fillBorder << ") Fill borders" << std::endl;
	std::cout << fillLine << ") Fill line" << std::endl;
	std::cout << fillSegment << ") Fill line segment" << std::endl;
	std::cout << fillBlock << ") Fill block" << std::endl;
	std::cout << fillPoint << ") Fill point" << std::endl;
	std::cout << writeFile << ") Save map" << std::endl;
	std::cout << null << ") To exit" << std::endl;

	std::cin >> choice;

	return (Selection) choice;

}

//Name:			selectAction
//Description:	MapMaker class which takes in the fill option the user entered and selects that option
//Parameters:	Takes in a Selection enum which is the fill option the user entered
//Return:		Void
void MapMaker::selectAction(Selection choice)
{	
	std::string fileName;
	Selection selectionType;
	Coordinate firstCoordinate, secondCoordinate;

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
			firstCoordinate = choosePosition(false);
			fillLines(selectionType, firstCoordinate);

		break;

		case fillSegment:

			selectionType = chooseLineType();
			firstCoordinate = choosePosition(true);
			fillLineSegment(selectionType, firstCoordinate);

		break;

		case fillBlock:

			selectionType = chooseBlockType();
			std::cout << "Enter the first corner of the block:" << std::endl;
			firstCoordinate = choosePosition(true);
			std::cout << "Enter the opposite corner of the block:" << std::endl;
			secondCoordinate = choosePosition(true);
			fillBlocks(selectionType, firstCoordinate, secondCoordinate);

		break;

		case fillPoint:

			fillPoints();

		break;

		case writeFile:

  			fileName = enterFileName();
  			createMap(fileName);

		break;

		case null:

			std::cout << "Exiting program" << std::endl;

		break;

		default:

			std::cout << "Invalid input" << std::endl;
			std::cin.clear();
			std::cin.ignore();

		break;	
	}
}

//Name:			enterFileName
//Description:	MapMaker class which prompts the user to enter a file and returns it
//Parameters:	None
//Return:		Returns a string which is the name of the file 
std::string MapMaker::enterFileName()
{
	std::string fileName = " ";

	std::cout << "Enter the name of the file:" << std::endl;
	std::cin >> fileName;

	return fileName;
}

//Name:			chooseBorder
//Description:	MapMaker class which
//Parameters:	None
//Return:
MapMaker::Selection MapMaker::chooseBorder()
{
	int choice;

	std::cout << "Choose a border to fill:" << std::endl;
	std::cout << all << ") Fill all borders" << std::endl;
	std::cout << top << ") Fill top border" << std::endl;
	std::cout << bottom << ") Fill bottom border" << std::endl;
	std::cout << right << ") Fill right border" << std::endl;
	std::cout << left << ") Fill left border" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

//Name:			chooseLineType
//Description:	MapMaker class which
//Parameters:	None
//Return:
MapMaker::Selection MapMaker::chooseLineType()
{
	int choice;

	std::cout << "Choose a type of line:" << std::endl;
	std::cout << vertical << ") Vertical line" << std::endl;
	std::cout << horizontal << ") Horizontal line" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

//Name:			chooseBlockType
//Description:	MapMaker class which
//Parameters:	None
//Return:
MapMaker::Selection MapMaker::chooseBlockType()
{
	int choice;

	std::cout << "Choose a block type:" << std::endl;
	std::cout << outline << ") Block outline" << std::endl;
	std::cout << solid << ") Solid block" << std::endl;

	std::cin >> choice;

	return (Selection) choice;
}

//Name:			choosePosition
//Description:	MapMaker class which
//Parameters:
//Return:
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

//Name:			fillEntire
//Description:	MapMaker class which
//Parameters:	None
//Return:		Void
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

//Name:			fillBorders
//Description:	MapMaker class which fills the borders of the char map with a char input by the user
//Parameters:	Takes in the border to fill, whether the top, bottom, left, or right border, or all of them
//Return:		Void
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

//Name:			fillLines
//Description:	MapMaker class which fills a line in the char map with a char input by the user
//Parameters:	Takes in a the type of line which is be filled, horizontal or vertical, and the position
//				of the line
//Return:		Void
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

//Name:			fillLineSegment
//Description:	MapMaker class which
//Parameters:
//Return:		Void
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

//Name:			fillBlocks
//Description:	MapMaker class which
//Parameters:
//Return:		Void
void MapMaker::fillBlocks(Selection lineType, Coordinate firstCoordinate, Coordinate secondCoordinate)
{
	int inner, outer;
	char mapCharacter;

	if(lineType == null)
	{
		return;
	}

	std::cout << "Enter the character to fill:" << std::endl;
	std::cin >> mapCharacter; 

	for(outer = firstCoordinate.y; outer <= secondCoordinate.y; outer++)
	{
		for(inner = firstCoordinate.x; inner <= secondCoordinate.x; inner++)
		{
			if(outer >= 0 && outer < rows && inner >= 0 && inner < columns)
			{
				if(outer == firstCoordinate.y || outer == secondCoordinate.y || 
					inner == firstCoordinate.x || inner == secondCoordinate.x || lineType == solid)
				{
					map[outer][inner] = mapCharacter;
				}
			}	
		}
	}
}

//Name:			fillPoints
//Description:	MapMaker class which
//Parameters:	None
//Return:		Void
void MapMaker::fillPoints()
{
	char mapCharacter;
	Coordinate coordinate;

	std::cout << "Enter the character to fill:" << std::endl;
	std::cin >> mapCharacter; 

	coordinate = choosePosition(true);

	if(coordinate.y >= 0 && coordinate.y < rows && coordinate.x >= 0 && coordinate.x < columns)
	{
		map[coordinate.y][coordinate.x] = mapCharacter;
	}
}


//Name:			printMap
//Description:	MapMaker class which prints the current char map to the screen
//Parameters:	None
//Return:		Void
void MapMaker::printMap()
{
	int inner, outer;

	std::cout << std::endl << "   ";	
	for(inner = 0; inner < columns; inner++)
	{
		if(inner < 10)
		{
			std::cout << "0";
		}
		std::cout << inner << " "; 		
	}	
	std::cout << std::endl;	

	for(outer = 0; outer < rows; outer++)
	{
		if(outer < 10)
		{
			std::cout << "0";
		}
		std::cout << outer << " ";

		for(inner = 0; inner < columns; inner++)
		{
			std::cout << map[outer][inner] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;	
}

//Name:			createMap
//Description:	MapMaker class which writes the char map out to a file
//Parameters:	Takes in a string which is the name of the file to write the char map to
//Return:		Void
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