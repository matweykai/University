#include "Func.h"

Food** copy_arr(Food** arr, int size)
{
	if (arr == nullptr || size <= 0)
		return nullptr;

	Food** result = new Food*[size];

	for (int i = 0; i < size; i++)
		result[i] = arr[i];

	return result;
}
Food** sort_by_price(Food** arr)
{
	Food** result = copy_arr(arr);
	int size = Food::get_food_count();

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - i - 1; j++)
			if (result[j]->get_price() < result[j + 1]->get_price())
			{
				Food* t_obj = result[j];
				result[j] = result[j + 1];
				result[j + 1] = t_obj;
			}

	return result;
}
Food* find_by_name(Food** arr, string* name)
{
	if (name == nullptr)
		return nullptr;

	int size = Food::get_food_count();

	for (int i = 0; i < size; i++)
	{
		string* t_name = arr[i]->get_name();
		if (*t_name == *name)
		{
			delete t_name;
			return arr[i];
		}
		delete t_name;
	}

	return nullptr;
}
Food** filter_by_date(Food** arr, Date date, int* found)
{
	*found = 0;
	int size = Food::get_food_count();

	for (int i = 0; i < size; i++)
	{
		Date* t_date = arr[i]->get_date();
		if (*t_date == date)
			*(found) += 1;
		delete t_date;
	}

	int counter = 0;
	Food** result = nullptr;

	if(*found != 0)
		result = new Food*[*found];

	for (int i = 0; i < size; i++)
	{
		Date* t_date = arr[i]->get_date();
		if (*t_date == date)
			result[counter++] = arr[i];
		delete t_date;
	}

	return result;
}
void show_table(Food** arr, vector<string>* types, int size)
{
	int name_size = max_size(arr, size) + 2, type_size = 10, weight_size = 10, count_size = 10, price_size = 10, date_size = 20;

	cout.setf(ios::left);
	cout.width(name_size);
	cout << "Название";
	cout.width(type_size);
	cout << "Тип";
	cout.width(weight_size);
	cout << "Вес";
	cout.width(count_size);
	cout << "Кол-во";
	cout.width(price_size);
	cout << "Цена";
	cout.width(date_size);
	cout << "Дата производства";
	cout.width(date_size);
	cout << "Дата продажи" << endl;

	print_line(name_size + type_size + weight_size + count_size + price_size + 2 * date_size, 2);
	cout << endl;

	for (int i = 0; i < size; i++)
	{
		arr[i]->print(types, name_size, type_size, weight_size, count_size, date_size, price_size);
		cout << endl;
	}

	print_line(name_size + type_size + weight_size + count_size + price_size + 2 * date_size, 2);
	cout << endl;
}
int max_size(Food** arr, int size)
{
	int result = 0;
	
	for (int i = 0; i < size; i++)
	{
		string* t_name = arr[i]->get_name();

		if (result < t_name->length())
			result = t_name->length();

		delete t_name;
	}

	return result;
}
void print_line(int size, int adding_count)
{
	for (int i = 0; i < size + adding_count; i++)
		cout << "-";
}
Date get_current_date() 
{
	time_t now = time(0);

	tm* temp = new tm; 
	localtime_s(temp, &now);

	return Date(temp->tm_mday, temp->tm_mon + 1, 1900 + temp->tm_year);
}
Food** find_spoiled_food(Food** arr, unsigned int hours, int* found)
{
	Food** result = nullptr;
	Date today = get_current_date();
	int spoiled_num = today.get_year() * 365 + today.get_month() * 31 + today.get_day() - hours / 24;

	for (int i = 0; i < Food::get_food_count(); i++)
	{
		Date* temp_date = arr[i]->get_date();
		if (temp_date == nullptr)
			throw invalid_argument("Date is null");
		if (temp_date->get_day() + temp_date->get_month() * 31 + temp_date->get_year() * 365 < spoiled_num)
			*found += 1;
	}
	if (*found != 0)
	{
		result = new Food * [*found];
		int counter = 0;
		for (int i = 0; i < Food::get_food_count(); i++)
		{
			Date* temp_date = arr[i]->get_date();
			if (temp_date->get_day() + temp_date->get_month() * 31 + temp_date->get_year() * 365 < spoiled_num)
				result[counter++] = arr[i];
		}
	}

	return result;
}