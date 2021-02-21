#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <list>
#include <string>
#include "FullName.h"
#include "TeacherDataBase.h"
#include "Func.h"

using namespace std;

class Teacher
{
	static list<string>* dep_list;
	static list<string>* status_list;
	static int count;

	int department;
	int status;
	FullName* fullname;

public:
	Teacher();
	Teacher(char* name, char* surname, char* second_name, int department, int status);
	Teacher(const Teacher& teacher);

	static void set_dep_list(list<string>* dep_list);
	static void set_status_list(list<string>* status_list);
	char* get_status();
	char* get_department();
	FullName* get_fullname();
	static list<string>* get_dep_list();
	static list<string>* get_status_list();
	int static get_count();
	void swap(Teacher*);

	friend class TeacherDataBase;

	~Teacher();
};

class TeacherDataBase
{
	Teacher* arr;
	string file_path;

	void dump_obj(FILE* source, Teacher* obj);
	void dump_db();
	Teacher* load_object(FILE* file);
	void download_db();
	Teacher* copy_arr();

public:

	TeacherDataBase(string file_path);
	Teacher* get_arr();
	Teacher* find_teacher(FullName fullname);
	Teacher* sorted_list();
	Teacher* filter_by_status(int status, int* founded);
	void add_teacher(Teacher* teacher);
	~TeacherDataBase();
};

int max_size(Teacher* arr, int size = -1);