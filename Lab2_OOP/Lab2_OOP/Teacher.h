#pragma once
#include <list>
#include <string>
#include "FullName.h"

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
	Teacher(char* name, char* surname, char* second_name, int department, int status);
	Teacher(const Teacher& teacher);

	void set_dep_list(list<string>* dep_list);
	void set_status_list(list<string>* status_list);
	char* get_status();
	char* get_department();
	FullName get_fullname();
	list<string>* get_dep_list();
	list<string>* get_status_list();
	int static get_count();

	~Teacher();
};