#pragma once
#include "functions.h"

class TeacherDataBase 
{
	Teacher* arr;
	
	//Filesystem methods
	void dump_obj(FILE* source, Teacher* obj);
	void dump_db(string file_name);
	Teacher* load_object(FILE* file);
	void download_db(string file_name);
	
public:
	TeacherDataBase(string file_path);

	Teacher* find_by_fio(Teacher* teachers, int size, char* fio);
	Teacher* filter_by_status(Teacher* base, int size, int status, int* found);
	Teacher* sort(Teacher* base, int size);
	void add_record(Teacher* obj);

	~TeacherDataBase();
};