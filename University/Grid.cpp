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
	// DANG BAO TRI :(((
	//
	//
	//
	//unsigned max_col = _grid[0].size();
	//for (unsigned i = 1; i < _grid.size(); i++) {
	//	if (_grid[i].size() > max_col) max_col = _grid[i].size();
	//}
	//for (int i = 0; i < max_col; i++) {
	//	unsigned max_string = 0;
	//	int locate;
	//	for (int j = 0; j < _grid.size(); j++) {
	//		if (_grid[j].size() > i) {
	//			if (_grid[j][i]->Content().size() > max_string) {
	//				locate = j;
	//				max_string = _grid[j][i]->Content().size();
	//			}
	//		}
	//	}
	//	for (int k = 0; k < _grid.size(); k++) {
	//		if (_grid[k].size() >= i + 1 && i + 1 < max_col) {
	//			int x = _grid[k][i]->X();
	//			unsigned size = _grid[k][i]->Content().size();
	//			_grid[k][i + 1]->setX(x + (max_string - size) + _rowGap);
	//		}
	//	}
	//	for (int above = locate; above >= 0; above--) {

	//	}
	//}
}

void Grid::insertLeft(const Grid& other) {
	Grid copy(other);
	for (unsigned i = 0; i < _grid.size(); i++) {
		for (unsigned j = 0; j < _grid[i].size(); j++) {
			copy._grid[i].push_back(_grid[i][j]);
		}
	}
	*this = copy;
}

void Grid::insertRight(const Grid& other){
	for (unsigned i = 0; i < other._grid.size(); i++) {
		for (unsigned j = 0; j < other._grid[i].size(); j++) {
			_grid[i].push_back(other._grid[i][j]);
		}
	}
}

void Grid::insertAbove(const Grid& other) {
	Grid copy(other);
	for (unsigned i = 0; i < _grid.size(); i++) {
		copy._grid.push_back(_grid[i]);
	}
	*this = copy;
}

void Grid::insertBelow(const Grid& other) {
	for (unsigned i = 0; i < other._grid.size(); i++) {
		_grid.push_back(other._grid[i]);
	}
}

void Grid::showContentFullGrid() {
	for (auto it : _grid) {
		for (auto it2 : it) {
			it2->showContentWithCoordinate();
		}
	}
}