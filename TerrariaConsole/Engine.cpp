#include "Engine.h"

void Engine::update_frame() 
{
	char** next_frame = form_next_frame();

	for(int i = 1; i < HEIGHT - 1; i++)
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (current_frame[i][j] != next_frame[i][j])
			{
				vector<Block>::iterator found = find_if(blocks.begin(), blocks.end(), [i, j](Block obj)
					{ return obj.get_coordinates()->getX() == j && obj.get_coordinates()->getY() == i; });
				if(found != blocks.end())
					SetConsoleColour(found->get_color());
				else
					SetConsoleColour(FOREGROUND_INTENSITY);
				SetCursorPosition(j, i);
				cout << next_frame[i][j];
			}
			current_frame[i][j] = next_frame[i][j];
		}

	for (int i = 0; i < HEIGHT; i++)
		delete[] next_frame[i];
	delete next_frame;
}
char** Engine::form_next_frame() 
{
	char** result = new char*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++)
		result[i] = new char[WIDTH];

	for (int i = 1; i < HEIGHT - 1; i++)
		for (int j = 1; j < WIDTH - 1; j++)
			result[i][j] = ' ';

	for (int i = 0; i < blocks.size(); i++)
	{
		result[blocks[i].get_coordinates()->getY()][blocks[i].get_coordinates()->getX()] = BLOCK_SYM;
		result[player.get_coordinates()->getY()][player.get_coordinates()->getX()] = PLAYER_DOWN;
		result[player.get_coordinates()->getY() - 1][player.get_coordinates()->getX()] = PLAYER_UPPER;
	}
	
	return result;
}
void Engine::init_map()
{
	for (int i = 1; i < HEIGHT - 1; i++)	//Боковые стены
	{
		//Заполнение массива
		current_frame[i][0] = WALL_SYM;
		current_frame[i][WIDTH - 1] = WALL_SYM;
		for (int j = 1; j < WIDTH - 1; j++)
			current_frame[i][j] = ' ';
		//Вывод в консоль
		SetCursorPosition(i, 0);
		cout << WALL_SYM;
		SetCursorPosition(i, WIDTH - 1);
		cout << WALL_SYM;
	}
	for (int i = 0; i < WIDTH; i++)	//Верхняя и нижняя стены
	{
		//Заполнение массива
		current_frame[0][i] = WALL_SYM;
		current_frame[HEIGHT - 1][i] = WALL_SYM;
		//Вывод в консоль
		SetCursorPosition(0, i);
		cout << WALL_SYM;
		SetCursorPosition(HEIGHT - 1, i);
		cout << WALL_SYM;
	}
	//blocks.push_back(Block());
}
void Engine::start_game() 
{
	init_map();
	//FOR TESTING
	int counter = 0;
	while (true)
	{
		update_frame();
		if (!(counter++ % 5))
		{
			blocks.push_back(Block(HEIGHT / 2 + (rand() % 4), WIDTH / 2 + (rand() % 4), FOREGROUND_BLUE));
			switch (rand() % 4)
			{
			case 0:
				player.moveDown();
				break;
			case 1:
				player.moveUp();
				break;
			case 2:
				player.moveLeft();
				break;
			case 3:
				player.moveRight();
				break;
			}
		}
		Sleep(500);
	}
}

void SetCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
void SetConsoleColour(unsigned short colour)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	SetConsoleTextAttribute(hOut, colour);
}