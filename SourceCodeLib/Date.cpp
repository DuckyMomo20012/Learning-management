#include "Date.h"

Date::Date(int day, int month, int year) {
	try {
		if (!isValidDate(day, month, year)) throw "Invalid date format!!!";
		else {
			_day = day;
			_month = month;
			_year = year;
		}
	}
	catch (const char* ex) {
		*this = Date(); // Dua ve mac dinh
		cout << ex << endl;
	}
}

Date::Date(string value) {
	if (tryParseDate(value) && isValidDate(_day, _month, _year)) parseDate(value);
	try {
		if (!tryParseDate(value) && !isValidDate(_day, _month, _year)) throw "Invalid date format!!!";
		else {
			parseDate(value);
		}
	}
	catch (const char* ex) {
		*this = Date();
		cout << ex << endl;
	}
}

string Date::showDate() {
	stringstream writer;
	if (_day < 10) writer << "0";
	writer << _day << "/";
	if (_month < 10) writer << "0";
	writer << _month << "/" << _year;
	return writer.str();
}

bool Date::isLeapYear(int year) {
	return (0 == year % 4 && 0 != year % 100) || (0 == year % 400);
}

bool Date::isValidDate(int day, int month, int year) {
	bool flag = true;
	if (year < 1900) flag = false;
	else if (month < 1 || month > 12) flag = false;
	else if (day < 1 || day > 31) flag = false;
	else {
		int MaxDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (isLeapYear(year)) MaxDay[1] = 29;
		if (day > MaxDay[month - 1]) flag = false;
	}
	return flag;
}

void Date::parseDate(string value) {
	_day = stoi(value.substr(0, 2));
	_month = stoi(value.substr(3, 2));
	_year = stoi(value.substr(6, value.size() - 6));
}

bool Date::tryParseDate(string value) {
	bool flag = true;
	int day, month, year;
	try {
		day = stoi(value.substr(0, 2));
		month = stoi(value.substr(3, 2));
		year = stoi(value.substr(6, value.size() - 6));
	}
	catch(const exception& ex){
		flag = false;
		cout << "Invalid date format!!!" << endl << ex.what();
	}
	return flag;
}