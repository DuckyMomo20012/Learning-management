#pragma once
#include <iostream>
#include <sstream>
#include "Support/Address.h"
#include "Support/Date.h"
using namespace std;

class Person {
private:
	string _id, _name, _tel, _email;
	Address _address;
	Date _DOB;
public:
	Person() : _id(""), _name(""), _tel(""), _email("") {}
	explicit Person(string value);
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
	Student() : Person(), _schoolYear(""), _department("") {}
	Student(string value) : Person(value) {
		vector<string> _store(Tokenizer::split(value, "(", ")"));
		try {
			setSchoolYear(_store[6]);
			setDepartment(_store[7]);
		}
		catch (...) {
			cout << "Invalid string format" << endl;
		}
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
	Prof(string value) : Person(value) {}
};

