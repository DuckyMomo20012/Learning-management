#include "Interface.h"

State& State::operator= (const State& other) {
	_user = other._user;
	_exitFlag = other._exitFlag;
	_goBackFlag = other._goBackFlag;
	_menuTable = other._menuTable;
	return *this;
}

State::~State() {
	delete _user;
	delete _menuTable;
}

void State::initializeMenuTable() {
	_menuTable->insertRowBelow({ "INFO", "SCHEDULE", "TRANSCRIPT", "ENROLL", "EXIT"});
}

void MainPage::initializePage() {
	Table* tempTable = getStateIPage()->getMenuTable();
	setIPageTable(tempTable);
}

void MainPage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->Col() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::YesNoQuestionBox(new Point(2, 2), "Do u want to exit?"));
		setStateIPage(tempState);
	}
}

void InfoPage::initializePage() {
	system("cls");
	Table* infoPage = new Table(3, 3, 2, 4);
	infoPage->insertRowBelow({ "ID: " + getStateIPage()->User()->Id() });
	infoPage->insertRowBelow({ "NAME: " + getStateIPage()->User()->Name() });
	infoPage->insertRowBelow({ "D.O.B: " + getStateIPage()->User()->DOB() });
	infoPage->insertRowBelow({ "TELEPHONE: " + getStateIPage()->User()->Telephone() });
	infoPage->insertRowBelow({ "EMAIL: " + getStateIPage()->User()->Email() });
	infoPage->insertRowBelow({ "ADDRESS: " + getStateIPage()->User()->getAddress() });
	infoPage->insertAbove(*getStateIPage()->getMenuTable());
	setIPageTable(infoPage);
}

void InfoPage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->Col() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::YesNoQuestionBox(new Point(2, 2), "Do u want to exit?"));
		setStateIPage(tempState);
	}
	else if (locate->X() == 2 && locate->Y() == 0) {
		State* tempState = getStateIPage();
		string editString = edit(getIPageTable()->getTable()[locate->X()][locate->Y()], "NAME: ");
		if (editString != "") {
			tempState->User()->setName(editString);
		}
		setStateIPage(tempState);
	}
	else if (locate->X() == 3 && locate->Y() == 0) {
		State* tempState = getStateIPage();
		string editString = edit(getIPageTable()->getTable()[locate->X()][locate->Y()], "D.O.B: ");
		if (editString != "") {
			tempState->User()->setDOB(editString);
		}
		setStateIPage(tempState);
	}
	else if (locate->X() == 4 && locate->Y() == 0) {
		State* tempState = getStateIPage();
		string editString = edit(getIPageTable()->getTable()[locate->X()][locate->Y()], "TELEPHONE: ");
		if (editString != "") {
			tempState->User()->setTelephone(editString);
		}
		setStateIPage(tempState);
	}
	else if (locate->X() == 5 && locate->Y() == 0) {
		State* tempState = getStateIPage();
		string editString = edit(getIPageTable()->getTable()[locate->X()][locate->Y()], "EMAIL: ");
		if (editString != "") {
			tempState->User()->setEmail(editString);
		}
		setStateIPage(tempState);
	}
	else if (locate->X() == 2 && locate->Y() == 0) {
		State* tempState = getStateIPage();
		string editString = edit(getIPageTable()->getTable()[locate->X()][locate->Y()], "ADDRESS: ");
		if (editString != "") {
			tempState->User()->setAddress(editString);
		}
		setStateIPage(tempState);
	}
	else if (locate->X() == -1 && locate->Y() == -1) {
		State* tempState = getStateIPage();
		tempState->setGoBackFlag(true);
		setStateIPage(tempState);
	}
}

string InfoPage::edit(Point*& locate, string ignoreString) {
	string editString;
	bool confirmChange = false;
	string oldContent = locate->Content();
	locate->clearPrintedContent();
	locate->setContent(ignoreString);
	cout << *locate;
	Point* editBox = new Point(locate->X() + locate->Content().size(), locate->Y());
	editString = editBox->controlConsoleInput(0, 20);
	Point* confirmBox = new Point(locate->X() + locate->Content().size() + editString.size() + 1 /*Khoang cach giua edit va confirm*/, locate->Y());
	if (editString != "") {
		confirmChange = Interface::YesNoQuestionBox(confirmBox, "Confirm? ");
	}
	if (confirmChange == false) {
		editBox->clearPrintedContent();
		locate->clearPrintedContent();
		locate->setContent(oldContent);
		cout << *locate;
		editString = "";
	}
	else {
		locate->setContent(ignoreString + editString);
	}
	delete confirmBox, editBox;
	return editString;
}

void SchedulePage::initializePage() {
	system("cls");
	vector <string> weekday = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY" };
	Table* schedulePage(new Table(3, 3, 2, 2, 5, 6));
	schedulePage->getTable()[0][0]->setContent("SHIFT");
	schedulePage->getTable()[1][0]->setContent("1");
	schedulePage->getTable()[2][0]->setContent("2");
	schedulePage->getTable()[3][0]->setContent("3");
	schedulePage->getTable()[4][0]->setContent("4");
	for (int i = 1; i < 6; i++) { // 6 ngay trong tuan
		schedulePage->getTable()[0][i]->setContent(weekday[i - 1]);
		for (auto it : getStateIPage()->User()->getCourse()) {
			map<string, vector<int>> time = it->Time();
			if (time.find(weekday[i - 1]) != time.end()) {
				for (auto shiftAmount : time[weekday[i - 1]]) { // so ca hoc trong ngay
					int shift = shiftAmount;
					schedulePage->getTable()[shift][i]->setContent(it->Name());
				}
			}
		}
	}
	schedulePage->insertAbove(*getStateIPage()->getMenuTable());
	setIPageTable(schedulePage);
}

void SchedulePage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->getTable()[0].size() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::YesNoQuestionBox(new Point(2, 2), "Do u want to exit?"));
		setStateIPage(tempState);
	}
	else if (locate->X() == -1 && locate->Y() == -1) {
		State* tempState = getStateIPage();
		tempState->setGoBackFlag(true);
		setStateIPage(tempState);
	}
}

void EnrollPage::initializePage() {
	system("cls");
}

void EnrollPage::executeFunction(Point* locate) {
	if (locate->X() == 0 && locate->Y() == getIPageTable()->Col() - 1) {
		State* tempState = getStateIPage();
		tempState->setExitFlag(Interface::YesNoQuestionBox(new Point(2, 2), "Do u want to exit?"));
		setStateIPage(tempState);
	}
}

void EnrollPage::getCourse() {
	fstream file("Course.json", ios::in);
	if (file.fail()) cout << "CANNOT OPEN FILE!!!";
	else {
		json arrayCourse = json::array();
		file >> arrayCourse;
		for (auto it : arrayCourse) {
			for (auto it2 : arrayCourse["time"]) {
				_totalSelection += it2["shift"].size();
			}
			
		}
	}
	file.close();
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

void Caretaker::push_back(IPage* other) {
	if (_history.empty())  _history.push_back(other);
	else if (other != _history.back()) _history.push_back(other);
}

void Caretaker::pop_back() {
	if (_history.size() > 1) _history.pop_back();
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

void Interface::login() {
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
			string id = loginTextBox.controlConsoleInput(0, 20);
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

bool Interface::YesNoQuestionBox(Point* locate, string sentence) {
	locate->setContent(sentence + " ");
	cout << *locate;
	Table confirmTable(locate->X() + locate->Content().size(), locate->Y(), 1, 2, 1, 2);
	confirmTable.getTable()[0][0]->setContent("Y");
	confirmTable.getTable()[0][1]->setContent("N");
	cout << *confirmTable.getTable()[0][0];
	cout << *confirmTable.getTable()[0][1];
	Point* confirm = confirmTable.moveWithinTable();
	locate->clearPrintedContent();
	confirmTable.getTable()[0][0]->clearPrintedContent();
	confirmTable.getTable()[0][1]->clearPrintedContent();
	if (0 == confirm->Y()) return true;
	else return false;
}

void Interface::run() {
	login();
	_care.push_back(new MainPage(getState()));
	while (getState()->ExitFlag() == false) {
		system("cls");
		getCare().getCurrentPage()->getIPageTable()->showTableContent();
		Point* locate = getCare().getCurrentPage()->getIPageTable()->moveWithinTable();
		IPage* newPage = Factory::clone(locate, getState());
		if (newPage != NULL && newPage != getCare().getCurrentPage()) {
			_care.push_back(newPage);
		}
		else _care.getCurrentPage()->executeFunction(locate);
		if (getState()->GoBackFlag() == true) {
			_care.pop_back();
			getState()->setGoBackFlag(false);
		}
	}
	system("cls");
}