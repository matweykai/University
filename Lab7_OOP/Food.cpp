#include "FoodDataBase.h"

int Food::foodCount = 0;
int Food::maxLen = 0;

Food::Food(double price, Date* produce_date, string* name)
{
	if (price < 0)
		throw exception("Wrong arguments");

	this->price = price;
	this->produceDate = produce_date;
	this->name = name;

	if (name != nullptr)
	{
		Food::foodCount++;
		if (maxLen < name->length())
			maxLen = name->length();
	}
}
Food::Food(const Food& obj)
{
	this->price = obj.price;
	this->produceDate = new Date(*obj.produceDate);
	this->name = new string(*obj.name);
}

double Food::get_price() { return price; }
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

	produceDate = nullptr;
	name = nullptr;
}
void Food::dump_obj(ofstream* stream)
{
	if (stream != nullptr)
	{
		*stream << price << endl;
		*stream << produceDate->get_day() << endl;
		*stream << produceDate->get_month() << endl;
		*stream << produceDate->get_year() << endl;
		*stream << *name << endl;
	}
}

bool Food::operator==(Food obj)
{
	return price == obj.price
		&& produceDate == obj.produceDate
		&& name == obj.name;
}
Food& Food::operator =(const Food& obj)
{
	this->price = obj.price;
	if (produceDate != nullptr)
		delete produceDate;
	this->produceDate = new Date(*obj.produceDate);
	if (name != nullptr)
		delete name;
	this->name = new string(*obj.name);

	return *this;
}
ostream& operator <<(ostream& os, const Food& right) 
{
	os.width(Food::maxLen);
	os << *right.name;

	os.width(PRICE_S);
	os << right.price;

	os.width(DATE_S);
	os << to_string(right.produceDate->get_day()) + "." + to_string(right.produceDate->get_month()) + "." + to_string(right.produceDate->get_year());

	return os;
}