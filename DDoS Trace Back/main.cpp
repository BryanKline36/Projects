//
// Bryan Kline
// CS445
// HW#1
// main.cpp
// The main driver of the program
//

#include <iostream>
#include <fstream>
#include "NetworkTopology.h"
#include "Router.h"

using namespace std;

int main(int argc, char* argv[])
{
	int packetCount;
	string input;
	string fileName = "output.txt";
	ofstream outFile;

	if(argc > 1)
	{
		fileName = argv[1];
	}	

	outFile.open(fileName.c_str());

	cout << "Enter the name of the victim: ";
	cin >> input;

	cout << "Enter the baseline number of packets per host: ";
	cin >> packetCount;

	NetworkTopology network(input, packetCount);
	network.buildTopology();
	network.runAttack();
	network.nodeSamplingResults();
	network.edgeSamplingResults();
	network.printNodeResults(outFile, true);
	network.printEdgeResults(outFile, true);

	outFile.close();
	
	cout << "Print out topology? (y/n): ";
	cin >> input;

	if(input == "y" || input == "Y")
	{
		cout << endl;
		network.printNetwork();
	}	

	cout << "Print out packets? (y/n): ";
	cin >> input;

	if(input == "y" || input == "Y")
	{
		cout << endl;
		network.printPackets();
	}	

	cout << "Print out Nodes? (y/n): ";
	cin >> input;

	if(input == "y" || input == "Y")
	{
		cout << endl;
		network.printNodes();
	}	

	cout << "Print out Edges? (y/n): ";
	cin >> input;

	if(input == "y" || input == "Y")
	{
		cout << endl;
		network.printEdges();
	}

	cout << endl;
	
	return 0;
}
