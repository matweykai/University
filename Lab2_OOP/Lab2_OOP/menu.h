#pragma once
#include "TeacherDataBase.h"
#include "Func.h"
#include <iostream>
#include <conio.h>

using namespace std;

void start_menu(TeacherDataBase*);
void show_table(Teacher*, int = -1);
void add_record(TeacherDataBase*);
void find_teacher(TeacherDataBase*);
void find_by_status(TeacherDataBase*);
void sort_by_fio(TeacherDataBase*);