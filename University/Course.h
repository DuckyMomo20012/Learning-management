#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

class Course {
private:
	string _id, _name;
	vector<int> _point;
	map<string, int> _time;
public:
	Course() : _id(""), _name("") {}
	Course(string id, string name) : _id(id), _name(name) {}
	Course(const json& info);
public:
	string Id() { return _id; }
	void setId(string value) { _id = value; }
	string Name() { return _name; }
	void setName(string value) { _name = value; }
	vector<int> Point() { return _point; }
	void setPoint(vector <int> value) { _point = value; }
	void setPoint(const int& value, const int& pos);
	map<string, int> Time() { return _time; }
	void setTime(map<string, int> value) { _time = value; }
 };