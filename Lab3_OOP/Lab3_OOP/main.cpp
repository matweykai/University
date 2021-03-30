#include "Func.h"
#include "Menu.h"
#include <windows.h>

using namespace std;

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu;

	menu.startMenu();

	return 0;
}