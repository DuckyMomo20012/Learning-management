#include "Console.h"

Point Button::operator[] (string i) {
	try {
		if (_store.find(i) == _store.end()) throw "Invalid index";
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	return _store[i];
}

pair<string, Point> Button::operator[] (int i) {
	try {
		if ((unsigned)i > _store.size()) throw "Invalid index";
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	auto it = _store.begin(); //map iterator
	while (--i >= 0) ++it;
	pair <string, Point> p;
	p.first = it->first;
	p.second = it->second;
	return p;
}
void Button::loadButton() {
	fstream file;
	file.open("button.txt");
	while (!file.eof()) {
		string temp;
		getline(file, temp);
		vector<string> split(Tokenizer::split(temp, " "));
		Point locate(stoi(split[1]), stoi(split[2]));
		_store.insert(make_pair(split[0], locate));
	}
	file.close();
}

void Interface::resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	LONG style = GetWindowLong(console, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(console, GWL_STYLE, style); // LAM MO NUT MAXIMIZE
	GetWindowRect(console, &r); // THAY DOI KICH CO CMD
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Interface::goTo(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor); // DI CHUYEN 
}

void Interface::drawMenuPanel() {
	for (int i = 0; i < 3; i++) {
		goTo(_button[i].second.X(), _button[i].second.Y());
		cout << _button[i].first;
	}
}