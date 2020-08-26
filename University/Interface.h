#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Person.h"
#include "Course.h"
#include "Table.h"
#include "json.hpp"
#include "Support/Tokenizer.h"
using namespace std;

using json = nlohmann::json;
//class Memento {
//public:
//	virtual void restore() = 0;
//};
//
//class Originator {
//public:
//	virtual Memento* save() = 0;
//};
//
//class IPage : public Originator {
//private:
//	Person* _client;
//	Table* _table;
//	map<Point*, void (IPage::*)()> _functions;
//public:
//	IPage(const IPage& other);
//	~IPage();
//public:
//	//void virtual setPageFunctions() = 0;
//public:
//	IPage& operator= (const IPage& other);
//	Person* Client() { return _client; }
//	void setClient(Person* client) { _client = client; }
//	Table* getTable() { return _table; }
//	void setTable(Table* table) { _table = table; }
//public:
//	Memento* save();
//};
//
//class IPageMemento : public Memento {
//private:
//	IPage orriginator;
//	Person* _client;
//	Table* _table;
//	map<Point*, void (IPage::*)()> _functions;
//public:
//	IPageMemento(Person* client, Table* table, map<Point*, void (IPage::*)()> functions)
//		: _client(client), _table(table), _functions(functions) {}
//	void restore() {
//
//	}
//	void foo();
//};
//
//class InfoPage : public IPage {
//
//};

class State {
private:
	Student* _user;
	Table _menuPage;
	friend class Interface;
public:
	State() : _user(), _menuPage() {}
	~State();
	State(const State& other);
	State& operator= (const State& other);
};

class Interface {
private:
	State _state;
	map<Point*, void (Interface::*)()> _command;
	vector<Point*> _trackProgress;
public:
	Interface() {
		resizeConsole(900, 500);
	}
public:
	void resizeConsole(int width, int height);
	void moveWithinGridAndExecuteFunction(Table& _grid);
	Point moveWithinGrid(Table& grid);
	void loginPage();
	void menuPage();
	void infoPage();
	void schedulePage();
	bool confirmExit();
};