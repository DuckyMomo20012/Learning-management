#include "testFunc.h"
Test::Test(string ques, string a, string b, string c, string d, string ans) {
	_Question = ques;
	_A = a;
	_B = b;
	_C = c;
	_D = d;
	_Ans = ans;
}
string Test::toString() {
	stringstream writer;
	writer << _Question << "-" << _A << "-" << _B << "-" << _C << "-" << _D << "-" << _Ans;
	return writer.str();
}
vector<string>Test::split(string haystack, string separator) {
    vector<string> result;

    int startPos = 0;
    int foundPos;

    while (true) {
        foundPos = haystack.find(separator, startPos);
        if (foundPos != string::npos) {
            string token = haystack.substr(startPos, foundPos - startPos);
            startPos = separator.length() + foundPos;
            result.push_back(token);
        }
        else {
            string token = haystack.substr(startPos, haystack.length() - startPos);
            result.push_back(token);
            break;
        }
    }

    return result;
}
string Test::toQues() {
    stringstream writer;
    writer << "Cau hoi:"<<_Question << endl;
    writer << "A." << _A << endl;
    writer << "B." << _B << endl;
    writer << "C." << _C << endl;
    writer << "D." << _D << endl<<endl;
    return writer.str();

}