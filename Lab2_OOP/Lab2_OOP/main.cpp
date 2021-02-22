#include "FullName.h"
#include "TeacherDataBase.h"
#include <iostream>
#include "Func.h"
#include <fstream>
#include <windows.h>
#include "menu.h"


int main() 
{
	//Configuring console
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	//Configuring app
	string file_path = "db.bin";

	TeacherDataBase* db = new TeacherDataBase(file_path);
	
	list<string>* status_list = new list<string>();
	list<string>* dep_list = new list<string>();

	dep_list->push_back(string("иповс"));
	dep_list->push_back(string("вм"));
	dep_list->push_back(string("вт"));

	status_list->push_back(string("преподаватель"));
	status_list->push_back(string("доцент"));
	status_list->push_back(string("доктор наук"));

	Teacher::set_dep_list(dep_list);
	Teacher::set_status_list(status_list);
	//Starting app
	start_menu(db);

	delete db;

	return 0;
}