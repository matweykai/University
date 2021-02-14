#pragma once
#include <stdio.h>
#include "Teacher.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

char* read_str(FILE* source);
int max_size(Teacher* arr);
void print_line(int size, int adding_count = 0);
int get_word_from_list(list<string>* lst);
char to_lower(char sym);
char to_upper(char sym);
