#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
using namespace std;

class Table {
private:
	int _row, _col, _rowGap, _colGap;
	vector< vector<Point*>> _grid;
public:
	Table() : _row(1), _col(1), _rowGap(1), _colGap(1) {}
	Table(int row, int col) : _row(row), _col(col), _rowGap(1), _colGap(1) {}
	Table(int row, int col, int rowGap, int colGap) : _row(row), _col(col), _rowGap(rowGap), _colGap(colGap) {}
	Table(const Table& other);
	~Table();
	Table& operator= (const Table& other);
public:
	int Row() { return _row; }
	void setRow(int value) { _row = value; }
	int Col() { return _col; }
	void setCol(int value) { _col = value; }
	int RowGap() { return _rowGap; }
	void setRowGap(int value) { _rowGap = value; }
	int ColGap() { return _colGap; }
	void setColGap(int value) { _colGap = value; }
	vector <vector<Point*>> getGrid() { return _grid; }
	void setGrid(vector<vector<Point*>> value) { _grid = value; }
public:
	vector <Point*>& operator[] (int i) {
		return _grid[i];
	}
	void createGrid();
	void createGrid(Point gridCoordinate);
	void beautifyGrid();
	void insertLeft(const Table& other);
	void insertRight(const Table& other);
	void insertAbove(const Table& other);
	void insertBelow(const Table& other);
	void showContentFullGrid();
};