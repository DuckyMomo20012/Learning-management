#pragma once
#include <iostream>
#include <sstream>
#include "Console.h"
#include "Support/Random.h"
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
	Person(string id, string name, string tel, string email, string address, string dob);
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
public:
	virtual string showInfo() = 0;
};

class Student : public Person {
private:
	string _schoolYear, _department; // department: khoa
public:
	Student() : Person(), _schoolYear(""), _department("") {}
	Student(string id, string name, string tel, string email, string address, string dob, string schoolYear, string department) 
		: Person(id, name, tel, email, address, dob)	
	{	
		_schoolYear = schoolYear;
		_department = department;
	}
public:
	string SchoolYear() { return _schoolYear; }
	void setSchoolYear(string value) { _schoolYear = value; }
	string Department() { return _department; }
	void setDepartment(string value) { _department = value; }
public:
	string showInfo() override;
};

class Prof : public Person {
private:
	
public:
	Prof() : Person() {}
	Prof(string id, string name, string tel, string email, string address, string dob)
		: Person(id, name, tel, email, address, dob) {}
};
