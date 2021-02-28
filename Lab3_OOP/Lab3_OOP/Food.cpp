#include "FoodDataBase.h"

int Food::foodCount = 0;

Food::Food(double price, FoodType type, double weight, int count, Date* produce_date, string* name)
{
	if (price < 0 || weight < 0)
		throw exception("Wrong arguments");

	this->price = price;
	this->type = type;
	this->weight = weight;
	this->count = count;
	this->produceDate = produce_date;
	this->name = name;

	if (name != nullptr)
		Food::foodCount++;
}
Food::Food(const Food& obj)
{
	this->price = obj.price;
	this->type = obj.type;
	this->weight = obj.weight;
	this->count = obj.count;
	this->produceDate = new Date(*obj.produceDate);
	this->name = new string(*obj.name);
}

double Food::get_price() { return price; }
FoodType Food::get_type() { return type; }
double Food::get_weight() { return weight; }
int Food::get_count() { return count; }
Date* Food::get_date() { return new Date(*produceDate); }
string* Food::get_name() { return new string(*name); }
int Food::get_food_count() { return foodCount; }
void Food::destroy(bool copy) 
{
	if (!copy)
		Food::foodCount--;
	this->~Food();
}
Food::~Food() 
{
	if (produceDate != nullptr)
		delete produceDate;
	if (name != nullptr)
		delete name;
}

bool Food::operator==(Food obj) 
{
	return price == obj.price
		&& type == obj.type
		&& produceDate == obj.produceDate
		&& name == obj.name;
}
Food& Food::operator =(const Food& obj) 
{
	this->price = obj.price;
	this->type = obj.type;
	this->weight = obj.weight;
	this->count = obj.count;
	this->produceDate = new Date(*obj.produceDate);
	this->name = new string(*obj.name);

	return *this;
}