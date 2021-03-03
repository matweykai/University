#pragma once

#include <iostream>
#include <conio.h>
#include "Func.h"

using namespace std;

class Menu 
{
	FoodDataBase* db = nullptr;
	vector<string>* types = nullptr;
	void findByName();
	void showAll();
	void showSortedArr();
	void findByDate();
	void addRecord();
	Date enterDate();

public:
	Menu();
	void startMenu();
	~Menu();
};
template<class T>
T* enter_num();