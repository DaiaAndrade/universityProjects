#include <iostream>
#include "graphHeader.h"


int main(int argc, char **argv)
{
	Graph novo = Graph();
	int insertions;
	float x,y;
	cin >> insertions;
	while (insertions != 0)
	{
		cin >> x;
		cin >> y;
		novo.insertPair(x,y);
		novo.increaseNumberNodes();
		insertions--;
	}
	cout << novo.shortestPath() << endl;
	return 0;
}
