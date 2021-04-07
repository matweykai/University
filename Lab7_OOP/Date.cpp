#include "Date.h"

Date::Date(int day, int month, int year)
{
	check_enter(day, month, year);	//Throws an exception if something wrong

	this->day = day;
	this->month = month;
	this->year = year;
}

int Date::get_day() { return day; }
int Date::get_month() { return month; }
int Date::get_year() { return year; }

bool Date::operator==(const Date& obj2)
{
	return this->day == obj2.day
		&& this->month == obj2.month
		&& this->year == obj2.year;
}
bool Date::operator >(const Date& right)
{
	int left_sum = this->day + this->month * 31 + this->year * 12 * 31;
	int right_sum = right.day + right.month * 31 + right.year * 12 * 31;

	return left_sum > right_sum;
}
bool Date::operator <(const Date& right)
{
	int left_sum = this->day + this->month * 31 + this->year * 12 * 31;
	int right_sum = right.day + right.month * 31 + right.year * 12 * 31;

	return left_sum < right_sum;
}

DateException::DateException(const char* str)
{
	this->str = str;
}
const char* DateException::get_str() { return str; }
void Date::check_enter(int day, int month, int year)
{
	if (day <= 0)
		throw DateException("День должен быть положительным числом!");
	if (month > 12 || month < 1)
		throw DateException("Такой месяц не существует!");
	if (year <= 0)
		throw DateException("Год должен быть положительным числом!");

	switch (month)
	{
	case JANUARY:
	case MARCH:
	case MAY:
	case JULY:
	case AUGUST:
	case OCTOBER:
	case DECEMBER:
		if (day > 31 || day < 1)
			throw DateException("Неправильно введён день! Он не может быть больше 31");
		break;
	case APRIL:
	case JUNE:
	case SEPTEMBER:
	case NOVEMBER:
		if (day > 30 || day < 1)
			throw DateException("Неправильно введён день! Он не может быть больше 30");
		break;
	case FEBRUARY:
		if (is_leap(year) && day > 29)
			throw DateException("Неправильно введён день! Он не может быть больше 29");
		else if (!is_leap(year) && day > 28)
			throw DateException("Неправильно введён день! Он не может быть больше 28");
	}
}
bool is_leap(int year)
{
	if (!(year % 4) && year % 100 | !(year % 400))
		return true;
	return false;
}