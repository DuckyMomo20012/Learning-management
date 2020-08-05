#include "Person.h"

Person::Person(string id, const json& j) {
	setId(id);
	setName(j["name"]);
	setTel(j["tel"]);
	setEmail(j["email"]);
	Address _tempAddress(j["address"]);
	setAddress(_tempAddress);
	Date _tempDOB(j["dob"]);
	setDOB(_tempDOB);
}