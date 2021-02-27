#pragma once
#include "Date.h"
#include <string>

using namespace std;

enum class FoodType {};

class Food 
{
	static int foodCount;

	double price;
	FoodType  type;
	double weight;
	int count;
	Date* produceDate;
	string* name;

public:
	Food(double price = 0, FoodType type = FoodType(0), double weight = 0, int count = 0, Date* produce_date = nullptr, string* name = nullptr);
	Food(const Food& obj);
	
	double get_price();
	FoodType get_type();
	double get_weight();
	int get_count();
	Date* get_date();
	string* get_name();
	static int get_food_count();
	void destroy(bool copy = false);
	~Food();

	bool operator ==(Food obj);
	Food& operator =(const Food& obj);
	friend ostream& operator <<(ostream& os, const Food& right);
};