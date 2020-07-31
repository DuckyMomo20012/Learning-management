#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Tokenizer.h"
using namespace std;

class Address {
private:
	string	_number, _street, _ward, _district, _city;
public:
	Address() : _number(""), _ward(""), _street(""), _district(""), _city("") {}
	Address(string number, string ward, string street, string district, string city) 
	: _number(number), _ward(ward), _street(street), _district(district), _city(city) {}
	Address(string value);
public:
	void Number(string value) { _number = value; }
	string getNumber() { return _number; }
	void StreetName(string value) { _street = value; }
	string getStreetName() { return _street; }
	void WardName(string value) { _ward = value; }
	string getWardName() { return _ward; }
	void DistrictName(string value) { _district = value; }
	string getDistrictName() { return _district; }
	void CityName(string value) { _city = value; }
	string getCityName() { return _city; }
public:
	string showFullAddress();
	void parseAddress(string value);
};
