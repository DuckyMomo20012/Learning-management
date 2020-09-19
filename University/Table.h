#pragma once
#include <vector>
#include <iostream>
#include "Point.h"
using namespace std;

class Table {
private:
	int _row, _col, _rowGap, _colGap;
	vector<vector<Point*>> _table;
	Point* _root;
public:
	Table() : _root(new Point(0, 0)), _row(1), _col(1), _rowGap(1), _colGap(1) {
		createTable(_root);
	}
	Table(int xRoot, int yRoot, int rowGap, int colGap) : _root(new Point(xRoot, yRoot)), _rowGap(rowGap), _colGap(colGap), _row(0), _col(0) {
		createTable(_root);
	}
	Table(int xRoot, int yRoot, int rowGap, int colGap, int row, int col) : _root(new Point(xRoot, yRoot)),
		_rowGap(rowGap), _colGap(colGap), _row(row), _col(col)
	{
		createTable(_root);
	}
	Table(Point* root, int rowGap, int colGap, int row, int col) : _root(root), _rowGap(rowGap), _colGap(colGap), _row(row), _col(col) {
		createTable(_root);
	}
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
	vector <vector<Point*>> getTable() { return _table; }
	void setTable(vector<vector<Point*>> value) { _table = value; }
public:
	void createTable();
	void createTable(Point* tableCoordinate);
	void wrapText(unsigned rowPos, unsigned contentLimit);
	void beautifyTable();
	void insertLeft(const Table& other);
	void insertRight(const Table& other);
	void insertAbove(const Table& other);
	void insertBelow(const Table& other);
	void insertRowBelow(const vector <string>& values);
	void showTableContent();
	Point* moveWithinTable();
	void deleteRow(unsigned rowPos);
};