#pragma once
#include <string>
#include <iostream>
#include "Console.h"
using namespace std;

class Point {
private:
	int _x, _y;
	string _content;
public:
	Point() : _x(0), _y(0), _content("") {}
	Point(Point& other);
	Point(int x, int y) : _x(x), _y(y) {}
	Point(int x, int y, string content) : _x(x), _y(y), _content(content) {}
public:
	int X() { return _x; }
	void setX(int value) { _x = value; }
	int Y() { return _y; }
	void setY(int value) { _y = value; }
	string Content() { return _content; }
	void showContentWithCoordinate() {
		goTo(_x, _y);
		cout << _content;
	}
	void setContent(string value) { _content = value; }
	friend ostream& operator<< (ostream& os, const Point& _point);
};