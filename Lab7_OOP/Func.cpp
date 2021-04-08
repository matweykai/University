#include "Func.h"


class Greater
{
public:
	bool operator() (Food f1, Food f2)
	{
		return f1.get_price() > f2.get_price();
	}
};

deque<Food> find_by_date(deque<Food> arr, Date date) 
{
	deque<Food>::iterator temp_obj = find_if(arr.begin(), arr.end(), [date](Food obj) { return *obj.get_date() == date; });

	deque<Food> result;

	while (temp_obj != arr.end())
	{
		result.push_back(*temp_obj);
		temp_obj++;
		temp_obj = find_if(temp_obj, arr.end(), [date](Food obj) { return *obj.get_date() == date; });
	}

	return result;
}
deque<Food> sort_by_price(deque<Food> arr) 
{
	deque<Food> result;
	result.resize(arr.size());

	copy(arr.begin(), arr.end(), result.begin());

	sort(result.begin(), result.end(), Greater());

	return result;
}
void print_line(int size, int adding_count)
{
	for (int i = 0; i < size + adding_count; i++)
		cout << "-";
}
void show_table(deque<Food> arr)
{
	cout.setf(ios::left);
	cout.width(Food::get_maxLen() + NAME_SPACE);
	cout << "Название";
	cout.width(PRICE_S);
	cout << "Цена";
	cout.width(DATE_S);
	cout << "Дата" << endl;
	

	print_line(Food::get_maxLen() + DATE_S + PRICE_S + NAME_SPACE, 2);
	cout << endl;

	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << endl;
	}

	print_line(Food::get_maxLen() + DATE_S + PRICE_S + NAME_SPACE, 2);
	cout << endl;
}