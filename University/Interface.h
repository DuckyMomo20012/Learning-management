#pragma once
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include "Console.h"
#include "Person.h"
#include "Course.h"
#include "json.hpp"
#include "Support/Tokenizer.h"
using namespace std;

using json = nlohmann::json;

class Point {
private:
	int _x, _y;
public:
	Point() : _x(0), _y(0) {}
	Point(int x, int y) : _x(x), _y(y) {}
public:
	int X() { return _x; }
	void setX(int value) { _x = value; }
	int Y() { return _y; }
	void setY(int value) { _y = value; }
};

enum Menu {
	INFO,
	SCHEDULE,
	TRANSCRIPT,
	TEST,
	ENROLL
};

class State {
private:
	unordered_map<string, Student*> _allStu;
	unordered_map<string, Prof*> _allProf;
	unordered_map<string, Course*> _allCourse;
	unordered_map<int, vector<Point*>> _allButton;
	friend class Interface;
public:
	State() {}
	~State();
	State(const State& other);
	State& operator= (const State& other);
public:
	void loadAllStudent(const char* fileName);
	void loadAllButton(const char* fileName);
};

class Interface {
private:
	State _state;
public:
	Interface() {
		_state.loadAllButton("Button.json");
		_state.loadAllStudent("Student.json");
	}
	void drawInfoPanel(string id);
};
