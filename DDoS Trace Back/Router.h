//
// Bryan Kline
// CS445
// HW#1
// Router.h
// Router class header file
//  

#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <vector>

using namespace std;

class Router;
struct NodePacket;
struct EdgePacket;

struct Link
{
	bool towardsRoot;
	string name;
	Router* toRoot;
	Router* toLeaf;
};

class Router
{
    public:
    
        Router(string addressName, bool isRoot);
        ~Router();
        void addRouter(Router* routerAdded);
        void markNodePacket(NodePacket* packet, float probability, int randomValue);
        void markEdgePacket(EdgePacket* packet, float probability, int randomValue);
        void printRouter();

    friend class NetworkTopology;    

    private:
        
        int linkCount;
        bool root;
        bool leaf;
        bool attacker;
        string address;
        vector<Link> links;
};

#endif 
 
