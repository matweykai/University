#pragma once

#include <iostream>
#include <conio.h>
#include "Func.h"
#include "EnterException.h"

using namespace std;

class Menu 
{
	FoodDataBase* db = nullptr;
	vector<string>* types = nullptr;
	void findByName();
	void showAll();
	void showSortedArr();
	void findByDate();
	void addRecord(istream& str);
	Date enterDate();

public:
	Menu();
	void startMenu();

	friend istream& operator >>(istream& str, Menu* menu);
	~Menu();
};
template<class T>
T* enter_num();