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
			vector <int> shiftAmount; //so ca hoc trong mot ngay
			for (auto it2 : it["shift"]) {
				shiftAmount.push_back(it2);
			}
			_time.insert(make_pair(it["weekday"], shiftAmount));
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