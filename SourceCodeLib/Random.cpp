#include "Random.h"
int Random::next() {
	return rand();
}

int Random::next(int ceil) {
	return rand() % ceil;
}

int Random::next(int floor, int ceil) {
	return rand() % (ceil - floor + 1) + floor;
}