#pragma once
#include "FoodDataBase.h"
#include <algorithm>

deque<Food> find_by_date(deque<Food> arr, Date date);
deque<Food> sort_by_price(deque<Food> arr);
void print_line(int size, int adding_count = 0);
void show_table(deque<Food> arr);