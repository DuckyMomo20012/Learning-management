#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Person.h"
#include "Support/Tokenizer.h"
using namespace std;

class Course {
private:
	string _id, _name;
public:
	Course() : _id(""), _name("") {}
	Course(string id, string name) : _id(id), _name(name) {}
	Course(string value);
};