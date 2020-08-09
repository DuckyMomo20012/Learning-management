#include "Interface.h"

State::State(const State& other) {
	map<string, Student*> temp1;
	map<string, Prof*> temp2;
	map<string, Course*> temp3;
	_allStu.swap(temp1);
	_allProf.swap(temp2);
	_allCourse.swap(temp3);
	for (auto it : other._allStu) {
		_allStu.insert(it);
	}
	for (auto it : other._allProf) {
		_allProf.insert(it);
	}
	for (auto it : other._allCourse) {
		_allCourse.insert(it);
	}
}

State& State::operator= (const State& other) {
	map<string, Student*> temp1;
	map<string, Prof*> temp2;
	map<string, Course*> temp3;
	_allStu.swap(temp1);
	_allProf.swap(temp2);
	_allCourse.swap(temp3);
	// swap voi object rong se xoa tat ca du lieu cua cai bi swap, luc nay capacity = 0
	// xai clear() thi capacity != 0
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

void State::setGridMenu() {
	Point root(3, 1);
	_menuGrid.createGrid(root);
	for (int i = 0; i < 5; i++) {
		_menuGrid[0][i]->setContent(_menu[0]);
	}
}

void State::loadAllStudent(const char* fileName) {
	ifstream file(fileName, ios::in);
	if (file.fail()) cout << "Cannot open file!!!";
	else {
		json _array = json::array();
		file >> _array;
		for (unsigned i = 0; i < _array.size(); i++) {
			_allStu.insert(make_pair(_array[i]["id"], new Student(_array[i])));
		}
	}
	file.close();
}

void State::loadAllCourse(const char* fileName) {
	ifstream file(fileName, ios::in);
	if (file.fail()) cout << "Cannot open file!!!";
	else {
		json _array = json::array();
		file >> _array;
		for (unsigned i = 0; i < _array.size(); i++) {
			_allCourse.insert(make_pair(_array[i]["id"], new Course(_array[i])));
		}
	}
	file.close();
}

//void State::loadAllButton(const char* fileName) {
//	ifstream file(fileName, ios::in);
//	if (file.fail()) cout << "Cannot open file!!!";
//	else {
//		json _array = json::array();
//		file >> _array;
//		vector <Point*> _store;
//		for (unsigned i = 0; i < _array.size(); i++) {	
//			_store.push_back(new Point(_array[i][0]["x"], _array[i][0]["y"]));
//		}
//		_grid.push_back(_store);
//	}
//	file.close();
//}

void Interface::move(Grid& _grid) {
	unsigned row = 0, col = 0;
	goTo(_grid[row][col]->X() - 1, _grid[row][col]->Y());
	while (1) {
		switch (toupper(_getch())) {
		case 'W': {
			if (row > 0 && _grid[row - 1].size() >= col) {
				goTo(_grid[row - 1][col]->X() - 1, _grid[row - 1][col]->Y());
				row--;
			}
			break;
		}
		case 'S': {
			if (row < (unsigned)_grid.Row() - 1 && _grid[row + 1].size() >= col) {
				goTo(_grid[row + 1][col]->X() - 1, _grid[row + 1][col]->Y());
				row++;
			}
			break;
		}
		case 'A': {
			if (col > 0) {
				goTo(_grid[row][col - 1]->X() - 1, _grid[row][col - 1]->Y());
				col--;
			}
			break;
		}
		case 'D': {
			if (col < _grid[row].size() - 1) {
				goTo(_grid[row][col + 1]->X() - 1, _grid[row][col + 1]->Y());
				col++;
			}
			break;
		}
		}
	}
}

//void Interface::drawMenuPanel() {
//	Grid _grid(1, 5, 1, 4);
//	vector<vector<Point*>> grid = _grid.getGrid();
//	Point root(3, 1);
//	_grid.createGrid(root);
//	for (int i = 0; i < 5; i++) {
//		grid[0][i]->setContent(_menu[i]);
//	}
//	_grid.setGrid(grid);
//	_grid.beautifyGrid();
//}

void Interface::drawInfoPanel(string id) {
	Grid _grid(6, 1, 1, 4);
	Point root(3, 3);
	_grid.createGrid(root);
	_grid[0][0]->setContent("ID: " + _state._allStu[id]->Id());
	_grid[1][0]->setContent("NAME: " + _state._allStu[id]->Name());
	_grid[2][0]->setContent("D.O.B: " + _state._allStu[id]->DOB().showDate());
	_grid[3][0]->setContent("TELEPHONE: " + _state._allStu[id]->Tel());
	_grid[4][0]->setContent("EMAIL: " + _state._allStu[id]->Email());
	_grid[5][0]->setContent("ADDRESS: " + _state._allStu[id]->getAddress().showFullAddress());
	Grid _grid2(6, 1, 1, 4);
	Point root1(30, 3);
	_grid2.createGrid(root1);
	_grid2[0][0]->setContent("ID: " + _state._allStu[id]->Id());
	_grid2[1][0]->setContent("NAME: " + _state._allStu[id]->Name());
	_grid2[2][0]->setContent("D.O.B: " + _state._allStu[id]->DOB().showDate());
	_grid2[3][0]->setContent("TELEPHONE: " + _state._allStu[id]->Tel());
	_grid2[4][0]->setContent("EMAIL: " + _state._allStu[id]->Email());
	_grid2[5][0]->setContent("ADDRESS: " + _state._allStu[id]->getAddress().showFullAddress());
	_grid.insertRight(_grid2);
	_grid.beautifyGrid();
	_grid.showContentFullGrid();
	move(_grid);
}

//
//void Interface::drawSchedulePanel(string id) {
//	Point root(5, 5);
//	_state.setGrid(root, 5, 6, 1, 10);
//	for (unsigned i = 1; i < _state._grid[1].size(); i++) {
//		goTo(_state._grid[1][i]->X(), _state._grid[1][i]->Y());
//		cout << _weekday[i - 1];
//	}
//	for (unsigned i = 2; i < _state._grid.size(); i++) {
//		goTo(_state._grid[i][0]->X(), _state._grid[i][0]->Y());
//		cout << i - 1;
//	}
//	for (unsigned i = 2; i < _state._grid.size(); i++) {
//		for (unsigned j = 1; j < _state._grid[i].size(); j++) {
//			goTo(_state._grid[i][j]->X(), _state._grid[i][j]->Y());
//			for (auto it : _state._allStu[id]->getCourse()) {
//				if (it->Time()[_weekday[j - 1]] == i - 1) {
//					cout << it->Name();
//				}
//			}
//		}
//	}
//	move();
//}

