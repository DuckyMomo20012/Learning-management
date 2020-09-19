#include "Person.h"

Person::Person(const json& info) {
	setId(info["id"]);
	setName(info["name"]);
	setTelephone(info["tel"]);
	setEmail(info["email"]);
	setAddress(info["address"]);
	setDOB(info["dob"]);
}

Student::Student(Student& other) {
	setId(other.Id());
	setName(other.Name());
	setTelephone(other.Telephone());
	setEmail(other.Email());
	setAddress(other.Address());
	setDOB(other.DOB());
	setIntake(other._intake);
	setDepartment(other._department);
	for (auto it : other._course) {
		this->_course.push_back(it);
	}
}

Student& Student::operator=(Student& other) {
	setId(other.Id());
	setName(other.Name());
	setTelephone(other.Telephone());
	setEmail(other.Email());
	setAddress(other.Address());
	setDOB(other.DOB());
	setIntake(other._intake);
	setDepartment(other._department);
	for (auto it : other._course) {
		this->_course.push_back(it);
	}
	return *this;
}