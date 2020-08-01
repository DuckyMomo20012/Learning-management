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

vector<string> Tokenizer::split(string value, string separator1, string separator2) {
    vector <string> _store;
    int mark = value.find(separator1);
    int head = value.find(separator2);
    _store.push_back(value.substr(++mark, head - mark));
    while ((head = value.find(separator2, head + separator2.size())) != value.npos) {
        try {
            mark = value.find(separator1, mark + separator1.size());
            if (mark < head) {
                _store.push_back(value.substr(++mark, head - mark));
            }
            else {
                throw "Invalid format";
            }
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
    return _store;
}