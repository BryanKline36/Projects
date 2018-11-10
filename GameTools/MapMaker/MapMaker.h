
//Name:         mapMakerDriver.h
//Date:         November 9, 2018
//Author:       Bryan Kline
//Description:  MapMaker class header file

#include <iostream>
#include <fstream>
#include <string>

#ifndef MAP_MAKER_H
#define MAP_MAKER_H

class MapMaker
{
  public:

  	const int MAX_ROWS = 16;
  	const int MAX_COLUMNS = 16;

  	struct Coordinate
  	{
  		int x;
  		int y;
  	};

	enum Selection
	{
		null,
		fillAll,
		fillBorder,
		fillLine,
		fillSegment,
		fillBlock,
		fillPoint,
		writeFile,
		all,
		top,
		bottom,
		right,
		left,
		vertical,
		horizontal,
		outline,
		solid
	};

    MapMaker();
    ~MapMaker();
  
  	void run();

  private:

  	Selection promptAction();
  	void selectAction(Selection choice);
  	std::string enterFileName();
  	Selection chooseBorder();
  	Selection chooseLineType();
	Selection chooseBlockType();
  	Coordinate choosePosition(bool isCoordinate);

  	void fillEntire();
  	void fillBorders(Selection borderChoice);
  	void fillLines(Selection lineType, Coordinate coordinate);
  	void fillLineSegment(Selection lineType, Coordinate coordinate);
  	void fillBlocks(Selection lineType, Coordinate firstCoordinate, Coordinate secondCoordinate);
  	void fillPoints();

  	void printMap();
    void createMap(std::string fileName);

    int rows;
    int columns;

    char** map;
};

#endif
