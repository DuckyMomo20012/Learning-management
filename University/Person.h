#pragma once
#include <iostream>
#include "Course.h"
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class Person {
private:
	string _id, _name, _tel, _email,  _address, _dob;
public:
	Person() : _id(""), _name(""), _tel(""), _email(""), _address(""), _dob("") {};
	Person(const json& info);
public:
	string Id() { return _id; }
	void setId(string value) { _id = value; }
	string Name() { return _name; }
	void setName(string value) { _name = value; }
	string Telephone() { return _tel; }
	void setTelephone(string value) { _tel = value; }
	string Email() { return _email; }
	void setEmail(string value) { _email = value; }
	string Address() { return _address; }
	void setAddress(string value) { _address = value; }
	string DOB() { return _dob; }
	void setDOB(string value) { _dob = value; }
};

class Student : public Person {
private:
	string _intake, _department;
	vector<Course*> _course;
public:
	Student() : Person(), _intake(""), _department("") {};
	Student(const json& info) : Person(info) {
		setIntake(info["schoolyear"]);
		setDepartment(info["department"]);
		if (info["course"].size() > 0) {
			for (auto it : info["course"]) {
				_course.push_back(new Course(it));
			}
		}
	}
	Student(Student& other);
	Student& operator= (Student& other);
	~Student() {
		for (auto it : _course) {
			delete it;
		}
	}
public:
	string Intake() { return _intake; }
	void setIntake(string value) { _intake = value; }
	string Department() { return _department; }
	void setDepartment(string value) { _department = value; }
	vector<Course*> getCourse() { return _course; }
	void setCourse(vector<Course*> value) { _course = value; }
	void pushBackCourse(Course* value) { _course.push_back(value); }
};