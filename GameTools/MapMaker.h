#include <iostream>
#include <string>


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

	}

    
    MapMaker();
    ~MapMaker();
  
  	void run();

  private:

  	void fillAll();
  	void fillBorder(Selection borderChoice);
  	void fillLine(Selection lineType, int position);
    void createMap();
};

MapMaker::MapMaker()
{

}

MapMaker::~MapMaker()
{

}

void MapMaker::run()
{

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

void MapMaker::createMap()
{


}