#pragma once
#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

class Random {
public:
	Random() {
		srand((unsigned int)time(NULL));
	}
	int next();
	int next(int);
	int next(int, int);
};