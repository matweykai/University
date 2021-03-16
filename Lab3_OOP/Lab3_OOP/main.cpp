#include "Func.h"
#include "FoodDataBase.h"
#include <windows.h>
#include "Menu.h"

using namespace std;

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<string>* t_vect = new vector<string>();
	t_vect->push_back("t_12");

	Food* t_food = new Food(1, FoodType(0), 1, 1, new Date(1,1,1), new string("name"));
	t_food->print(t_vect, 10);
	cout << endl;

	t_food->destroy();
	t_food = new FoodExtra(1, FoodType(0), 1, 1, new Date(1, 1, 1), new string("name"), new Date(2, 2, 2));
	t_food->print(t_vect, 10);
	t_food->destroy();

	delete t_vect;
	//Menu menu;

	//menu.startMenu();

	return 0;
}