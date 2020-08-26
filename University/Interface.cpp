#include "Interface.h"

State::State(const State& other) {
	_user = other._user;
}

State& State::operator= (const State& other) {
	_user = other._user;
	return *this;
}

State::~State() {
	delete _user;
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

bool Interface::moveWithinGridAndExecuteFunction(Grid& _grid) {
	unsigned row = 0, col = 0;
	//goTo(_grid[row][col]->X() - 1, _grid[row][col]->Y());
	_grid[0][0]->setPointerTo();
	bool flagContinue = true;
	bool flagGoBack = false;
	while (flagContinue) {
		switch (toupper(_getch())) {
		case 'W': {
			if (row > 0 && _grid[row - 1].size() > col) {
				//goTo(_grid[row - 1][col]->X() - 1, _grid[row - 1][col]->Y());
				_grid[--row][col]->setPointerTo();
			}
			break;
		}
		case 'S': {
			if (row < (unsigned)_grid.Row() - 1 && _grid[row + 1].size() > col) {
				//goTo(_grid[row + 1][col]->X() - 1, _grid[row + 1][col]->Y());
				_grid[++row][col]->setPointerTo();
			}
			break;
		}
		case 'A': {
			if (col > 0) {
				//goTo(_grid[row][col - 1]->X() - 1, _grid[row][col - 1]->Y());
				_grid[row][--col]->setPointerTo();
			}
			break;
		}
		case 'D': {
			if (col < _grid[row].size() - 1) {
				//goTo(_grid[row][col + 1]->X() - 1, _grid[row][col + 1]->Y());
				_grid[row][++col]->setPointerTo();
			}
			break;
		}
		case 8: {
			flagGoBack = true;
			break;
		}
		case 27: {
			flagContinue = !confirmExit();
			if (flagContinue == true) {
				_grid[row][col]->setPointerTo();
			}
			break;
		}
		case 13: {
			if (_command.find(_grid[row][col]) != _command.end())
			{
				(this->*_command[_grid[row][col]])();
				_trackProgress.push_back(_grid[row][col]);
			}
			else if (_grid[row][col] == _state._menuPage[0][4]) {
				flagContinue = !confirmExit();
				if (flagContinue == true) _grid[row][col]->setPointerTo();
			}
			break;
		}
		}
	}
	return flagGoBack;
}

Point Interface::moveWithinGrid(Grid& _grid) {
	unsigned row = 0, col = 0;
	_grid[0][0]->setPointerTo();
	bool flagContinue = true;
	while (flagContinue) {
		switch (toupper(_getch())) {
		case 'W': {
			if (row > 0 && _grid[row - 1].size() > col) {
				_grid[--row][col]->setPointerTo();
			}
			break;
		}
		case 'S': {
			if (row < (unsigned)_grid.Row() - 1 && _grid[row + 1].size() > col) {
				_grid[++row][col]->setPointerTo();
			}
			break;
		}
		case 'A': {
			if (col > 0) {
				_grid[row][--col]->setPointerTo();
			}
			break;
		}
		case 'D': {
			if (col < _grid[row].size() - 1) {
				_grid[row][++col]->setPointerTo();
			}
			break;
		}
		case 13: {
			flagContinue = false;
			break;
		}
		}
	}
	return *_grid[row][col];
}

void Interface::loginPage() {
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
					_state._user = new Student(allStudent[i]);
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
	if (flag == true) menuPage();
}

void Interface::menuPage() {
	system("cls");
	_state._menuPage = Grid(1, 5, 2, 4);
	Point menuPageCoordinate(2, 2);
	_state._menuPage.createGrid(menuPageCoordinate);
	_state._menuPage[0][0]->setContent("INFO");
	_state._menuPage[0][1]->setContent("SCHEDULE");
	_state._menuPage[0][2]->setContent("TRANSCRIPT");
	_state._menuPage[0][3]->setContent("ENROLL");
	_state._menuPage[0][4]->setContent("EXIT");
	_state._menuPage.beautifyGrid();
	void (Interface:: * infoCommand)() = &Interface::infoPage;
	_command.insert(make_pair(_state._menuPage[0][0], infoCommand));
	void (Interface:: * scheduleCommand)() = &Interface::schedulePage;
	_command.insert(make_pair(_state._menuPage[0][1], scheduleCommand));
	_state._menuPage.showContentFullGrid();
	moveWithinGridAndExecuteFunction(_state._menuPage);
}

void Interface::infoPage() {
	bool flagContinue = true;
	while (flagContinue) {
		system("cls");
		Grid infoPage(7, 1, 2, 4);
		Point infoPageCoordinate(3, 3);
		infoPage.createGrid(infoPageCoordinate);
		infoPage[0][0]->setContent("ID: " + _state._user->Id());
		infoPage[1][0]->setContent("NAME: " + _state._user->Name());
		infoPage[2][0]->setContent("D.O.B: " + _state._user->DOB());
		infoPage[3][0]->setContent("TELEPHONE: " + _state._user->Tel());
		infoPage[4][0]->setContent("EMAIL: " + _state._user->Email());
		infoPage[5][0]->setContent("ADDRESS: " + _state._user->getAddress());
		infoPage[6][0]->setContent("EDIT INFO");
		infoPage.insertAbove(_state._menuPage);
		infoPage.beautifyGrid();
		void (Interface:: * editButton)() = &Interface::editPage;
		_command.clear();
		_command.insert(make_pair(infoPage[7][0], editButton));
		infoPage.showContentFullGrid();
		flagContinue = moveWithinGridAndExecuteFunction(infoPage);
		//moveWithinGridAndExecuteFunction(infoPage);
	}
}
void Interface::editPage()
{
	system("cls");
	Grid editPage(7, 1, 2, 2);
	Point editPageCoordinate(3, 3);
	editPage.createGrid(editPageCoordinate);
	editPage[0][0]->setContent("EDIT ID ");
	editPage[1][0]->setContent("EDIT NAME ");
	editPage[2][0]->setContent("EDIT D.O.B ");
	editPage[3][0]->setContent("EDIT TELEPHONE ");
	editPage[4][0]->setContent("EDIT EMAIL ");
	editPage[5][0]->setContent("EDIT ADDRESS ");
	editPage[6][0]->setContent("BACK");
	//editPage.insertAbove(_state._menuPage);
	editPage.beautifyGrid();
	_command.clear();
	void (Interface:: * editIDButton)() = &Interface::editIDPage;
	_command.insert(make_pair(editPage[0][0], editIDButton));
	void(Interface:: * editNameButton)() = &Interface::editNamePage;
	_command.insert(make_pair(editPage[1][0], editNameButton));
	void(Interface:: * editDOBButton)() = &Interface::editDOBPage;
	_command.insert(make_pair(editPage[2][0], editDOBButton));
	void(Interface:: * editTelephoneButton)() = &Interface::editTelephonePage;
	_command.insert(make_pair(editPage[3][0], editTelephoneButton));
	void(Interface:: * editEmailButton)() = &Interface::editEmailPage;
	_command.insert(make_pair(editPage[4][0], editEmailButton));
	void(Interface:: * editAddressButton)() = &Interface::editAddressPage;
	_command.insert(make_pair(editPage[5][0], editAddressButton));
	void(Interface:: * backButton)() = &Interface::backToInfoPage;
	_command.insert(make_pair(editPage[6][0], backButton));
	editPage.showContentFullGrid();
	moveWithinGridAndExecuteFunction(editPage);
}
void Interface::inputID()
{
	string str;
	cin >> str;
	_state._user->setId(str);
	cout << _state._user->Id();
}
void Interface::inputName()
{
	string str;
	getline(cin, str);
	_state._user->setName(str);
	cout << _state._user->Name();
}
void Interface::inputDOB()
{
	string str;
	getline(cin, str);
	_state._user->setDOB(str);
}
void Interface::inputTelephone()
{
	string str;
	getline(cin, str);
	_state._user->setTel(str);
}
void Interface::inputEmail() {
	string str;
	getline(cin, str);
	_state._user->setEmail(str);
}
void Interface::inputAddress()
{
	string str;
	getline(cin, str);
	_state._user->setAddress(str);
}
void Interface::backToEditPage()
{
	Interface::editPage();
}
void Interface::backToInfoPage()
{
	Interface::infoPage();
}
void Interface::editIDPage()
{
	system("cls");
	Grid newID(2, 2, 2, 3);
	Point editIDPageCoordinate(3, 3);
	newID.createGrid(editIDPageCoordinate);
	newID[0][0]->setContent("Insert new ID:");
	newID[0][1]->setContent("");
	newID[1][0]->setContent("SAVE!");
	newID[1][1]->setContent("BACK");
	newID.beautifyGrid();
	newID.showContentFullGrid();
	_command.clear();
	void (Interface:: * newIDButton)() = &Interface::inputID;
	_command.insert(make_pair(newID[0][1], newIDButton));
	void (Interface:: * backButton)() = &Interface::backToEditPage;
	_command.insert(make_pair(newID[1][1], backButton));
	moveWithinGridAndExecuteFunction(newID);
}
void Interface::editNamePage()
{
	system("cls");
	Grid newName(2, 2, 2, 3);
	Point editNamePageCoordinate(3, 3);
	newName.createGrid(editNamePageCoordinate);
	newName[0][0]->setContent("Insert new Name: ");
	newName[0][1]->setContent("");
	newName[1][0]->setContent("SAVE!");
	newName[1][1]->setContent("BACK");
	newName.beautifyGrid();
	newName.showContentFullGrid();
	_command.clear();
	void (Interface:: * newNameButton)() = &Interface::inputName;
	_command.insert(make_pair(newName[0][1], newNameButton));
	void (Interface:: * backButton)() = &Interface::backToEditPage;
	_command.insert(make_pair(newName[1][1], backButton));
	moveWithinGridAndExecuteFunction(newName);
}
void Interface::editDOBPage()
{
	system("cls");
	Grid newDOB(2, 2, 2, 3);
	Point editDOBPageCoordinate(3, 3);
	newDOB.createGrid(editDOBPageCoordinate);
	newDOB[0][0]->setContent("Insert new DOB: ");
	newDOB[0][1]->setContent("");
	newDOB[1][0]->setContent("SAVE!");
	newDOB[1][1]->setContent("BACK");
	newDOB.beautifyGrid();
	newDOB.showContentFullGrid();
	_command.clear();
	void (Interface:: * newDOBButton)() = &Interface::inputDOB;
	_command.insert(make_pair(newDOB[0][1], newDOBButton));
	void (Interface:: * backButton)() = &Interface::backToEditPage;
	_command.insert(make_pair(newDOB[1][1], backButton));
	moveWithinGridAndExecuteFunction(newDOB);
}
void Interface::editTelephonePage()
{
	system("cls");
	Grid newTel(2, 2, 2, 3);
	Point editTelPageCoordinate(3, 3);
	newTel.createGrid(editTelPageCoordinate);
	newTel[0][0]->setContent("Insert new Tel: ");
	newTel[0][1]->setContent("");
	newTel[1][0]->setContent("SAVE!");
	newTel[1][1]->setContent("BACK");
	newTel.beautifyGrid();
	newTel.showContentFullGrid();
	_command.clear();
	void (Interface:: * newTelButton)() = &Interface::inputTelephone;
	_command.insert(make_pair(newTel[0][1], newTelButton));
	void (Interface:: * backButton)() = &Interface::backToEditPage;
	_command.insert(make_pair(newTel[1][1], backButton));
	moveWithinGridAndExecuteFunction(newTel);
}
void Interface::editEmailPage()
{
	system("cls");
	Grid newEmail(2, 2, 2, 3);
	Point editEmailPageCoordinate(3, 3);
	newEmail.createGrid(editEmailPageCoordinate);
	newEmail[0][0]->setContent("Insert new Email: ");
	newEmail[0][1]->setContent("");
	newEmail[1][0]->setContent("SAVE!");
	newEmail[1][1]->setContent("BACK");
	newEmail.beautifyGrid();
	newEmail.showContentFullGrid();
	_command.clear();
	void (Interface:: * newEmailButton)() = &Interface::inputEmail;
	_command.insert(make_pair(newEmail[0][1], newEmailButton));
	void (Interface:: * backButton)() = &Interface::backToEditPage;
	_command.insert(make_pair(newEmail[1][1], backButton));
	moveWithinGridAndExecuteFunction(newEmail);
}
void Interface::editAddressPage()
{
	system("cls");
	Grid newAddress(2, 2, 2, 3);
	Point editAddressPageCoordinate(3, 3);
	newAddress.createGrid(editAddressPageCoordinate);
	newAddress[0][0]->setContent("Insert new Address: ");
	newAddress[0][1]->setContent("");
	newAddress[1][0]->setContent("SAVE!");
	newAddress[1][1]->setContent("BACK");
	newAddress.beautifyGrid();
	newAddress.showContentFullGrid();
	_command.clear();
	void (Interface:: * newAddressButton)() = &Interface::inputAddress;
	_command.insert(make_pair(newAddress[0][1], newAddressButton));
	void (Interface:: * backButton)() = &Interface::backToEditPage;
	_command.insert(make_pair(newAddress[1][1], backButton));
	moveWithinGridAndExecuteFunction(newAddress);
}
void Interface::schedulePage() {
	bool flagContinue = true;
	while (flagContinue) {
		system("cls");
		vector <string> weekday = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY" };
		Grid shiftPanel(4, 1, 2, 4);
		Point root(2, 4);
		shiftPanel.createGrid(root);
		shiftPanel[0][0]->setContent("1");
		shiftPanel[1][0]->setContent("2");
		shiftPanel[2][0]->setContent("3");
		shiftPanel[3][0]->setContent("4");
		Grid schedulePage(5, 5, 2, 2);
		Point root2(4, 3);
		schedulePage.createGrid(root2);
		for (int i = 0; i < 5; i++) {
			schedulePage[0][i]->setContent(weekday[i]);
			for (auto it : _state._user->getCourse()) {
				map<string, int> time = it->Time();
				if (time.find(weekday[i]) != time.end()) {
					int shift = it->Time()[weekday[i]];
					schedulePage[shift][i]->setContent(it->Name());
				}
			}
		}
		schedulePage.insertAbove(_state._menuPage);
		schedulePage.insertLeft(shiftPanel);
		schedulePage.beautifyGrid();
		schedulePage.showContentFullGrid();
		flagContinue = moveWithinGridAndExecuteFunction(schedulePage);
	}
}

bool Interface::confirmExit() {
	Point warningTextCoordinate(2, 1);
	warningTextCoordinate >> "Do you want to exit? ";
	cout << warningTextCoordinate;
	Point confirmGridCoordinate(25, 1);
	Grid confirmGrid(1, 2, 1, 2);
	confirmGrid.createGrid(confirmGridCoordinate);
	confirmGrid[0][0]->setContent("Y");
	confirmGrid[0][1]->setContent("N");
	cout << *confirmGrid[0][0];
	cout << *confirmGrid[0][1];
	Point confirm = moveWithinGrid(confirmGrid);
	warningTextCoordinate.clearPrintedContent();
	confirmGrid[0][0]->clearPrintedContent();
	confirmGrid[0][1]->clearPrintedContent();
	if (*confirmGrid[0][0] == confirm) return true;
	else return false;
}