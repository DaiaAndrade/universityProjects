#include "graphHeader.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;
using std::list;
using std::vector;

float distanceBetween2Points(Pair A, Pair B);
int minimumKey(float key[], bool mstSet[], int size);

Graph::Graph()
{
	this->numberNodes = 0;
}

Graph::~Graph()
{

}

void Graph::insertPair(float xValue, float yValue)
{
	Pair coordinates = Pair();
	coordinates.setXY(xValue,yValue);
	this->nodes.push_back(coordinates);

}

void Graph::increaseNumberNodes()
{
	this->numberNodes++;
}

int Graph::getNumberNodes()
{
	return this->numberNodes;
}

void Graph::printPairs()
{
	list<Pair>::iterator iterator;
	for(iterator = this->nodes.begin(); iterator != this->nodes.end(); iterator++)
	{
		cout << iterator->getX() << "," << iterator->getY() << endl;
	}
}

float Graph::shortestPath()
{
	list<Pair> auxNodes = this->nodes;
	list<Pair>::iterator it, it2;
	Pair auxNode, inicio;
	int i,j, size;
	size = auxNodes.size();
	float distances[size][size];
	float menorCaminho, menorValor;
	int parent[size];
	float key[size];
	bool inseridos[size];

		
	it = auxNodes.begin();
	for (i=0;i<size;i++)
	{
		it2 = auxNodes.begin();
		inicio.setXY(it->getX(),it->getY());
		for(j=0;j<size;j++)
		{
			auxNode.setXY(it2->getX(),it2->getY());
			distances[i][j] = distanceBetween2Points(inicio,auxNode);
			it2++;
		}
		it++;
	}

	for (i=0; i<size; i++)
	{
		key[i] = INT_MAX, inseridos[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;

	for (i=0; i<size-1; i++)
	{
		int u = minimumKey(key, inseridos, size);
		inseridos[u] = true;

		for (j=0; j<size; j++)
		{
			if (distances[u][j] && inseridos[j] == false && distances[u][j] <  key[j])
			{
				parent[j]  = u;
				key[j] = distances[u][j];	
			}
		}
	}
	
	for (i=1; i<size; i++)
	{
		menorCaminho += distances[i][parent[i]];
	}

	return menorCaminho;
}

float distanceBetween2Points(Pair A, Pair B)
{
	float distance, x, y, bValueX, bValueY, aValueX, aValueY;
	bValueX = B.getX();
	bValueY = B.getY();
	aValueX = A.getX();
	aValueY = A.getY();
	x = pow(bValueX - aValueX,2);
	y = pow(bValueY - aValueY,2);
	if (x == 0 && y == 0)
	{
		distance = 0;
	}
	else
	{
		distance = sqrt(x+y);
	}
	return distance;
}

int minimumKey(float key[], bool mstSet[], int size)
{
	int min = INT_MAX, minIndex;
	int v;
	for (v=0; v<size; v++)
	{
		if (mstSet[v] == false && key[v] < min)
		{
			min = key[v];
			minIndex = v;
		}
	}
 
	return minIndex;
}
