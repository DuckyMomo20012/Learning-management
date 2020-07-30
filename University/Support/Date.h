#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class Date {
private:
	int _day, _month, _year;
public:
	Date() : _day(1), _month(1), _year(1900) {}
	Date(int day, int month, int year);
public:
	int Day() { return _day; }
	void setDay(int value) { _day = value; }
	int Month() { return _month; }
	void setMonth(int value) { _month = value; };
	int Year() { return _year; }
	void setYear(int value) { _year = value; }
public:
	bool isLeapYear(int year);
	bool isValidDate(int day, int month, int year);
	string showDate();
};
