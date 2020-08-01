#include "Course.h"

Course::Course(string value) {
	vector<string> _store(Tokenizer::split(value, " "));
	_id = _store[0];
	auto it = _store.begin();
	while (++it != _store.end())
		_name += *it + " ";
}