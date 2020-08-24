#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Test {
private:
	string _Question;
	string _A, _B, _C, _D, _Ans;
public:
	Test(string, string, string, string, string, string);
	string toString();
	string toQues();
public:
	static vector<string> split(string haystack, string seperator);
};
