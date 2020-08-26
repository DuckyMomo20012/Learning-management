#include "Table.h"

Table::Table(const Table& other) {
	_row = other._row;
	_col = other._col;
	_rowGap = other._rowGap;
	_colGap = other._colGap;
	vector <vector<Point*>> emptyGrid;
	swap(_grid, emptyGrid);
	for (auto it : other._grid) {
		vector <Point*> store;
		for (auto it2 : it) {
			store.push_back(it2);
		}
		_grid.push_back(store);
	}
}

Table& Table::operator= (const Table& other) {
	_row = other._row;
	_col = other._col;
	_rowGap = other._rowGap;
	_colGap = other._colGap;
	vector <vector<Point*>> emptyGrid;
	swap(_grid, emptyGrid);
	for (auto it : other._grid) {
		vector <Point*> store;
		for (auto it2 : it) {
			store.push_back(it2);
		}
		_grid.push_back(store);
	}
	return *this;
}

Table::~Table() {
	for (auto it : _grid) {
		for (auto it2 : it) {
			delete it2;
		}
	}
}

void Table::createGrid() {
	for (int i = 0, y = 0; i < _row; i++, y += _colGap) {
		vector <Point*> _store;
		for (int j = 0, x = 0; j < _col; j++, x += _rowGap) {
			_store.push_back(new Point(x, y));
		}
		_grid.push_back(_store);
	}
}

void Table::createGrid(Point gridCoordinate) {
	for (int i = 0, y = gridCoordinate.Y(); i < _row; i++, y += _rowGap) {
		vector <Point*> _store;
		for (int j = 0, x = gridCoordinate.X(); j < _col; j++, x += _colGap) {
			_store.push_back(new Point(x, y));
		}
		_grid.push_back(_store);
	}
}

void Table::beautifyGrid() {
	for (unsigned i = 0; i < (unsigned)_col; i++) {
		unsigned max_string = 0;
		int max_x = 0;
		for (unsigned j = 0; j < _grid.size(); j++) {
			if (_grid[j].size() > i) {
				if (_grid[j][i]->Content().size() > max_string) {
					max_string = _grid[j][i]->Content().size();
				}
				if (_grid[j][i]->X() > max_x) max_x = _grid[j][i]->X();
			}
		}
		for (unsigned k = 0; k < _grid.size(); k++) {
			if (_grid[k].size() > i && _grid[k].size() > 1 && i + 1 < (unsigned)_col) {
				_grid[k][i + 1]->setX(max_x + max_string + _colGap);
			}
			if (_grid[k].size() > i && k > 0) {
				_grid[k][i]->setY(_grid[k - 1][i]->Y() + _rowGap);
			}
		}
	}
}

void Table::insertLeft(const Table& other) {
	Table* copy = new Table(other);
	if (_grid.size() > copy->_grid.size()) {
		int delta = _grid.size() - copy->_grid.size();
		for (int j = 0; j < delta; j++) { // them hang bi thieu
			vector<Point*> temp;
			temp.push_back(new Point(copy->_grid[copy->_row - 1][0]->X(), copy->_grid[copy->_row - 1][0]->Y() + _rowGap));
			for (int i = 1; i < copy->_col; i++) {
				temp.push_back(new Point(copy->_grid[copy->_row - 1][i]->X() + _colGap, copy->_grid[copy->_row - 1][i]->Y() + _rowGap));
			}
			copy->_grid.push_back(temp);
			copy->_row++;
		}
	}
	vector <vector <Point*>> temp = this->getGrid();
	copy->_col += _col;
	_grid.clear();
	_rowGap = copy->_rowGap;
	_colGap = copy->_colGap;
	_row = copy->_row;
	_col = copy->_col;
	for (auto it : copy->_grid) {
		_grid.push_back(it);
	}
	for (unsigned i = 0; i < temp.size(); i++) {
		for (unsigned j = 0; j < temp[i].size(); j++) {
			_grid[i].push_back(temp[i][j]);
		}
	}
	
}

void Table::insertRight(const Table& other){
	if (other._grid.size() > _grid.size()) {
		int delta = other._grid.size() - _grid.size();
		for (int j = 0; j < delta; j++) { // them hang bi thieu
			vector<Point*> temp;
			for (int i = 0; i < _col; i++) {
				temp.push_back(new Point(_grid[_row - 1][i]->X(), _grid[_row - 1][i]->Y() + _rowGap));
			}
			_grid.push_back(temp);
			_row++;
		}
	}
	for (unsigned i = 0; i < other._grid.size(); i++) {
		for (unsigned j = 0; j < other._grid[i].size(); j++) {
			_grid[i].push_back(other._grid[i][j]);
		}
	}
	_col += other._col;
}

void Table::insertAbove(const Table& other) {
	int row = _row;
	int col = _col;
	vector <vector <Point*>> copy = this->getGrid();
	_grid.clear();
	_rowGap = other._rowGap;
	_colGap = other._colGap;
	_row = row + other._row;
	if (other._col > col) _col = other._col;
	else _col = col;
	for (auto it : other._grid) {
		_grid.push_back(it);
	}
	for (auto it2 : copy) {
		_grid.push_back(it2);
	}
}

void Table::insertBelow(const Table& other) {
	for (unsigned i = 0; i < other._grid.size(); i++) {
		_grid.push_back(other._grid[i]);
		_row++;
	}
	if (other._col > _col) _col = other._col;
}

void Table::showContentFullGrid() {
	for (auto it : _grid) {
		for (auto it2 : it) {
			cout << *it2;
		}
	}
}