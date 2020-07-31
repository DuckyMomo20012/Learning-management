#pragma once
#include <Windows.h>
#include <map>
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
	map <string, Point> _store;
public:
	Button() {
		loadButton();
	}
	friend class Console;
public:

	void loadButton();
};

class Console {
public:
	void resizeConsole(int width, int height);
	void goTo(int x, int y);
	void drawMenuPanel();
};
