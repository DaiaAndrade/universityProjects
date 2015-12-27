#include "graphHeader.h"

Pair::Pair()
{

}

Pair::~Pair()
{

}

void Pair::setXY(float x, float y)
{
	this->xCoordinate = x;
	this->yCoordinate = y;
}
float Pair::getX()
{
	return this->xCoordinate;
}
float Pair::getY()
{
	return this->yCoordinate;
}
