#include "Course.h"

Course::Course(const json& info) {
	setId(info["id"]);
	setName(info["name"]);
	if (info.contains("point") && (info["point"].size() > 0)) {
		for (auto it : info["point"]) {
			_point.push_back(it);
		}
	}
	if (info["time"].size() > 0) {
		for (auto it : info["time"]) {
			_time.insert(make_pair(it["weekday"], it["shift"]));
		}
	}
}
// Chua test!!!!!
void Course::setPoint(const int& value, const int& pos) {
	try {
		if ((unsigned)value < _point.size()) throw "invalid index!!!";
		else {
			_point[pos] = value;
		}
	}
	catch (const char*& msg) {
		cout << msg << endl;
	}
}