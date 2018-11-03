#include <iostream>
#include <fstream>
#include <string>

#ifndef MAP_MAKER_H
#define MAP_MAKER_H

class MapMaker
{
  public:

  	const int mapDimension = 8;
  	const int minFillSelection = 7;
  	const int maxFillSelection = 9;

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
		all,
		top,
		bottom,
		right,
		left,
		vertical,
		horizontal

	};

    
    MapMaker();
    ~MapMaker();
  
  	void run(std::string fileName);

  private:

  	Selection promptAction();
  	void selectAction(Selection choice);
  	Selection chooseBorder();
  	Selection chooseLineType();
  	Coordinate choosePosition();

  	void fillEntire();
  	void fillBorders(Selection borderChoice);
  	void fillLines(Selection lineType, int position);
  	void fillLineSegment(Selection lineType, Coordinate position);

    void createMap(std::string fileName);

    int rows;
    int columns;
    char currentSymbol;

    char** map;
};

#endif
