#include "Func.h"


class Greater
{
public:
	bool operator() (Food f1, Food f2)
	{
		return f1.get_price() > f2.get_price();
	}
};

Food* find_by_date(deque<Food> arr, Date date) 
{
	deque<Food>::iterator result = find_if(arr.begin(), arr.end(), [date](Food obj) { return *obj.get_date() == date; });

	if (result != arr.end())
		return new Food(*result);
	else
		return nullptr;
}
deque<Food> sort_by_price(deque<Food> arr) 
{
	deque<Food> result;
	result.resize(arr.size());

	copy(arr.begin(), arr.end(), result.begin());

	sort(result.begin(), result.end(), Greater());

	return result;
}
