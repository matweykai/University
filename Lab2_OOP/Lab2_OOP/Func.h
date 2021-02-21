#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "TeacherDataBase.h"
#include <stdio.h>
#include <iostream>
#include <list>
#include <string>

#define BUFFERSIZE 25

using namespace std;

char* read_str(FILE* source);
void print_line(int size, int adding_count);
int get_word_from_list(list<string>* lst);
char to_lower(char sym);
char to_upper(char sym);
bool is_end(FILE* file);