#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

class Point {
private:
	int _x, _y;
	vector <string> _content;
public:
	Point() : _x(0), _y(0), _content(1) {}
	Point(int x, int y) : _x(x), _y(y), _content(1) {}
	Point(int x, int y, string content) : _x(x), _y(y), _content(1) { _content[0] = content; }
	Point(const Point& other);
	Point& operator= (const Point& other);
public:
	int X() { return _x; }
	void setX(int value) { _x = value; }
	int Y() { return _y; }
	void setY(int value) { _y = value; }
	vector <string> Content() { return _content; }
	void setWrappedContent(vector <string> value) { _content = value; }
	void setContent(string content) { _content[0] = content; }
public:
	//bool isEmpty() { return _content == "" ? true : false; }
	void static goTo(int x, int y);
	void goTo();
	void setPointerTo();
	string controlConsoleInput(unsigned ignoreSpace, unsigned max_size);
	void clearPrintedContent();
	void print();
	bool operator==(const Point& obj);
};