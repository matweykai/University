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
char* FullName::get_name() { return name; }
char* FullName::get_surname() { return surname; }
char* FullName::get_second_name() { return second_name; }