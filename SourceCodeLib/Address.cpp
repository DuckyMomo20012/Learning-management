#include "Address.h"

Address::Address(string value) {
    parseAddress(value);
}

void Address::parseAddress(string value) {
	vector<string> store = Tokenizer::split(value, " ");
    auto ptr = store.begin();
    while (*ptr != "Duong") {
        _number += *ptr + " ";
        ptr++;
    }
    while (*(++ptr) != "Phuong") {
        _street += *ptr + " ";
    }
    while (*(++ptr) != "Quan") {
        _ward += *ptr + " ";
    }
    while (*(++ptr) != "Thanh") {
        _district += *ptr + " ";
    }
    while (++ptr != store.end()) {
        _city += *ptr + " ";
    }
}

string Address::showFullAddress() {
	stringstream writer;
	writer << _number << "Duong " << _street
		<< "Phuong " << _ward << "Quan "
		<< _district << "Thanh pho " << _city;
	return writer.str();
}