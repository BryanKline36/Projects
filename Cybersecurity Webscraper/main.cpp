
// File name: 	main.cpp
// Author: 		Nathanael Fuller
// Author: 		Bryan Kline
// Class:		CS445
// Date:		May 3, 2018
// Description:	Main driver implementation file (C++)

#include <iostream>
#include "Dictionary.h"

using namespace std;

int main()
{
    // Dictionary object is created and its run method is called which opens the file
    // containing the contents of the database, moves through all non-dictionary terms 
    // in the database, assigns scores to and thresholds each one to determine if it
    // is a relevant term and should therefore be added to the dictionary
	Dictionary dictionary(false);
	dictionary.run();

    return 0;
}
