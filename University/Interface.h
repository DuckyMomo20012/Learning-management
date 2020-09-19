#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <list>
#include <algorithm>
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
	State() : _user(), _exitFlag(false), _goBackFlag(false), _menuTable(new Table(3, 3, 2, 4)) {
		initializeMenuTable();
	}
	State(const State& other) : _user(), _exitFlag(false), _goBackFlag(false), _menuTable(new Table(3, 3, 2, 4)) {
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
	virtual bool preventCreateNewPage() { return false; }
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

class EnrollPage : public IPage {
private:
	bool flagPickCourse;
	vector <pair<Course*, string>> _courseStore;
	vector <Course*> _courseChosenStore;
private:
	EnrollPage(State* state) : IPage(state), flagPickCourse(false) {
		initializePage();
	}
public:
	static IPage* instance(State* state) {
		static EnrollPage* neo = new EnrollPage(state);
		return neo;
	}
	void initializePage() override;
	void executeFunction(Point* locate) override;
	bool preventCreateNewPage() override;
public:
	void getCourse();
	void refresh();
	void increaseSlot(Course* course);
	void decreaseSlot(Course* course);
	void pickCourse(Point* locate);
	void deleteCourse(Point* locate);
	void saveChanges(Point* locate);
	void saveStudentCourseData(vector <Course*> newCourse);
	string checkCourseHasSameTime(Course* course);
};

class TranscriptPage : public IPage {
private:
	vector <pair<Course*, string>> _courseStore;
	vector <Course*> _courseChosenStore;
public:
	TranscriptPage(State* state) : IPage(state) {
		initializePage();
	}
public:
	void initializePage() override;
	void executeFunction(Point* locate) override;
public:
	
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
	bool preventCreateNewPage;
public:
	Interface() : _state(), preventCreateNewPage(false) {
		//resizeConsole(900, 500);
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
	void saveStudentInfoData();
};