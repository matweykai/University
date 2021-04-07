#pragma once

enum MonthDay
{
	JAN_DAY = 31,
	FEB_DAY = 28,
	MAR_DAY = 31,
	APR_DAY = 30,
	MAY_DAY = 31,
	JUN_DAY = 30,
	JUL_DAY = 31,
	AUG_DAY = 31,
	SEP_DAY = 30,
	OCT_DAY = 31,
	NOV_DAY = 30,
	DEC_DAY = 31
};
enum Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

class Date
{
	int day;
	int month;
	int year;

	void check_enter(int day, int month, int year);
public:
	Date(int day, int month, int year);

	int get_day();
	int get_month();
	int get_year();
	bool operator ==(const Date& obj2);
	bool operator >(const Date& right);
	bool operator <(const Date& right);
};
class DateException
{
	const char* str;
public:
	DateException(const char* str);
	const char* get_str();
};
bool is_leap(int year);