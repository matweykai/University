#pragma once
#define WIDTH 10
#define HEIGHT 10
#define WIDTH 10
#define PLAYER_UPPER '0'
#define PLAYER_DOWN 'A'
#define BLOCK_SYM 'O'
#define WALL_SYM '#'
//Нужны для перемещения курсора
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "Block.h"
#include "Player.h"
#include <vector>
#include <windows.h>
#include <iostream>
#include <algorithm>

class Engine
{
	vector<Block> blocks;
	Player player;
	char current_frame[HEIGHT][WIDTH];

	void init_map();
	void update_frame();
	char** form_next_frame();
	void control_enter();
public:
	void start_game();
};


void SetCursorPosition(int x, int y);
void SetConsoleColour(unsigned short colour);
