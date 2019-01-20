//
// Bryan Kline
// CS445
// HW#1
// NetworkTopology.cpp
// NetworkTopology implementation file
//

#ifndef NETWORKTOPOLOGY_CPP
#define NETWORKTOPOLOGY_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include "NetworkTopology.h"
#include "Router.h"

using namespace std;

bool sortNodePackets(const NodePacket& firstPacket, const NodePacket& secondPacket);
bool sortEdgePackets(const EdgePacket& firstPacket, const EdgePacket& secondPacket);
bool sortNodes(const Node& firstNode, const Node& secondNode);
bool sortEdges(const Edge& firstNode, const Edge& secondNode);

//Name:			NetworkTopology
//Description:	NetworkTopology class parameterized constructor
//Parameters:	Takes in a string corresponding to the name of the Router at the root of the
//				attack, i.e. the victim, an int corresponding to the maximum number of Routers
//				in the topology, and an int corresponding to the baseline number of packets
//				for each host	
//Return:		None
NetworkTopology:: NetworkTopology(string rootName, int packetCountValue)
{
	srand(time(NULL));

	probability[0] = 0.2;
	probability[1] = 0.4;
	probability[2] = 0.5;
	probability[3] = 0.6;
	probability[4] = 0.8;

	attackMultiplier[0] = 10;
	attackMultiplier[1] = 100;
	attackMultiplier[2] = 1000;

	routerCount = 0;
	nodeCount = 0;
	packetCount = packetCountValue;
	attackerCount = 0;

	root = new Router(rootName, true);
	routers.push_back(root);
	routerCount++;
}

//Name:			~NetworkTopology
//Description:	NetworkTopology class destructor
//Parameters:	None
//Return:		None
NetworkTopology:: ~NetworkTopology()
{
	int index;

	for(index = 0; index < routerCount; index++)
	{
		if(routers[index] != NULL)
		{
			delete routers[index];
			routers[index] = NULL;
		}	
	}	

	routers.clear();
	nodePackets.clear();
	nodeCounts.clear();
	nodeResults.clear();
}
	
//Name:			buildTopology
//Description:	NetworkTopology class method which continually reads input from the standard input
//				and uses that to build the topology of the network by adding Routers and host
//				devices and connects them, finally it calls the class method defineHosts which
//				allows for input from the standard input to indicate which hosts are normal and 
//				which are attackers
//Parameters:	None
//Return:		Void
void NetworkTopology:: buildTopology()
{
	string input = " ";
	Router* router;

	cout << "Enter a router or host followed by a list of other routers or hosts which are connected" << endl;
	cout << "to it.  Enter 'END' to quit." << endl;

	while(input != "END")
	{
		cout << "Enter an existing router: ";
		cin >> input;

		router = getRouter(input);

		if(router != NULL)
		{	
			cout << "Enter a comma separated list of other routers or hosts to which that router" << endl;
			cout << "is connected in parentheses in the following format: ( Ri, Rj, Rk )" << endl;
			cin >> input;

			while(input != ")")
			{	
				if(input != "(")
				{	
					input = formatInput(input);
					addRouter(router, input);	
				}

				cin >> input;	
			}
		}
		else
		{
			if(input != "END")
			{	
				cout << "That router does not exist." << endl;
			}
		}	
	}

	defineHosts();	
}

//Name:			runAttack
//Description:	NetworkTopology class method which iteratres through the all possible attack multipliers 
//				and marking probabilities, each being a separate attack scenario, and the moving through
//				each host, whether normal or attacker, and then causing packets to be sent from each one
//				for as many as specified as the baseline packet number per host, in the case of an attacker
//				this is multiplied by the attack mulitplier, both Node sampling and Edge sampling attacks
//				taking place simultaneously, and the packets sent through the system for every attack
//				are saved in vectors of NodePackets and EdgePackets
//Parameters:	None
//Return:		Void
void NetworkTopology:: runAttack()
{
	int probabilityIndex, multiplierIndex, routerIndex, packetCountIndex, packetNumber, count, size;
	float randomValue;
	string tempString;
	NodePacket* nodePacket = new NodePacket[1];
	EdgePacket* edgePacket = new EdgePacket[1];
	Node* node = new Node[1];
	Edge* edge = new Edge[1];
	vector<Node> tempNodeVector;
	vector<Edge> tempEdgeVector;

	for(probabilityIndex = 0; probabilityIndex < MAX_PROBABILITY; probabilityIndex++)
	{
		for(multiplierIndex = 0; multiplierIndex < MAX_MULTIPLIER; multiplierIndex++)
		{
			for(routerIndex = 0; routerIndex < routerCount; routerIndex++)
			{
				if(routers[routerIndex]->leaf)
				{
					packetNumber = packetCount;

					if(routers[routerIndex]->attacker)
					{
						packetNumber *= attackMultiplier[multiplierIndex];
					}	

					for(packetCountIndex = 0; packetCountIndex < packetNumber; packetCountIndex++)
					{	
						nodePacket->mark = " ";
						nodePacket->multiplier = attackMultiplier[multiplierIndex];
						nodePacket->probability = probability[probabilityIndex];

						edgePacket->firstMark = " ";
						edgePacket->secondMark = " ";
						edgePacket->distance = -1;
						edgePacket->multiplier = attackMultiplier[multiplierIndex];
						edgePacket->probability = probability[probabilityIndex];

						sendPacket(routers[routerIndex]->links[0].toRoot, nodePacket, edgePacket, probability[probabilityIndex]);
						
						if(nodePacket->mark != " ")
						{	
							nodePackets.push_back(*nodePacket);

							size = tempNodeVector.size();	
							for(count = 0; count < size; count++)
							{
								if(nodePacket->mark == tempNodeVector[count].routerName)
								{	
									tempNodeVector[count].count++;
									break;
								}
							}

							if(count == size)
							{
								node->routerName = nodePacket->mark;		
								node->count = 1;
								tempNodeVector.push_back(*node);
							}	
						}

						if(edgePacket->distance >= 0)
						{
							if(edgePacket->secondMark == " ")
							{
								edgePacket->secondMark =  root->address;
							}	
							edgePackets.push_back(*edgePacket); 

							size = tempEdgeVector.size();	
							for(count = 0; count < size; count++)
							{
								if(edgePacket->firstMark == tempEdgeVector[count].farEnd && edgePacket->secondMark == tempEdgeVector[count].closeEnd)
								{	
									tempEdgeVector[count].count++;
									break;
								}
							}

							if(count == size)
							{
								edge->farEnd = edgePacket->firstMark;
								edge->closeEnd = edgePacket->secondMark;		
								edge->distance = edgePacket->distance;
								edge->farRouter = getRouter(edgePacket->firstMark);
								edge->closeRouter = getRouter(edgePacket->secondMark);
								edge->count = 1;
								tempEdgeVector.push_back(*edge);
							}	
						}	
					}
				}	
			}

			nodeCounts.push_back(tempNodeVector);
			tempNodeVector.clear();
			edgeCounts.push_back(tempEdgeVector);
			tempEdgeVector.clear();
		}
	}
	//delete nodePacket;	
	//delete node;
	//delete edgePacket;	
	//delete edge;
}

//Name:			nodeSamplingResults
//Description:	NetworkTopology class method which moves through the vector of vectors of Nodes
//				which holds all the attack paths from the Node sampling attack and moves from
//				one Router to another, calling reconstructNodePath to ensure there is a contiguous
//				path in the topology from one to the next to verify that the path is valid and 
//				a vector of NodeSamplingResult structs is created to hold the results of each attack
//Parameters:	None
//Return:		Void
void NetworkTopology:: nodeSamplingResults()
{
	int index, innerIndex, size, attackRouterCount;
	float numerator, denominator;
	bool correctResult;
	Router *tempRouter;
	Node* tempNode = new Node[1];
	NodeSamplingResult* tempResult = new NodeSamplingResult[1];

	for(index = 0; index < (MAX_PROBABILITY * MAX_MULTIPLIER); index++)
	{
		sort(nodeCounts[index].begin(), nodeCounts[index].end(), sortNodes);

		size = nodeCounts[index].size();
		for(innerIndex = 0; innerIndex < size; innerIndex++)
		{
			if(innerIndex > 0)
			{
				numerator = nodeCounts[index][innerIndex].count;
				denominator = nodeCounts[index][innerIndex - 1].count;
			}
			if(innerIndex == 0 || (numerator / denominator) >= 0.1)
			{
				tempNode->count = nodeCounts[index][innerIndex].count;
				tempNode->routerName = nodeCounts[index][innerIndex].routerName;	

				tempResult->finalPath.push_back(*tempNode);
			}	
			else
			{
				break;
			}
		}	

		tempResult->baselinePackets = packetCount;
		tempResult->attackMultiplier = attackMultiplier[index % 3];
		tempResult->probability = probability[index / 3];
		tempResult->accurate = reconstructNodePath(tempResult->finalPath);

		nodeResults.push_back(*tempResult);
		tempResult->finalPath.clear();
	}

	//delete tempResult;
	//delete tempNode;
}

//Name:			edgeSamplingResults
//Description:	NetworkTopology class method which moves through the results from the Edge sampling
//				attack and determines if each one produced an accurate result or not by calling
//				the countEdgeAttackers method to get a count of the attackers in the system and 
//				comparing it to the actual number of attackers
//Parameters:	None
//Return:		Void
void NetworkTopology:: edgeSamplingResults()
{
	int index, attackerNumber = 0;

	for (index = 0; index < (MAX_MULTIPLIER * MAX_PROBABILITY); index++)
	{
		sort(edgeCounts[index].begin(), edgeCounts[index].end(), sortEdges);
		buildEdgeTree(index);

		edgeResults[index].baselinePackets = packetCount;
		edgeResults[index].attackMultiplier = attackMultiplier[index % 3];
		edgeResults[index].probability = probability[index / 3];
		edgeResults[index].accurate = false;

		attackerNumber = countEdgeAttackers(edgeResults[index].root);

		if(attackerNumber == attackerCount)
		{
			edgeResults[index].accurate = true;
		}
	}
}
	
//Name:			countEdgeAttackers
//Description:	NetworkTopology class method which takes in an Edge reference and recursively
//				moves through the tree of Edges which was constructed from the packets received
//				in the attack and counts up the number of attackers in the system
//Parameters:	Takes in an Edge pointer 
//Return:		Returns an int corresponding to the number of attackers in the topology			
int NetworkTopology:: countEdgeAttackers(Edge* edgeReference)
{
	int index, size = edgeReference->children.size(), attackers = 0;

	if(!edgeReference->farRouter->leaf && edgeReference->farRouter->attacker)
	{
		attackers++;
	}	

	for(index = 0; index < size; index++)
	{
		attackers += countEdgeAttackers(edgeReference->children[index]);
	}	

	return attackers;
}

//Name:			buildEdgeTree
//Description:	NetworkTopology class method which moves through a vector of Edges and 
//				constructs a tree from the Edges found in the attack, and the adds that to
//				a EdgeSamplingResult struct and then adds that to a vector which holds the
//				result and tree for that particular attack
//Parameters:	Takes in an int corresponding to the index in the vector of vectors of Edge
//				which holds the results from all the attack runs
//Return:		Void
void NetworkTopology:: buildEdgeTree(int index)
{
	int outerIndex, innerIndex, size = edgeCounts[index].size();
	EdgeSamplingResult* temp = new EdgeSamplingResult[1];

	for(outerIndex = 0; outerIndex < size; outerIndex++)
	{
		if(outerIndex == 0 && edgeCounts[index][outerIndex].distance == 0)
		{
			temp->root = &edgeCounts[index][outerIndex];
		}	

		for(innerIndex = 0; innerIndex < size; innerIndex++)
		{
			if(edgeCounts[index][outerIndex].farRouter == edgeCounts[index][innerIndex].closeRouter)
			{
				edgeCounts[index][outerIndex].children.push_back(&edgeCounts[index][innerIndex]);
			}	
		}	
	}	

	edgeResults.push_back(*temp);
}

//Name:			reconstructNodePath
//Description:	NetworkTopology class method which takes in a vector of Nodes which is the
//				putative attack path, the path is iterated through and each Node is compared to
//				to the next to ensure that there is a contiguous path from start to end, if
//				so true is returned, otherwise false is returned
//Parameters:	Takes in a vector of Nodes corresponding to the path which was found from the
//				to root the attacking Router
//Return:		Returns a bool corresponding to whether or not the path is contiguous
bool NetworkTopology:: reconstructNodePath(vector<Node> path)
{
	int index, counter = 0, linkSize, size = path.size();
	Router* temp;

	for(index = 0; index < size - 1; index++)
	{
		temp = getRouter(path[index].routerName);

		if(temp == NULL)
		{
			return false;
		}	

		linkSize = temp->linkCount;
		counter = 0;
		while(counter < linkSize && temp->links[counter].toLeaf->address != path[index + 1].routerName)
		{
			counter++;
		}

		if(counter == temp->linkCount)
		{
			return false;
		}
	}	

	temp = getRouter(path[index].routerName);
	if(temp != NULL && (temp->leaf || !temp->attacker))//counter < linkSize && !temp->links[counter].toLeaf->attacker)
	{
		return false;
	}	

	return true;
}

//Name:			sendPacket
//Description:	NetworkTopology class method which sends both NodePackets and EdgePackets through the 
//				system by moving through all Routers in the path from the leaf to the root, calling
//				the current Router's method markNodePacket on both packets to determine whether or not
//				they should be marked 
//Parameters:	Takes in a Router pointer corresponding to where a packet begins, a NodePacket pointer
//				and and EdgePacket pointer, both different types of packets, one for sampling Nodes
//				and the other for sampling Edges, and a float corresponding to the probability that the
//				packets will be marked at a given Router
//Return:		Void
void NetworkTopology:: sendPacket(Router* router, NodePacket* nodePacket, EdgePacket* edgePacket, float probability)
{
	int linkCountIndex, randomValue;

	while(!router->root)
	{
		for(linkCountIndex = 0; linkCountIndex < router->linkCount; linkCountIndex++)
		{
			if(router != NULL && router->links[linkCountIndex].towardsRoot)
			{
				randomValue = rand() % 1000;
				router->markNodePacket(nodePacket, probability, randomValue);

				randomValue = rand() % 1000;
				router->markEdgePacket(edgePacket, probability, randomValue);
				
				router = router->links[linkCountIndex].toRoot;
				break;
			}	
		}	
	}	
}

//Name:			defineHosts
//Description:	NetworkTopology class method which takes input in from the standard input after
//				the network topology has been specified and labels host devices as either normal
//				hosts or as attacker hosts 
//Parameters:	None
//Return:		Void
void NetworkTopology:: defineHosts()
{
	int listCount = 0; 
	string input = " ";
	Router* temp;

	cout << "Enter the addresses of the attackers and the addresses of the normal hosts as two" << endl;
	cout << "comma separated lists, each in parentheses, both lists in between curly braces." << endl;
	cout << "The correct format is: { ( Ai, Aj, Ak ) ( Ni, Nj, Nk ) }" << endl;
	
	while(input != "}")
	{
		cin >> input;

		if(input != "{" && input != "}"  && input != ")")
		{	
			if(input == "(")
			{
				listCount++;
			}	
			else
			{
				input = formatInput(input);
				temp = getRouter(input);

				if(temp != NULL)
				{
					temp->leaf = true;

					if(listCount == 1)
					{	
						temp->attacker = true;
						temp->links[0].toRoot->attacker = true;
						attackerCount++;
					}	
				}	
				else
				{
					cout << "That host doesn't exist." << endl;
				}
			}	
		}
	}
}

//Name:			getRouter
//Description:	NetworkTopology class method which takes in a string corresponding to a Router in topology
//				and a reference to that Router is returned
//Parameters:	Takes in a string corresponding to the name or address of a Router in the topology
//Return:		Returns a pointer to a Router which is the Router that is sought
Router* NetworkTopology:: getRouter(string input)
{
	int index;
	Router* router = NULL;

	for(index = 0; index < routerCount; index++)
	{
		if(routers[index]->address == input)
		{
			router = routers[index];
			break;
		} 
	}	

	return router;
}

//Name:			addRouter
//Description:	NetworkTopology class method which takes a reference to a Router, creates a new Router 
//				object, calls that Routers addRouter passing it a reference to the newly created Router, 
//				and also adds a reference to the Router to a vector which holds all Routers in the topology				 
//Parameters:	Takes in a pointer to the current Router and a string corresponding to the name of
//				the Router to be added to the current Router
//Return:		Void
void NetworkTopology:: addRouter(Router* currentRouter, string routerAdded)
{
	Router* router = new Router(routerAdded, false);

	currentRouter->addRouter(router);
	routers.push_back(router);
	routerCount++; 
}

//Name:			formatInput
//Description:	NetworkTopology class method which takes in a string, if the string has a comma
//				at the end of it, it is removed and the formatted string is returned
//Parameters:	Takes in a string which is the input which will be formated
//Return:		Returns the formatted string
string NetworkTopology:: formatInput(string input)
{
	int lastChar = input.size() - 1;
	char buffer[100];

	strcpy(buffer, input.c_str());

	if(buffer[lastChar] == ',')
	{
		buffer[lastChar] = '\0';
	}	

	input = buffer;

	return input;
}

//Name:			printNetwork
//Description:	NetworkTopology class method which prints out all the Routers in the topology
//Parameters:	None
//Return:		Void
void NetworkTopology:: printNetwork()
{
	int index;

	cout << endl << "The baseline number of packets at is leaf is: " << packetCount << endl;

	for(index = 0; index < routerCount; index++)
	{
		routers[index]->printRouter();
	}	
}

//Name:			printPackets
//Description:	NetworkTopology class method which prints out all packets in the topology
//Parameters:	None
//Return:		Void
void NetworkTopology:: printPackets()
{
	int index, size;

	size = nodePackets.size();
	sort(nodePackets.begin(), nodePackets.end(), sortNodePackets);

	cout << endl << "Node packets:" << endl;
	for(index = 0; index < size; index++)
	{
		cout << "Packet multiplier: " << nodePackets[index].multiplier << endl;
		cout << "Packet probability: " << nodePackets[index].probability << endl;
		cout << "Packet mark: " << nodePackets[index].mark << endl;
	}	

	size = edgePackets.size();
	sort(edgePackets.begin(), edgePackets.end(), sortEdgePackets);

	cout << endl << "Edge packets:" << endl << endl;
	for(index = 0; index < size; index++)
	{
		cout << "Packet multiplier: " << edgePackets[index].multiplier << endl;
		cout << "Packet probability: " << edgePackets[index].probability << endl;
		cout << "Packet distance: " << edgePackets[index].distance << endl;
		cout << "Packet first mark: " << edgePackets[index].firstMark << endl;
		cout << "Packet second mark: " << edgePackets[index].secondMark << endl << endl;
	}	

	cout << endl;
}

//Name:			printNodes
//Description:  NetworkTopology class method which prints out all the Nodes in the topology
//Parameters:	None
//Return:		Void
void NetworkTopology:: printNodes()
{
	int index, innerIndex, size;

	for(index = 0; index < (MAX_PROBABILITY * MAX_MULTIPLIER); index++)
	{
		cout << "Probability: " << probability[index / 3] << " Multiplier: " << attackMultiplier[index % 3] << endl;
		size = nodeCounts[index].size();
		for(innerIndex = 0; innerIndex < size; innerIndex++)
		{
			cout << nodeCounts[index][innerIndex].routerName << ":";
			cout << nodeCounts[index][innerIndex].count;

			if(innerIndex < size - 1) 
			{
				cout << ", ";
			}
		}	
		cout << endl << endl;
	}
}

//Name:			printEdges
//Description:  NetworkTopology class method which prints out all the Edges in topology
//Parameters:	None
//Return:		Void
void NetworkTopology:: printEdges()
{
	int index, innerIndex, size;

	for(index = 0; index < (MAX_PROBABILITY * MAX_MULTIPLIER); index++)
	{
		//sort(edgeCounts[index].begin(), edgeCounts[index].end(), sortEdges);

		cout << "Probability: " << probability[index / 3] << " Multiplier: " << attackMultiplier[index % 3] << endl;
		size = edgeCounts[index].size();
		for(innerIndex = 0; innerIndex < size; innerIndex++)
		{
			cout << "{(" << edgeCounts[index][innerIndex].closeEnd << "-";
			cout << edgeCounts[index][innerIndex].distance << "-";
			cout << edgeCounts[index][innerIndex].farEnd << ") : ";
			cout << edgeCounts[index][innerIndex].count << " : ";
			cout << "[" << edgeCounts[index][innerIndex].closeRouter->address << ", ";
			cout << edgeCounts[index][innerIndex].farRouter->address << "]}";

			if(innerIndex < size - 1) 
			{
				cout << ", ";
			}
		}	
		cout << endl << endl;
	}
}

//Name:			printNodeResults
//Description:  NetworkTopology class method which prints out all the NodeSamplingResults in the 
//				topology
//Parameters:	Takes in an ofstream object corresponding to a file to have the Node Sampling result
//				written out to and a bool which signals whether to write to the file in addition to 
//				printing to the screen
//Return:		Void
void NetworkTopology:: printNodeResults(ofstream& outFile, bool toFile)
{
	int index, innerIndex, size;

	cout << endl;
	for(index = 0; index < (MAX_PROBABILITY * MAX_MULTIPLIER); index++)
	{
		cout << "Baseline packets: " << nodeResults[index].baselinePackets << endl;
		cout << "Attack multiplier: " << nodeResults[index].attackMultiplier << endl;
		cout << "Total packets: " << nodeResults[index].attackMultiplier * nodeResults[index].baselinePackets << endl;
		cout << "Probability : " << nodeResults[index].probability << endl;
		cout << "Accurate: " << boolalpha << nodeResults[index].accurate << endl;
		cout << "Nodes in path:" << endl << "\t\t\t";
		size = nodeResults[index].finalPath.size();
		for(innerIndex = 0; innerIndex < size; innerIndex++)
		{
			cout << nodeResults[index].finalPath[innerIndex].routerName << ":";
			cout << nodeResults[index].finalPath[innerIndex].count << " ";
		}	
		cout << endl << endl;
	}

	if(toFile)
	{
		outFile << endl;
		for(index = 0; index < (MAX_PROBABILITY * MAX_MULTIPLIER); index++)
		{
			outFile << "Baseline packets: " << nodeResults[index].baselinePackets << endl;
			outFile << "Attack multiplier: " << nodeResults[index].attackMultiplier << endl;
			outFile << "Total packets: " << nodeResults[index].attackMultiplier * nodeResults[index].baselinePackets << endl;
			outFile << "Probability : " << nodeResults[index].probability << endl;
			outFile << "Accurate: " << boolalpha << nodeResults[index].accurate << endl;
			outFile << "Nodes in path:" << endl << "\t\t\t";
			size = nodeResults[index].finalPath.size();
			for(innerIndex = 0; innerIndex < size; innerIndex++)
			{
				outFile << nodeResults[index].finalPath[innerIndex].routerName << ":";
				outFile << nodeResults[index].finalPath[innerIndex].count << " ";
			}	
			outFile << endl << endl;
		}
	}
}

//Name:			printEdgeResults
//Description:	NetworkTopology class method which prints out all the EdgeSamplingResults in the 
//				topology
//Parameters:	Takes in an ofstream object corresponding to a file to have the Edge Sampling
//				results written out to and a bool which signals whether to write to the file in 
//				addition to printing to the screen
//Return:		Void
void NetworkTopology:: printEdgeResults(ofstream& outFile, bool toFile)
{
	int index;

	for (index = 0; index < (MAX_MULTIPLIER * MAX_PROBABILITY); index++)
	{
		cout << endl << "Baseline packets: " << edgeResults[index].baselinePackets << endl;
		cout << "Attack multiplier: " << edgeResults[index].attackMultiplier << endl;
		cout << "Total packets: " << edgeResults[index].attackMultiplier * edgeResults[index].baselinePackets << endl;
		cout << "Probability : " << edgeResults[index].probability << endl;
		cout << "Accurate: " << boolalpha << edgeResults[index].accurate << endl;
		cout << "Attackers: " << attackerCount << endl;
		cout << "Tree: " << endl;

		if(toFile)
		{
			outFile << endl << "Baseline packets: " << edgeResults[index].baselinePackets << endl;
			outFile << "Attack multiplier: " << edgeResults[index].attackMultiplier << endl;
			outFile << "Total packets: " << edgeResults[index].attackMultiplier * edgeResults[index].baselinePackets << endl;
			outFile << "Probability : " << edgeResults[index].probability << endl;
			outFile << "Accurate: " << boolalpha << edgeResults[index].accurate << endl;
			outFile << "Attackers: " << attackerCount << endl;
			outFile << "Tree: " << endl;
		}	

		printEdgeTree(edgeResults[index].root, outFile, toFile);

		cout << endl;

		if(toFile)
		{
			outFile << endl;
		}	
	}	
}

//Name:			printEdgeTree
//Description:	Takes in an Edge pointer, prints each of the Routers out, the count for that
//				edge, and then recursively moves through the children Edges in order to print the
//				entire tree to the screen 
//Parameters:	Takes in a Edge pointer, and ofstream object corresponding to a file to have the 
//				Edge EdgeSamplingResults results written out to and a bool which signals whether to 
//				write to the file in addition to printing to the screen
//Return:		Void
void NetworkTopology:: printEdgeTree(Edge* edgeReference, ofstream& outFile, bool toFile)
{
	int index, size = edgeReference->children.size();

	cout << "[" << edgeReference->closeRouter->address << "-"; 
	cout << edgeReference->farRouter->address << "]:" << edgeReference->count << " {";

	if(toFile)
	{
		outFile << "[" << edgeReference->closeRouter->address << "-"; 
		outFile << edgeReference->farRouter->address << "]:" << edgeReference->count << " {";
	}

	for(index = 0; index < size; index++)
	{
		printEdgeTree(edgeReference->children[index], outFile, toFile);
	}	

	cout << "} ";

	if(toFile)
	{
		outFile << "} ";
	}	
}

//Name:			sortPackets
//Description:	Free function which compares the mark field of two Packet structs in order
//				to assist in sorting vectors containing Packet structs
//Parameters:	Takes in two Packet structs
//Return:		Returns a bool corresponding to whether or not the first parameter is greater
//				greater than the second
bool sortNodePackets(const NodePacket& firstPacket, const NodePacket& secondPacket)
{
	return firstPacket.mark > secondPacket.mark;
}

//Name:			sortEdgePackets
//Description:	Free function which compares the distance field of two EdgePacket structs in order
//				to assist in sorting vectors containing EdgePacket structs
//Parameters:	Takes in two EdgePacket structs
//Return:		Returns a bool corresponding to whether or not the first EdgePacket is
//				smaller than the second
bool sortEdgePackets(const EdgePacket& firstPacket, const EdgePacket& secondPacket)
{
	return firstPacket.distance < secondPacket.distance;
}

//Name:			sortNodes
//Description:	Free function which compares the count field of two Node structs in order
//				to assist in sorting vectors containing Node structs
//Parameters:	Takes in two Node structs
//Return:		Returns a bool corresponding to whether or not the first parameter is greater
//				greater than the second
bool sortNodes(const Node& firstNode, const Node& secondNode)
{
	return firstNode.count > secondNode.count;
}

//Name:			sortEdges
//Description:	Free function which compares the distance field of two Edge structs in order
//				to assist in sorting vectors containing Edge structs
//Parameters:	Takes in two Edge structs
//Return:		Returns a bool corresponding to whether or not the first Edge is smaller
//				than the second
bool sortEdges(const Edge& firstNode, const Edge& secondNode)
{
	return firstNode.distance < secondNode.distance;
}

#endif