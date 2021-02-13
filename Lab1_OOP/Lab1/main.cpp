#include "functions.h"
#include <iostream>
#include "menu.h"
#include <string>
#include <windows.h>
#include "filesystem.h"

using namespace std;

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Teacher* teacher = nullptr;
	int size = 0;

	//You can add any positions you want
	list<string>* dep_list = new list<string>();
	list<string>* status_list = new list<string>();

	dep_list->push_back(string("иповс"));
	dep_list->push_back(string("вм"));
	dep_list->push_back(string("вт"));

	status_list->push_back(string("преподаватель"));
	status_list->push_back(string("доцент"));
	status_list->push_back(string("доктор наук"));

	teacher = download_db("db.txt", &size);

	teacher = start_menu(teacher, &size, dep_list, status_list);

	dump_db("db.txt", teacher, size);

	del_teachers(teacher, size);

	return 0;
}