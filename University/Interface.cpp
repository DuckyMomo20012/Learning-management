#include "Interface.h"

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

void Interface::loadButton(const char* fileName, unordered_map <int, Point>& _store) {
	fstream file;
	file.open(fileName);
	if (file.fail()) cout << "Failed to open file" << endl;
	else {
		int i = -1;
		while (!file.eof()) {
			string temp;
			getline(file, temp);
			vector<string> split(Tokenizer::split(temp, " "));
			Point locate(stoi(split[1]), stoi(split[2]));
			_store.insert(make_pair(++i, locate));
		}
	}
	file.close();
}

void Interface::loadStu() {
	fstream file;
	string temp;
	file.open("Stu.txt");
	if (file.fail()) cout << "Failed to open file" << endl;
	else {
		while (!file.eof()) {
			getline(file, temp);
			if (temp != "") {
				Student student(temp);
				_state._allStu.insert(make_pair(stoi(student.Id()), student));
				++_state._countStu;
			}
		}
	}
	file.close();
}

void Interface::loadProf() {
	fstream file;
	string temp;
	file.open("Prof.txt");
	if (file.fail()) cout << "Failed to open file" << endl;
	else {
		while (!file.eof()) {
			getline(file, temp);
			if (temp != "") {
				Prof prof(temp);
				_state._allProf.insert(make_pair(stoi(prof.Id()), prof));
				++_state._countProf;
			}
		}
	}
	file.close();
}

void Interface::drawMenuPanel() {
	goTo(_menu[INFO].X(), _menu[INFO].Y());
	cout << "INFO";
	goTo(_menu[SCHEDULE].X(), _menu[SCHEDULE].Y());
	cout << "SCHEDULE";
	goTo(_menu[TRANSCRIPT].X(), _menu[TRANSCRIPT].Y());
	cout << "TRANSCRIPT";
	goTo(_menu[TEST].X(), _menu[TEST].Y());
	cout << "TEST";
	goTo(_menu[ENROLL].X(), _menu[ENROLL].Y());
	cout << "ENROLL";
}

void Interface::showStudentInfo(string id) {
	drawMenuPanel();
	loadButton("InfoButton.txt", _button);
	auto it = _state._allStu.find(stoi(id));
	Student temp = it->second;
	goTo(_button[0].X(), _button[0].Y());
	cout << "ID: " << temp.Id();
	goTo(_button[1].X(), _button[1].Y());
	cout << "NAME: " << temp.Name();
	goTo(_button[2].X(), _button[2].Y());
	cout << "DOB: " << temp.DOB().showDate();
	goTo(_button[3].X(), _button[3].Y());
	cout << "EMAIL: " << temp.Email();
	goTo(_button[4].X(), _button[4].Y());
	cout << "TELEPHONE: " << temp.Tel();
	goTo(_button[5].X(), _button[5].Y());
	cout << "ADDRESS: " << temp.getAddress().showFullAddress();
	goTo(_button[6].X(), _button[6].Y());
	cout << "SCHOOLYEAR: " << temp.SchoolYear();
	goTo(_button[7].X(), _button[7].Y());
	cout << "DEPARTMENT: " << temp.Department();
}