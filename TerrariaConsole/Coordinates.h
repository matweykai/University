#pragma once
class Coordinates
{

	unsigned int x;
	unsigned int y;

public:
	Coordinates(unsigned int x, unsigned int y);

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();


	unsigned int getX();
	unsigned int getY();
	
};

