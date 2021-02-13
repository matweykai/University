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
Teacher::Teacher(const Teacher& teacher) 
{
	this->department = teacher.department;
	this->status = teacher.status;
	this->fullname = new FullName(*teacher.fullname);
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
char* Teacher::get_department() 
{
	list<string>::iterator iter = dep_list->begin();

	for (int i = 0; i < department; i++)
		iter++;
	//Full copy
	char* result = new char[(*iter).length() + 1];
	for (int i = 0; i < (*iter).length(); i++)
		result[i] = (*iter)[i];
	result[(*iter).length()] = '\0';

	return result;
}
char* Teacher::get_status() 
{
	list<string>::iterator iter = status_list->begin();

	for (int i = 0; i < status; i++)
		iter++;
	//Full copy
	char* result = new char[(*iter).length() + 1];
	for (int i = 0; i < (*iter).length(); i++)
		result[i] = (*iter)[i];
	result[(*iter).length()] = '\0';

	return result;
}
FullName Teacher::get_fullname() { return FullName(*fullname); }