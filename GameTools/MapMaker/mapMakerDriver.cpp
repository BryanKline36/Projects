#include <iostream>
#include <fstream>
#include <string>
#include "MapMaker.h"


int main()
{
	MapMaker mapMaker;
	std::string fileName = "outFile.map";

	mapMaker.run();

	return 0;
}