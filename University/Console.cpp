#include "Console.h"

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

void Console::resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	LONG style = GetWindowLong(console, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(console, GWL_STYLE, style); // LAM MO NUT MAXIMIZE
	GetWindowRect(console, &r); // THAY DOI KICH CO CMD
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Console::goTo(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor); // DI CHUYEN 
}

void Console::drawMenuPanel() {
	cout << "HISFSDFSDFSDF";
}