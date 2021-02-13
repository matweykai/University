#include "FullName.h"
#include "Teacher.h"
#include <iostream>

int main() 
{
	char* name = new char[] {"name"};
	char* surname = new char[] {"surname"};
	char* second_name = new char[] {"second name"};

	char* name1 = new char[] {"name1"};
	char* surname1 = new char[] {"surname1"};
	char* second_name1 = new char[] {"second name1"};

	//FullName fn(name, surname, second_name);
	//FullName fn1(fn);
	
	Teacher t(name1, surname1, second_name1, 1, 1);
	Teacher t1(t);

	int i = 1;

	return 0;
}