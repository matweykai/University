#pragma once
class FullName 
{
	char* name;
	char* surname;
	char* second_name;

public:
	FullName(char* name, char* surname, char* second_name);
	
	char* get_name();
	char* get_surname();
	char* get_second_name();

	~FullName();
};