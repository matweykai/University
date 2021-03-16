#pragma once
#include "Date.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

enum class FoodType { Muffin, Pie, Cake };

class Food
{
protected:

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
	void virtual destroy(bool copy = false);
	void virtual print(vector<string>* types, int name_size, int type_size = 10, int weight_size = 10, int count_size = 10, int date_size = 14, int price_size = 10);
	void virtual dump_obj(ofstream* stream);
	~Food();
	
	bool operator ==(Food obj);
	Food & operator =(const Food & obj);
	friend ostream & operator <<(ostream & os, const Food & right);

	friend class FoodDataBase;
};

class FoodExtra : public Food 
{
	Date* saleDate;

public:
	FoodExtra(double price = 0, FoodType type = FoodType(0), double weight = 0, int count = 0, Date* produce_date = nullptr, string* name = nullptr, Date* sale_date = nullptr) : Food(price, type, weight, count, produce_date, name)
	{
		this->saleDate = sale_date;
	}
	FoodExtra(const FoodExtra& obj) : Food(obj)
	{
		this->saleDate = new Date(*obj.saleDate);
	}

	void print(vector<string>* types, int name_size, int type_size = 10, int weight_size = 10, int count_size = 10, int date_size = 14, int price_size = 10) override;
	void destroy(bool copy = false) override;
	void dump_obj(ofstream* stream) override;

	FoodExtra& operator =(const FoodExtra& obj);

	~FoodExtra();
};

class FoodDataBase 
{
	static vector<string>* types;
	Food** arr;
	string path;

	Food* get_obj(ifstream* stream);
	void download_db();
	//void dump_obj(Food obj, ofstream* stream);
	void dump_db();
	bool is_end(ifstream* stream);

public:
	FoodDataBase(string path, vector<string>* types);

	vector<string>* get_types();
	Food** get_food_arr();
	void add_record(double price, FoodType type, double weight, int count, Date* produce_date, string* name, Date* sale_date = nullptr);

	~FoodDataBase();
};