#include "Course.h"

Course::Course(string id, const json& info) {
	setId(info["id"]);
	setName(info["name"]);
	if (info["point"].size() > 0) {
		for (auto it : info["point"]) {
			_point.push_back(it);
		}
	}
}

void Course::setPoint(const int& value, const int& pos) {
	try {
		if (value < _point.size()) throw "invalid index!!!";
		else {
			_point[pos] = value;
		}
	}
	catch (const char*& msg) {
		cout << msg << endl;
	}
}