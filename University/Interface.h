#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Person.h"
#include "Course.h"
#include "Grid.h"
#include "json.hpp"
#include "Support/Tokenizer.h"
using namespace std;

using json = nlohmann::json;

class State {
private:
	Student* _user;
	Grid _menuPage;
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
	map<Point* , void (Interface::*)()> _command;
	vector<Point*> _trackProgress;
public:
	Interface() {
		resizeConsole(900, 500);
	}
public:
	void resizeConsole(int width, int height);
	bool moveWithinGrid(Grid& _grid);
	//Point moveWithinGrid(Grid grid);
	void loginPage();
	void menuPage();
	void infoPage();
	void schedulePage();
	void exitPage();
	bool confirmExit();
};
