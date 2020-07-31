#pragma once
#include <Windows.h>
class Console {
public:
	void resizeConsole(int width, int height);
	void goTo(int x, int y);
};
