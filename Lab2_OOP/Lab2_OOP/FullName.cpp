#include "FullName.h"

FullName::FullName(char* name, char* surname, char* second_name)
{
		this->name = name;
		this->surname = surname;
		this->second_name = second_name;
}
FullName::~FullName()
{
	delete name;
	delete surname;
	delete second_name;
}
FullName::FullName(const FullName& fullname) 
{
	this->name = new char[strlen(fullname.name) + 1];
	for (int i = 0; i < strlen(fullname.name) + 1; i++)
		this->name[i] = fullname.name[i];

	this->surname = new char[strlen(fullname.surname) + 1];
	for (int i = 0; i < strlen(fullname.surname) + 1; i++)
		this->surname[i] = fullname.surname[i];

	this->second_name = new char[strlen(fullname.second_name) + 1];
	for (int i = 0; i < strlen(fullname.second_name) + 1; i++)
		this->second_name[i] = fullname.second_name[i];
}
char* FullName::get_name() { return name; }
char* FullName::get_surname() { return surname; }
char* FullName::get_second_name() { return second_name; }