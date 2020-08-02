#include "Person.h"

Person::Person(string value) {
	vector<string> _store(Tokenizer::split(value, "(", ")"));
	try {
		setId(_store[0]);
		setName(_store[1]);
		setTel(_store[2]);
		setEmail(_store[3]);
		setAddress(_store[4]);
		setDOB(_store[5]);
	}
	catch (...) {
		cout << "Invalid string format" << endl;
	}
}