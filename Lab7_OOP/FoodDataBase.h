#pragma once

#include "Date.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>

#define PRICE_S 5
#define DATE_S 12

using namespace std;

class Food
{
	static int foodCount;
	static int maxLen;

	double price;
	Date* produceDate;
	string* name;

public:
	Food(double price = 0, Date* produce_date = nullptr, string* name = nullptr);
	Food(const Food& obj);

	double get_price();
	Date* get_date();
	string* get_name();
	static int get_food_count();
	void destroy(bool copy = false);
	void dump_obj(ofstream* stream);
	~Food();

	bool operator ==(Food obj);
	Food& operator =(const Food& obj);
	friend ostream& operator <<(ostream& os, const Food& right);
};

class FoodDataBase
{
	deque<Food> arr;
	string path;

	Food* get_obj(ifstream* stream);
	void download_db();
	void dump_db();
	bool is_end(ifstream* stream);

public:
	FoodDataBase(string path);
	deque<Food> get_food_arr();
	void add_record(double price, Date* produce_date, string* name, bool before = false);
	void delete_record(int index = 0);

	~FoodDataBase();
};