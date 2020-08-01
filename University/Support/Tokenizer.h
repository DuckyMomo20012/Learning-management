#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Tokenizer {
public:
	static vector<string> split(string value, string separator);
	static vector<string> split(string value, string separator1, string separator2);
};