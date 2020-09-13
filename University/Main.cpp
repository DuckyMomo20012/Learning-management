#include "Interface.h"

int main() {
	/*Interface i;
	i.run();*/
	json student;
	student = readJson("Student.json", student);
	cout << student[0]<<endl<<endl;
	cout << student[0]["course"].size() << endl;
	student[0]["course"].erase(student[0]["course"].begin()+0 );
	cout << student[0].dump(4);
	return 0;
}

