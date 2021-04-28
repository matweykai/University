#include "Coordinates.h"

Coordinates::Coordinates(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
}

void Coordinates::moveRight()
{
	x++;
}

void Coordinates::moveLeft()
{
	x--;
}

void Coordinates::moveUp()
{
	y++;
}

void Coordinates::moveDown()
{
	y--;
}

unsigned int Coordinates::getX()
{
	return this->x;
}

unsigned int Coordinates::getY()
{
	return this->y;
}
