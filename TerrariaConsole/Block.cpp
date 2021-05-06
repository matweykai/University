#include "Block.h"

Coordinates* Block::get_coordinates() 
{
	return &coordinates;
}
short Block::get_color() 
{
	return color;
}
Block::Block(unsigned int x, unsigned int y, short color)
{
	this->coordinates = Coordinates(x, y);
	this->color = color;
}