#include "Teacher.h"

int Teacher::count = 0;
list<string>* Teacher::dep_list = nullptr;
list<string>* Teacher::status_list = nullptr;

Teacher::Teacher(char* name, char* surname, char* second_name, int department, int status)
{
	this->department = department;
	this->status = status;
	this->fullname = new FullName(name, surname, second_name);
	count++;
}
Teacher::~Teacher() 
{
	delete fullname;
	count--;
}
void Teacher::set_dep_list(list<string>* dep_list)
{
	if(dep_list != nullptr)
		this->dep_list = dep_list;
}
void Teacher::set_status_list(list<string>* status_list)
{
	if(status_list != nullptr)
		this->status_list = status_list;
}
list<string>* Teacher::get_dep_list() { return dep_list; }
list<string>* Teacher::get_status_list() { return status_list; }
int Teacher::get_count() 
{
	return count;
}