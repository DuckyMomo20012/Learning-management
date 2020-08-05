#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Course.h"
#include "json.hpp"
#include "Support/Address.h"
#include "Support/Date.h"
using namespace std;

using json = nlohmann::json;

class Person {
private:
	string _id, _name, _tel, _email;
	Address _address;
	Date _DOB;
public:
	Person() : _id(""), _name(""), _tel(""), _email("") {};
	Person(string id, const json& j);
public:
	string Id() { return _id; }
	void setId(string value) { _id = value; }
	string Name() { return _name; }
	void setName(string value) { _name = value; }
	string Tel() { return _tel; }
	void setTel(string value) { _tel = value; }
	string Email() { return _email; }
	void setEmail(string value) { _email = value; }
	Address getAddress() { return _address; }
	void setAddress(Address value) { _address = value; }
	Date DOB() { return _DOB; }
	void setDOB(Date value) { _DOB = value; }
};

class Student : public Person {
private:
	string _schoolYear, _department; // department: khoa
public:
	Student() : Person(), _schoolYear(""), _department("") {};
	Student(string id, const json& j) : Person(id, j) {
		setSchoolYear(j["schoolyear"]);
		setDepartment(j["department"]);
	}
public:
	string SchoolYear() { return _schoolYear; }
	void setSchoolYear(string value) { _schoolYear = value; }
	string Department() { return _department; }
	void setDepartment(string value) { _department = value; }
public:

};

class Prof : public Person {
public:
	Prof() : Person() {}
	Prof(string id, const json& j) : Person(id, j) {};
};

