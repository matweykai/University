#pragma once
#include "teacher.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

Teacher* find_by_fio(Teacher*, int, char*);
Teacher* filter_by_status(Teacher*, int, int, int*);
Teacher* sort(Teacher*, int);
Teacher* copy(Teacher*, int);
void del_teachers(Teacher*, int);
char* read_str(FILE*);
bool is_end(FILE* file);