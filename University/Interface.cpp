#include "Interface.h"

State::~State() {
	for (auto it : _allStu) {
		delete it;
	}
	for (auto it : _allProf) {
		delete it;
	}
}

State::State(const State& other) {
	this->_allStu = other._allStu;
	this->_allProf = other._allProf;
}

State& State::operator= (const State& other) {
	this->_allStu = other._allStu;
	this->_allProf = other._allProf;
	return *this;
}

void State::loadStu(const char* fileName) {
	ifstream file(fileName, ios::in);
	if (file.fail()) cout << "Cannot open file!!!";
	else {
		json _array = json::array();
		file >> _array;
		for (int i = 0; i < _array.size(); i++) {
			_allStu.insert(new Student(_array[i]["id"], _array[i])); //Student* _tempStudent = new Student(_array[i]["id"], _array[i]);
		}
	}
	file.close();
}