#include "Course.h"

Course::Course(const json& info) {
	setId(info["id"]);
	setName(info["name"]);
	if (info.contains("point") && (info["point"].size() > 0)) {
		for (auto it : info["point"]) {
			vector <int> temp;
			for (auto it2 : it) {
				temp.push_back(it2);
			}
			_point.push_back(temp);
		}
	}
	if (info["time"].size() > 0) {
		for (auto it : info["time"]) {
			vector <string> shiftAmount; //so ca hoc trong mot ngay
			for (auto it2 : it["shift"]) {
				shiftAmount.push_back(it2);
			}
			_time.insert(make_pair(it["weekday"], shiftAmount));
		}
	}
}

bool Course::operator==(Course* other) {
	bool flagSameCourse = true;
	if (_id != other->Id()) {
		flagSameCourse = false;
	}
	if (_name != other->Id()) {
		flagSameCourse = false;
	}
	if (checkSameTime(other) == false) {
		flagSameCourse = false;
	}
	return flagSameCourse;
}

bool Course::checkSameTime(Course* other) {
	auto it1 = _time.begin();
	map<string, vector<string>> otherTime = other->Time();
	auto it2 = otherTime.begin();
	while (it2 != otherTime.end()) {
		if (_time.find(it2->first) != _time.end()) {
			vector <string> timeShift = _time[it2->first];
			vector <string> otherShift = it2->second;
			sort(timeShift.begin(), timeShift.end());
			sort(otherShift.begin(), otherShift.end());
			int n = max(timeShift.size(), otherShift.size());
			for (int i = 0; i < n; i++) {
				if (timeShift[i] == otherShift[i]) return true;
			}
		}
		it2++;
	}
	return false;
}