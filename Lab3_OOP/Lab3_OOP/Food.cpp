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
	if (produceDate != nullptr)
		delete produceDate;
	this->produceDate = new Date(*obj.produceDate);
	if (name != nullptr)
		delete name;
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
void Food::print(vector<string>* types, int name_size, int type_size, int weight_size, int count_size, int date_size, int price_size)
{
	cout.width(name_size);
	cout << *name;

	cout.width(type_size);
	vector<string>::iterator iter = types->begin();

	for (int j = 0; j < (int)type; j++)
		iter++;
	cout << *iter;

	cout.width(weight_size);
	cout << weight;

	cout.width(count_size);
	cout << count;

	cout.width(price_size);
	cout << price;

	cout.width(date_size);
	Date* t_date = produceDate;
	cout << to_string(t_date->get_day()) + "." + to_string(t_date->get_month()) + "." + to_string(t_date->get_year());
}
void Food::dump_obj(ofstream* stream)
{
	if (stream != nullptr)
	{
		*stream << price << endl;
		*stream << weight << endl;
		*stream << (int)type << endl;
		*stream << count << endl;
		*stream << produceDate->get_day() << endl;
		*stream << produceDate->get_month() << endl;
		*stream << produceDate->get_year() << endl;
		*stream << *name << endl;
	}
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
	if (produceDate != nullptr)
		delete produceDate;
	this->produceDate = new Date(*obj.produceDate);
	if (name != nullptr)
		delete name;
	this->name = new string(*obj.name);

	return *this;
}