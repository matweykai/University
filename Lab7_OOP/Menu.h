#pragma once
#include "FoodDataBase.h"
#include "EnterException.h"
#include "Func.h"
#include <conio.h>

using namespace std;

class Menu 
{
	FoodDataBase* db;

	void showAll();
	void showSortedArr();
	void findByDate();
	void addRecord(istream& str);
	Date enterDate();

public:
	Menu(string fileName);
	void startMenu();
	~Menu();
};

template<class T>
T* enter_num();