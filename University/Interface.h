#pragma once
#include <unordered_set>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "Console.h"
#include "Person.h"
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
	unordered_set<Student*> _allStu;
	unordered_set <Prof*> _allProf;
	friend class Interface;
public:
	State() {}
	~State();
	State(const State& other);
	State& operator= (const State& other);
public:
	void loadStu(const char* fileName);
};

class Interface {
private:
	State _state;
	unordered_set <Point*> _menu;
public:
	Interface() {
	}
	void load (const char* fileName){
		_state.loadStu(fileName);
	}
};
