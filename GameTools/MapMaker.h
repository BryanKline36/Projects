#include <iostream>
#include <fstream>
#include <string>

#ifndef MAP_MAKER_H
#define MAP_MAKER_H

class MapMaker
{
  public:

	enum Selection
	{
		all,
		top,
		right,
		left,
		bottom,
		vertical,
		horizontal

	};

    
    MapMaker();
    ~MapMaker();
  
  	void run(std::string fileName);

  private:

  	void fillAll();
  	void fillBorder(Selection borderChoice);
  	void fillLine(Selection lineType, int position);
    void createMap(std::string fileName);

    int rows;
    int columns;

    char** map;
};

#endif
