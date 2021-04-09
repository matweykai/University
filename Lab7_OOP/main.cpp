#include "Menu.h"
#include <windows.h>

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu("test.txt");

	menu.startMenu();

	return 0;
}