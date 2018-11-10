
//Name:			mapMakerDriver.cpp
//Date:			November 9, 2018
//Author:		Bryan Kline
//Description:	Main driver for map maker project which simply instantiates a MapMaker object and calls
//				its run method

#include <iostream>
#include <fstream>
#include <string>
#include "MapMaker.h"

int main()
{
	MapMaker mapMaker;

	mapMaker.run();

	return 0;
}