#include "Tokenizer.h"

vector <string> Tokenizer::split(string value, string separator) {
    vector<string> result;
    int pos = 0, mark = 0;
    while ((pos = value.find(separator, pos + separator.size())) != value.npos) {
        result.push_back(value.substr(mark, pos - mark));
        if (result.back() == "") result.pop_back();
        mark = pos + separator.size();
    }
    result.push_back(value.substr(mark, value.size() - mark));
    return result;
}