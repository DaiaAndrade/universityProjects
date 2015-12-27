#ifndef GRAPHHEADER_H_
#define GRAPHHEADER_H_

#include <iostream>
#include <list>


using namespace std;
using std::list;

class Pair
{
	float xCoordinate, yCoordinate;

public:
	Pair();
	~Pair();
	void setXY(float x, float y);
	float getX();
	float getY();
};

class Graph
{
	list<Pair> nodes;
	int numberNodes;

public:
	Graph();
	~Graph();
	void insertPair(float xValue, float yValue);
	void increaseNumberNodes();
	int getNumberNodes();
	void printPairs();
	float shortestPath();
};

#endif
