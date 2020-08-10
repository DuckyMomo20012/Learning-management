#pragma once
#include <conio.h>
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include "Console.h"
#include "Person.h"
#include "Course.h"
#include "Grid.h"
#include "json.hpp"
#include "Support/Tokenizer.h"
using namespace std;

using json = nlohmann::json;

class State {
private:
	map<string, Student*> _allStu;
	map<string, Prof*> _allProf;
	map<string, Course*> _allCourse;
	Grid _menuGrid;
	vector <string> _menu = { "INFO", "SCHEDULE", "TRANSCRIPT", "TEST", "ENROLL" };
	vector <string> _weekday = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY" };
	friend class Interface;
public:
	State() : _menuGrid(1, 5, 5, 2){}
	~State() {} // Ko can thiet
	State(const State& other);
	State& operator= (const State& other);
public:
	void setGridMenu();
	void loadAllStudent(const char* fileName);
	void loadAllCourse(const char* fileName);
	//void loadAllButton(const char* fileName);
};

class Interface {
private:
	State _state;
public:
	Interface() {
		//_state.loadAllButton("Button.json");
		_state.loadAllStudent("Student.json");
		//drawMenuPanel();
	}
public:
	void move(Grid& _grid);
	void drawMenuPanel(Grid& _grid);
	void drawInfoPanel(string id);
	void drawSchedulePanel(string id);
	//void drawTranscriptPanel(string id);
};
