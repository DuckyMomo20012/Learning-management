#include "Interface.h"

State& State::operator= (const State& other) {
	_user = other._user;
	_exitFlag = other._exitFlag;
	_menuTable = other._menuTable;
	return *this;
}

State::~State() {
	delete _user;
	delete _menuTable;
}

void State::initializeMenuTable() {
	_menuTable->getTable()[0][0]->setContent("INFO");
	_menuTable->getTable()[0][1]->setContent("SHCEDULE");
	_menuTable->getTable()[0][2]->setContent("TRANSCRIPT");
	_menuTable->getTable()[0][3]->setContent("ENROLL");
	_menuTable->getTable()[0][4]->setContent("EXIT");
	_menuTable->beautifyTable();
}

void MainPage::initializePage() {
	Table* test = getStateIPage()->getMenuTable();
	setIPageTable(test);
}

void MainPage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->Col() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::Exit());
		setStateIPage(tempState);
	}
}

void InfoPage::initializePage() {
	system("cls");
	Table* infoPage = new Table(3, 3, 6, 1, 2, 4);
	infoPage->getTable()[0][0]->setContent("ID: " + getStateIPage()->User()->Id());
	infoPage->getTable()[1][0]->setContent("NAME: " + getStateIPage()->User()->Name());
	infoPage->getTable()[2][0]->setContent("D.O.B: " + getStateIPage()->User()->DOB());
	infoPage->getTable()[3][0]->setContent("TELEPHONE: " + getStateIPage()->User()->Tel());
	infoPage->getTable()[4][0]->setContent("EMAIL: " + getStateIPage()->User()->Email());
	infoPage->getTable()[5][0]->setContent("ADDRESS: " + getStateIPage()->User()->getAddress());
	infoPage->insertAbove(*getStateIPage()->getMenuTable());
	infoPage->beautifyTable();
	setIPageTable(infoPage);
}

void InfoPage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->Col() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::Exit());
		setStateIPage(tempState);
	}
}

void SchedulePage::initializePage() {
	system("cls");
	vector <string> weekday = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY" };
	Table* schedulePage(new Table(3, 3, 5, 6, 2, 2));
	schedulePage->getTable()[0][0]->setContent("SHIFT");
	schedulePage->getTable()[1][0]->setContent("1");
	schedulePage->getTable()[2][0]->setContent("2");
	schedulePage->getTable()[3][0]->setContent("3");
	schedulePage->getTable()[4][0]->setContent("4");
	for (int i = 1; i < 6; i++) {
		schedulePage->getTable()[0][i]->setContent(weekday[i - 1]);
		for (auto it : getStateIPage()->User()->getCourse()) {
			map<string, int> time = it->Time();
			if (time.find(weekday[i - 1]) != time.end()) {
				int shift = it->Time()[weekday[i - 1]];
				schedulePage->getTable()[shift][i]->setContent(it->Name());
			}
		}
	}
	schedulePage->insertAbove(*getStateIPage()->getMenuTable());
	schedulePage->beautifyTable();
	setIPageTable(schedulePage);
}

void SchedulePage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->getTable()[0].size() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::Exit());
		setStateIPage(tempState);
	}
}

IPage* Factory::clone(Point* locate, State* state) {
	IPage* newPage = NULL;
	if (locate->X() == 0 && locate->Y() == 0) {
		newPage = new InfoPage(state);
	}
	else if (locate->X() == 0 && locate->Y() == 1) {
		newPage = new SchedulePage(state);
	}
	else if (locate->X() == 0 && locate->Y() == 2) {
		// transcript page
	}
	else if (locate->X() == 0 && locate->Y() == 3) {
		// enroll page
	}
	return newPage;
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

void Interface::Login() {
	Point textBox(20, 10);
	Point loginTextBox(29, 10);
	Point errorTextBox(29, 11);
	bool flag = false;
	ifstream file("Student.json", ios::in);
	if (file.fail()) cout << "Cannot open file!" << endl;
	else {
		textBox >> "NHAP ID:";
		cout << textBox;
		json allStudent = json::array();
		file >> allStudent;
		while (flag == false) {
			string id = loginTextBox.controlConsoleInput(20);
			for (unsigned i = 0; i < allStudent.size(); i++) {
				if (allStudent[i]["id"] == id) {
					flag = true;
					if (!errorTextBox.isEmpty()) errorTextBox.clearPrintedContent();
					State* temp = new State();
					temp->setStudent(new Student(allStudent[i]));
					setState(temp);
					break;
				}
				else {
					loginTextBox.clearPrintedContent();
					errorTextBox >> "Can't find this id";
					cout << errorTextBox;
				}
			}
		}
	}
	file.close();
	system("cls");
}

bool Interface::Exit() {
	Point warningTextCoordinate(2, 1);
	warningTextCoordinate >> "Do you want to exit? ";
	cout << warningTextCoordinate;
	Point confirmTableCoordinate(25, 1);
	Table confirmTable(2, 2, 1, 2, 1, 2);
	confirmTable.getTable()[0][0]->setContent("Y");
	confirmTable.getTable()[0][1]->setContent("N");
	cout << *confirmTable.getTable()[0][0];
	cout << *confirmTable.getTable()[0][1];
	Point* confirm = confirmTable.moveWithinTable();
	warningTextCoordinate.clearPrintedContent();
	confirmTable.getTable()[0][0]->clearPrintedContent();
	confirmTable.getTable()[0][1]->clearPrintedContent();
	if (0 == confirm->Y()) return true;
	else return false;
}

void Interface::run() {
	Login();
	State* temp = getState();
	pushBackNewPage(new MainPage(getState()));
	while (getState()->ExitFlag() == false) {
		system("cls");
		getCare().getCurrentPage()->getIPageTable()->showTableContent();
		Point* locate = getCare().getCurrentPage()->getIPageTable()->moveWithinTable();
		IPage* newPage = Factory::clone(locate, getState());
		if (newPage != NULL && newPage != getCare().getCurrentPage()) {
			_care.push_back(newPage);
		}
		else _care.getCurrentPage()->executeFunction(locate);
	}
}