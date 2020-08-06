#include "Interface.h"

State::~State() {
	for (auto it : _allStu) {
		delete it.second;
	}
	for (auto it : _allProf) {
		delete it.second;
	}
	for (auto it : _allCourse) {
		delete it.second;
	}
	for (auto it : _allButton) {
		for (auto it2 : it.second) {
			delete it2;
		}
	}
}

State::State(const State& other) {
	for (auto it : other._allStu) {
		_allStu.insert(it);
	}
	for (auto it : other._allProf) {
		_allProf.insert(it);
	}
	for (auto it : other._allCourse) {
		_allCourse.insert(it);
	}
	for (auto it : other._allButton) { // it de chay key kieu int
		for (auto it2 : it.second) { // it2 de chay tung ptu cua vector<*Point>
			_allButton[it.first].push_back(it2);
		}
	}
}

State& State::operator= (const State& other) {
	_allStu.clear();
	_allProf.clear();
	_allCourse.clear();
	for (auto it : other._allStu) {
		_allStu.insert(it);
	}
	for (auto it : other._allProf) {
		_allProf.insert(it);
	}
	for (auto it : other._allCourse) {
		_allCourse.insert(it);
	}
	return *this;
}

void State::loadAllStudent(const char* fileName) {
	ifstream file(fileName, ios::in);
	if (file.fail()) cout << "Cannot open file!!!";
	else {
		json _array = json::array();
		file >> _array;
		for (unsigned i = 0; i < _array.size(); i++) {
			//string _id = _array[i]["id"];
			//Student* _tempStudent = new Student(_array[i]["id"], _array[i]);
			_allStu.insert(make_pair(_array[i]["id"], new Student(_array[i]["id"], _array[i])));
		}
	}
	file.close();
}

void State::loadAllButton(const char* fileName) {
	ifstream file(fileName, ios::in);
	if (file.fail()) cout << "Cannot open file!!!";
	else {
		json _array = json::array();
		file >> _array;
		for (unsigned i = 0; i < _array.size(); i++) {
			vector <Point*> _storePoint;
			for (auto it : _array[i]) { // _array co nhieu nut nhu info, schedule... lan luot la array[0], array[1]
				for (auto it2 : it) { // it de duyet tung ptu cua tung nut, it co nhieu toa do, it2 de duyet tung toa do
					_storePoint.push_back(new Point(it2["x"], it2["y"]));
				}
			}
			_allButton.insert(make_pair(i, _storePoint));
		}
	}
	file.close();
}

void Interface::drawInfoPanel(string id) {
	int x = _state._allButton[INFO][0]->X(); // INFO co gtri 0
	int y = _state._allButton[INFO][0]->Y();
	goTo(x, y);
	cout << "NAME: " << _state._allStu[id]->Name();
	goTo(x, ++y);
	cout << "ID: " << _state._allStu[id]->Id();
	goTo(x, ++y);
	cout << "TELEPHONE: " << _state._allStu[id]->Tel();
	goTo(x, ++y);
	cout << "EMAIL: " << _state._allStu[id]->Email();
	goTo(x, ++y);
	cout << "ADDRESS: " << _state._allStu[id]->getAddress().showFullAddress();
	x = _state._allButton[INFO][1]->X();
	y = _state._allButton[INFO][1]->Y();
	vector <Course*> _course = _state._allStu[id]->getCourse();
	for (auto it : _course) {
		goTo(x, y++);
		cout << "ID: " << it->Id();
		cout << "NAME: " << it->Name() << " ";
		for (auto it2 : it->Point()) {
			cout << it2 << " ";
		}
	}
}