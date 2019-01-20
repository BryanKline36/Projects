//
// Bryan Kline
// CS445
// HW#1
// NetworkTopology.h
// NetworkTopology class header file
//

#ifndef NETWORKTOPOLOGY_H
#define NETWORKTOPOLOGY_H

#include <fstream>
#include <string>
#include <vector>
#include "Router.h"

using namespace std;

struct Node
{
	int count;
	string routerName;
};

struct NodeSamplingResult
{
	int baselinePackets;
	int attackMultiplier;
	float probability;
	bool accurate;
	vector<Node> finalPath;
};

struct NodePacket
{
	int multiplier;
	float probability;
	string mark;
};

struct Edge
{
	int count;
	int distance;
	string farEnd; 
	string closeEnd;
	Router* farRouter;
	Router* closeRouter;
	vector<Edge*> children;
};

struct EdgeSamplingResult
{
	int baselinePackets;
	int attackMultiplier;
	float probability;
	bool accurate;
	Edge* root;
};

struct EdgePacket
{
	int multiplier;
	int distance;
	float probability;
	string firstMark;
	string secondMark;
};

class NetworkTopology
{
	static const int MAX_PROBABILITY = 5;
	static const int MAX_MULTIPLIER = 3;	

	public:

		NetworkTopology(string rootName, int packetCountValue);
		~NetworkTopology();

		void buildTopology();
		void runAttack();
		void nodeSamplingResults();
		void edgeSamplingResults();
		int countEdgeAttackers(Edge* edgeReference);
		void buildEdgeTree(int index);
		bool reconstructNodePath(vector<Node> path);
		void sendPacket(Router* router, NodePacket* nodePacket, EdgePacket* edgePacket, float probability);
		void defineHosts();
		Router* getRouter(string input);
		void addRouter(Router* currentRouter, string routerAdded);
		string formatInput(string input);
		void printNetwork();
		void printPackets();
		void printNodes();
		void printEdges();
		void printNodeResults(ofstream& outFile, bool toFile);
		void printEdgeResults(ofstream& outFile, bool toFile);
		void printEdgeTree(Edge* edgeReference, ofstream& outFile, bool toFile);

	private:
		
		int routerCount;
		int nodeCount;
		int packetCount;
		int attackerCount;
		int attackMultiplier[MAX_MULTIPLIER];
		float probability[MAX_PROBABILITY];		

		Router* root;
		vector<Router*> routers;

		vector<EdgePacket> edgePackets;
		vector< vector<Edge> > edgeCounts;
		vector<EdgeSamplingResult> edgeResults;

		vector<NodePacket> nodePackets;
		vector< vector<Node> > nodeCounts;
		vector<NodeSamplingResult> nodeResults;
};

#endif