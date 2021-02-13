#pragma once

#include "teacher.h"
#include <iostream>
#include <list>
#include <string>
#include "functions.h"
#include <conio.h>

using namespace std;

Teacher* start_menu(Teacher*, int*, list<string>*, list<string>*);
void show_table(Teacher*, int, list<string>*, list<string>*);
Teacher* add_record(Teacher*, int*, list<string>*, list<string>*);
int max_size(Teacher*, int);
void print_line(int, int);
string get_element(list<string>*, int);
int get_word_from_list(list<string>*);
char to_lower(char);
char to_upper(char);
void find_teacher(Teacher*, int, list<string>*, list<string>*);
void find_by_status(Teacher*, int, list<string>*, list<string>*);
void sort_by_fio(Teacher*, int, list<string>*, list<string>*);
