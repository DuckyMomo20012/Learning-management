#include "Point.h"

Point::Point(const Point& other) {
	_x = other._x;
	_y = other._y;
	_content = other._content;
}

Point& Point::operator= (const Point& other) {
	_x = other._x;
	_y = other._y;
	_content = other._content;
	return *this;
}

void Point::goTo(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor); // DI CHUYEN 
}

void Point::goTo() {
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = _x;
	Cursor.Y = _y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor); // DI CHUYEN 
}

void Point::setPointerTo() {
	goTo(_x - 1, _y);
}

string Point::controlConsoleInput(unsigned ignoreSpace, unsigned max_size) {
	if (_content.empty()) _content.push_back("");
	goTo(_x + ignoreSpace + _content[0].size(), _y);
	while (1) {
		char type = _getch();
		if ((_content[0].size() < max_size) && (type >= 47 && type <= 122)) {
			goTo(_x + ignoreSpace + _content[0].size(), _y);
			cout << type;
			_content[0].push_back(type);
		}
		else if (8 == type && _content.size() > 0) {
			_content[0].pop_back();
			goTo(_x + ignoreSpace + _content[0].size(), _y);
			cout << " ";
			goTo(_x + ignoreSpace + _content[0].size(), _y);
		}
		else if (27 == type) {
			clearPrintedContent();
			break;
		}
		else if (13 == type) {
			break;
		}
	}
	return _content[0];
}

void Point::clearPrintedContent() {
	for (unsigned i = 0; i < _content.size(); i++) {
		for (unsigned j = 0; j < _content[i].size(); j++) {
			goTo(_x + j, _y + i);
			cout << " ";
		}
	}
	goTo(_x, _y);
	_content.clear();
	_content.push_back("");
}

void Point::print() {
	for (unsigned i = 0; i < _content.size(); i++) {
		goTo(_x, _y + i);
		cout << _content[i];
	}
}

bool Point::operator==(const Point& obj) {
	return (_x == obj._x) && (_y == obj._y);
}