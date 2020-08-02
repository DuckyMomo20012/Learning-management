#pragma once
#include <Windows.h>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"
#include "Support/Tokenizer.h"
using namespace std;

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
	static int _countStu;
	static int _countProf;
private:
	unordered_map <int, Student> _allStu;
	unordered_map <int, Prof> _allProf;
	friend class Interface;
};

class Interface {
private:
	State _state;
	unordered_map <int, Point> _menu;
	unordered_map <int, Point> _button;
public:
	Interface() {
		resizeConsole(800, 500);
		loadButton("MenuButton.txt", _menu);
		loadStu();
		loadProf();
	}
public:
	void resizeConsole(int width, int height);
	void goTo(int x, int y);
	void loadButton(const char* fileName, unordered_map <int, Point>& _store);
	void loadStu();
	void loadProf();
	void drawMenuPanel();
	void showStudentInfo(string id);
};
