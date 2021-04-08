#pragma once
#include "FoodDataBase.h"
#include <algorithm>

Food* find_by_date(deque<Food> arr, Date date);
deque<Food> sort_by_price(deque<Food> arr);