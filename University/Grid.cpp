#include "Grid.h"

Grid::Grid(const Grid& other) {
	_row = other._row;
	_col = other._col;
	_rowGap = other._rowGap;
	_colGap = other._colGap;
	for (auto it : _grid) {
		for (auto it2 : it) {
			delete it2;
		}
	}
	for (auto it : other._grid) {
		vector <Point*>_store;
		for (auto it2 : it) {
			_store.push_back(it2);
		}
		_grid.push_back(_store);
	}
}

Grid& Grid::operator=(const Grid& other) {
	_row = other._row;
	_col = other._col;
	_rowGap = other._rowGap;
	_colGap = other._colGap;
	vector <vector <Point*>> temp1;
	_grid.swap(temp1);
	for (auto it : other._grid) {
		vector <Point*>_store;
		for (auto it2 : it) {
			_store.push_back(it2);
		}
		_grid.push_back(_store);
	}
	return *this;
}

void Grid::createGrid() {
	for (int i = 0, y = 0; i < _row; i++, y += _colGap) {
		vector <Point*> _store;
		for (int j = 0, x = 0; j < _col; j++, x += _rowGap) {
			_store.push_back(new Point(x, y));
		}
		_grid.push_back(_store);
	}
}

void Grid::createGrid(Point root) {
	for (int i = 0, y = root.Y(); i < _row; i++, y += _rowGap) {
		vector <Point*> _store;
		for (int j = 0, x = root.X(); j < _col; j++, x += _colGap) {
			_store.push_back(new Point(x, y));
		}
		_grid.push_back(_store);
	}
}

void Grid::beautifyGrid() {
	for (unsigned i = 0; i < (unsigned)_col - 1; i++) {
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
			if (_grid[k].size() > i && _grid[k].size() > 1) {
				_grid[k][i + 1]->setX(max_x + max_string + _colGap);
			}
		}
	}
}

void Grid::insertLeft(const Grid& other) {
	Grid copy(other);
	if (_grid.size() > copy._grid.size()) {
		int delta = _grid.size() - copy._grid.size();
		for (int j = 0; j < delta; j++) { // them hang bi thieu
			vector<Point*> temp;
			for (int i = 0; i < copy._col; i++) {
				temp.push_back(new Point(copy._grid[copy._row - 1][i]->X(), copy._grid[copy._row - 1][i]->Y() + _rowGap));
			}
			copy._grid.push_back(temp);
			copy._row++;
		}
	}
	for (unsigned i = 0; i < _grid.size(); i++) {
		for (unsigned j = 0; j < _grid[i].size(); j++) {
			copy._grid[i].push_back(_grid[i][j]);
		}
	}
	copy._col += this->_col;
	*this = copy;
}

void Grid::insertRight(const Grid& other){
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

void Grid::insertAbove(const Grid& other) {
	Grid copy(other);
	for (unsigned i = 0; i < _grid.size(); i++) {
		copy._grid.push_back(_grid[i]);
		copy._row++;
	}
	if (_col > copy._col) copy._col = _col;
	*this = copy;
}

void Grid::insertBelow(const Grid& other) {
	for (unsigned i = 0; i < other._grid.size(); i++) {
		_grid.push_back(other._grid[i]);
		_row++;
	}
	if (other._col > _col) _col = other._col;
}

void Grid::showContentFullGrid() {
	for (auto it : _grid) {
		for (auto it2 : it) {
			it2->showContentWithCoordinate();
		}
	}
}