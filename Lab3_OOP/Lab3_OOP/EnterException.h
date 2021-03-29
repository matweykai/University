#include <string>
#include <iostream>

class EnterException 
{
	std::string msg;

public:
	EnterException(std::string msg) 
	{
		this->msg = msg;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.clear();
	}
	std::string get_msg() { return msg; }
};