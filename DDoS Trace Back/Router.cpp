//
// Bryan Kline
// CS445
// HW#1
// Router.cpp
// Router class implementation file
//

#ifndef ROUTER_CPP
#define ROUTER_CPP

#include <iostream>
#include <string>
#include "Router.h"
#include "NetworkTopology.h"

using namespace std;

//Name:			Router
//Description: 	Router class parameterized constructor
//Parameters:	Takes in a string corresponding to the name or address of the Router and a bool which
//				determines whether or not the Router is the root of the attack tree
//Return:		None
Router:: Router(string addressName, bool isRoot)
{
	address = addressName;
	linkCount = 0;
	root = isRoot;
	leaf = false;
	attacker = false;
}

//Name:			~Router
//Description:	Router class destructor
//Parameters:	None
//Return:		None
Router:: ~Router()
{
	links.clear();
}

//Name:			addRouter
//Description:	Router class Method which adds a Link from the local object to another Router 
//				passed into the method and which adds all the fields in the Link between the
//				two Routers
//Parameters:	Takes in a pointer to a Router with which a Link to the local object is established 
//Return:		Void
void Router:: addRouter(Router* routerAdded)
{
	Link temp;
	string linkName = address + "-" + routerAdded->address;

	temp.name = linkName;
	temp.toRoot = this;
	temp.toLeaf = routerAdded;
	temp.towardsRoot = false;

	links.push_back(temp);
	linkCount++;

	linkName = routerAdded->address + "-" + address;
	temp.name = linkName;
	temp.toRoot = this;
	temp.toLeaf = routerAdded;
	temp.towardsRoot = true;

	routerAdded->links.push_back(temp);
	routerAdded->linkCount++;
}

//Name:			markNodePacket
//Description:	Router class Method which takes in a random number and compares it with a probability 
//				and compares them to determine whether or not to mark a packet also passed into the
//				method with the name or address of the Router
//Parameters:	Takes in a pointer to a Packet, a float corresponding to a probability to mark the
//				packet, and a random number which is used to compare against the probability
//Return:		Void
void Router:: markNodePacket(NodePacket* packet, float probability, int randomValue)
{
	float probabilityValue = randomValue / 1000.0;

	if(probabilityValue < probability)
	{
		packet->mark = address;	
	}	
}

//Name:			markEdgePacket
//Description:	Router class Method which takes in a random number and compares it with a probability 
//				and compares them to determine whether or not to mark a packet also passed into the
//				method with the name or address of the Router
//Parameters:	Takes in a pointer to an Edge, a float corresponding to a probability to mark the
//				packet, and a random number which is used to compare against the probability
//Return:		Void
void Router:: markEdgePacket(EdgePacket* packet, float probability, int randomValue)
{
	float probabilityValue = randomValue / 1000.0;

	if(probabilityValue < probability)
	{
		packet->firstMark = address;
		packet->secondMark = " ";
		packet->distance = 0;
	}	
	else if(packet->distance != -1)
	{
		if(packet->distance == 0)
		{	
			packet->secondMark = address;
		}	

		packet->distance++;
	}	
}

//Name:			printRouter
//Description:	Router class Method which prints out all the attributes of the Router
//Parameters:	None
//Return:		Void
void Router:: printRouter()
{
	int index;

	cout << endl;
	cout << "Address: " << address  << endl;
	cout << "Root: " << boolalpha << root << endl;
	cout << "Leaf: " << boolalpha << leaf << endl;
	cout << "Attacker: " << boolalpha << attacker << endl;
	cout << "Number of links: " << linkCount << endl;
	cout << "Links:\t(";

	for(index = 0; index < linkCount; index++)
	{
		cout << links[index].toRoot->address << "-";

		if(links[index].toLeaf != NULL)
		{	
			cout << links[index].toLeaf->address << " (" << boolalpha << links[index].towardsRoot << ")";
		}
		else
		{
			cout << "NULL";
		}	 	

		if(index < linkCount - 1)
		{
			cout << ", ";
		}
	}	

	cout << ")" << endl;
}

#endif 