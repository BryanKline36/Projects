
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
	createMap(fileName);
}


void MapMaker::fillAll()
{


}

void MapMaker::fillBorder(Selection borderChoice)
{


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