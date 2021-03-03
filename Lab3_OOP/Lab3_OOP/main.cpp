#include "Func.h"
#include "FoodDataBase.h"
#include <windows.h>
#include "Menu.h"

using namespace std;

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu;

	menu.startMenu();

	return 0;
}