#pragma once
#include<sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <list>
#include "Person.h"
#include "Course.h"
#include "Table.h"
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class State {
private:
	Student* _user;
	Table* _menuTable;
	bool _exitFlag;
	bool _goBackFlag;
public:
	State() : _user(), _exitFlag(false), _goBackFlag(false), _menuTable(new Table(3, 3, 1, 5, 2, 4)) {
		initializeMenuTable();
	}
	State(const State& other) : _user(), _exitFlag(false), _goBackFlag(false), _menuTable(new Table(3, 3, 1, 5, 2, 4)) {
		initializeMenuTable();
	}	
	~State();
	State& operator= (const State& other);
public:	
	void setStudent(Student* user) { _user = user; }
	Student* User() { return _user; }
	void initializeMenuTable();
	Table* getMenuTable() { return _menuTable; }
	void setExitFlag(bool value) { _exitFlag = value; }
	bool ExitFlag() { return _exitFlag; }
	void setGoBackFlag(bool value) { _goBackFlag = value; }
	bool GoBackFlag() { return _goBackFlag; }
};

class IPage {
private:
	State* _state;
	Table* _table;
public:
	IPage(State* state) : _state(state), _table() {}
public:
	State* getStateIPage() { return _state; }
	void setStateIPage(State* other) { _state = other; }
	Table* getIPageTable() { return _table; }
	void setIPageTable(Table* table) { _table = table; }
public:
	virtual void initializePage() = 0;
	virtual void executeFunction(Point* locate) = 0;
};

class MainPage : public IPage {
public:
	MainPage(State* state) : IPage(state) {
		initializePage();
	}
public:
	void initializePage() override;
	void executeFunction(Point* locate) override;
};

class InfoPage : public IPage {
public:
	InfoPage(State* state) : IPage(state) {
		initializePage();
	}
public:
	void initializePage() override;
	void executeFunction(Point* locate) override;
public:
	string edit(Point*& locate, string ignoreString);
};

class SchedulePage : public IPage {
public:
	SchedulePage(State* state) : IPage(state) {
		initializePage();
	}
public:
	void initializePage() override;
	void executeFunction(Point* locate) override;
};
class EnrollPage :public IPage
{
public:
	EnrollPage(State* state) : IPage(state) {
		initializePage();
	}
public:
	void initializePage() override;
	void executeFunction(Point* locate) override;
public:
	string edit(Point*& locate);
};

class Factory {
public:
	static IPage* clone(Point* locate, State* state);
};

class Caretaker {
private:
	list<IPage*> _history;
public:
	IPage* getCurrentPage() { return _history.back(); }
	IPage* getMainPage() { return _history.front(); }
	void push_back(IPage* other);
	void pop_back();
};

class Interface {
private:
	State* _state;
	Caretaker _care;
public:
	Interface() : _state() {
		resizeConsole(900, 500);
	}
public:
	State* getState() { return _state; }
	void setState(State* value) { _state = value; }
	Caretaker getCare() { return _care; }
	void setCare(Caretaker& value) { _care = value; }
public:
	void resizeConsole(int width, int height);
	void login();
	static bool YesNoQuestionBox(Point* locate, string sentence);
	void run();
};
