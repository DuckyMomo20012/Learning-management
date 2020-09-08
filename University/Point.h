#pragma once
#include <string>
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

class Point {
private:
	int _x, _y;
	string _content;
public:
	Point() : _x(0), _y(0), _content("") {}
	Point(int x, int y) : _x(x), _y(y) {}
	Point(int x, int y, string content) : _x(x), _y(y), _content(content) {}
	Point(const Point& other);
	Point& operator= (const Point& other);
public:
	int X() { return _x; }
	void setX(int value) { _x = value; }
	int Y() { return _y; }
	void setY(int value) { _y = value; }
	string Content() { return _content; }
	void setContent(string value) { _content = value; }
public:
	bool isEmpty() { return _content == "" ? true : false; }
	void static goTo(int x, int y);
	void goTo();
	void setPointerTo();
	string controlConsoleInput(unsigned ignoreSpace, unsigned max_size);
	void clearPrintedContent();
	friend ostream& operator<< (ostream& out, Point& object);
	void operator>> (string content);
	bool operator==(const Point& obj);
};