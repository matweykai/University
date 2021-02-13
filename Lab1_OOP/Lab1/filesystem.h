#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "teacher.h"
#include <string>
#include <iostream>	
#include "functions.h"
#include <conio.h>

using namespace std;


Teacher* load_object(FILE*);
Teacher* download_db(string, int*);
void dump_obj(FILE*, Teacher*);
void dump_db(string, Teacher*, int);