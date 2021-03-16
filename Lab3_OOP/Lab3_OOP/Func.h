#pragma once
#include "FoodDataBase.h"
#include <iostream>
#include <list>

Food** copy_arr(Food** arr, int size = Food::get_food_count());
Food** sort_by_price(Food** arr);
Food* find_by_name(Food** arr, string* name);
Food** filter_by_date(Food** arr, Date date, int* found);
void show_table(Food** arr, vector<string>* types, int size = Food::get_food_count());
int max_size(Food** arr, int size = Food::get_food_count());
void print_line(int size, int adding_count = 0);