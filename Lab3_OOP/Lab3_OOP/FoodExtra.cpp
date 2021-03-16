#include "FoodDataBase.h"

void FoodExtra::print(vector<string>* types, int name_size, int type_size, int weight_size, int count_size, int date_size, int price_size)
{
	Food::print(types, name_size, type_size, weight_size, count_size, date_size, price_size);

	cout.width(date_size);
	Date* t_date = saleDate;
	cout << to_string(t_date->get_day()) + "." + to_string(t_date->get_month()) + "." + to_string(t_date->get_year());
}
void FoodExtra::destroy(bool copy) 
{
	Food::destroy(copy);
	if (saleDate != nullptr)
		delete saleDate;
}
void FoodExtra::dump_obj(ofstream* stream)
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
		*stream << saleDate->get_day() << endl;
		*stream << saleDate->get_month() << endl;
		*stream << saleDate->get_year() << endl;
		*stream << *name << endl;
	}
}

FoodExtra::~FoodExtra() 
{
	destroy(true);
}