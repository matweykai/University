#pragma once
#include "Coordinates.h"
#include "Item.h"

class Block : Item
{
	Coordinates coordinates;
	short color;
public:
	Block(unsigned int x, unsigned int y, short color);
	Coordinates* get_coordinates();
	short get_color();
};


