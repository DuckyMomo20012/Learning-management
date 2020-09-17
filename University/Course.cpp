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
	auto it1 = _time.begin();
	map<string, vector<string>> otherTime = other->Time();
	auto it2 = otherTime.begin();
	while ((it1++ != _time.end()) && (it2++ != _time.end())) {
		if (it1->first != it2->first) flagSameCourse = false;
		auto it3 = it1->second.begin();
		auto it4 = it2->second.begin();
		while ((it3 != it1->second.end()) && (it4 != it2->second.end())) {
			if (it3 != it4) flagSameCourse = false;
		}
		if (it1->second.size() != it2->second.size()) flagSameCourse = false;
	}
	if (_time.size() != otherTime.size()) flagSameCourse = false;
	return flagSameCourse;
}

bool Course::checkSameTime(Course* other) {
	auto it1 = _time.begin();
	map<string, vector<string>> otherTime = other->Time();
	auto it2 = otherTime.begin();
	while ((it1 != _time.end()) && (it2 != otherTime.end())) {
		if (it1->first == it2->first) return true;
		auto it3 = it1->second.begin();
		auto it4 = it2->second.begin();
		while ((it3 != it1->second.end()) && (it4 != it2->second.end())) {
			if (*it3 == *it4) return true;
			it3++;
			it4++;
		}
		it1++;
		it2++;
	}
	return false;
}