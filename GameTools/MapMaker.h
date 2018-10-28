#include <iostream>
#include <fstream>
#include <string>

#ifndef MAP_MAKER_H
#define MAP_MAKER_H

class MapMaker
{
  public:

  	const int minFillSelection = 7;
  	const int maxFillSelection = 9;


	enum Selection
	{
		all,
		top,
		bottom,
		right,
		left,
		vertical,
		horizontal,
		fillAll,
		fillBorder,
		fillLine

	};

    
    MapMaker();
    ~MapMaker();
  
  	void run(std::string fileName);

  private:

  	Selection promptAction();
  	void selectAction(Selection choice);
  	Selection chooseBorder();

  	void fillAll();
  	void fillBorder(Selection borderChoice);
  	void fillLine(Selection lineType, int position);

    void createMap(std::string fileName);

    int rows;
    int columns;
    char currentSymbol;

    char** map;
};

#endif
