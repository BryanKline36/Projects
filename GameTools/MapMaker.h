#include <iostream>
#include <fstream>
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
    void createMap(string fileName);

    int rows = 8;
    int columns = 8;

    char map[rows][columns];
};

MapMaker::MapMaker()
{
	int inner, outer;

	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			map[outer][outer] = " ";
		}
	}
}

MapMaker::~MapMaker() {} = default;

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

void MapMaker::createMap(string fileName)
{
	int inner, outer;
	ofstream outFile;

	outFile.open(fileName);

	for(outer = 0; outer < rows; outer++)
	{
		for(inner = 0; inner < columns; inner++)
		{
			outFile >> map[outer][outer];
		}
		outFile >> '\n';
	}
}