#include "Func.h"

Food* find_by_date(deque<Food> arr, Date date) 
{
	for (deque<Food>::iterator iter = arr.begin(); iter < arr.end(); iter++)
		if (*iter->get_date() == date)
			return new Food(*iter);

	return nullptr;
}
deque<Food> sort_by_price(deque<Food> arr) 
{
	deque<Food> result;
	
	int size = arr.size();

	for (int i = 0; i < size; i++)
	{
		deque<Food>::iterator max = arr.begin();
		for (deque<Food>::iterator iter = arr.begin(); iter < arr.end(); iter++)
			if (iter->get_price() > max->get_price())
				max = iter;
		
		result.push_back(*max);
		arr.erase(max);
	}

	return result;
}