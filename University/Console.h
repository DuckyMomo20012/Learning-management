#pragma once
#include <Windows.h>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
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

class Button {
private:
	unordered_map <string, Point> _store;
	friend class Interface;
public:
	Button() {
		loadButton();
	}
public:
	Point operator[] (string i);
	pair<string, Point> operator[] (int i);
	void loadButton();
};

class Interface {
private:
	Button _button;
public:
	Interface() {
		resizeConsole(600, 500);
	}
public:
	void resizeConsole(int width, int height);
	void goTo(int x, int y);
	void drawMenuPanel();
};
