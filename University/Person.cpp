#include "Person.h"

Person::Person(const json& info) {
	setId(info["id"]);
	setName(info["name"]);
	setTel(info["tel"]);
	setEmail(info["email"]);
	Address _tempAddress(info["address"]);
	setAddress(_tempAddress);
	Date _tempDOB(info["dob"]);
	setDOB(_tempDOB);
}

Student::Student(Student& other) {
	setId(other.Id());
	setName(other.Name());
	setTel(other.Tel());
	setEmail(other.Email());
	setAddress(other.getAddress());
	setDOB(other.DOB());
	setSchoolYear(other._schoolYear);
	setDepartment(other._department);
	for (auto it : other._course) {
		this->_course.push_back(it);
	}
}