#include "testFunc.h"
int main() {
	int num;
	cout << "Nhap so luong cau hoi: ";
	cin >> num;
	vector<Test*>list;
	string ques;
	string a, b, c, d, ans;
	cin.ignore();
	for (int i = 0; i < num; i++) {
		cout << endl << "Nhap cau hoi " << i + 1 << ": ";
		getline(cin, ques);
		cout << "A.";
		getline(cin, a);
		cout << "B.";
		getline(cin, b);
		cout << "C.";
		getline(cin, c);
		cout << "D.";
		getline(cin, d);
		cout << "Answer:";
		getline(cin, ans);
		list.push_back(new Test(ques, a, b, c, d, ans));
	}
	ofstream writer("test.txt", ios::out);
	if (!writer) {
		cout << "Khong mo duoc File!";
		exit(EXIT_FAILURE);
	}
	writer <<num;
	for (auto &i : list) {
		writer << endl << i->toString();
	}
	writer.close();


	ifstream reader("test.txt", ios::in);
	if (!reader) {
		cout << "Khong mo duoc file!";
		exit(EXIT_FAILURE);
	}
	string str;
	getline(reader, str, '\n');
	cout << "BO DE KIEM TRA GOM " << num << " CAU HOI";
	vector<Test*>list1;
	
	for (int i = 0; i < num; i++) {
		int y = 0;
		getline(reader, str, '\n');
		vector<string>q = Test::split(str, "-");
		ques =q[y++];
		a = q[y++];
		b = q[y++];
		c = q[y++];
		d = q[y++];
		ans = q[y++];
		list1.push_back(new Test(ques,a,b,c,d,ans));
		q.erase(q.begin(),q.end());
	}
	for (auto& quess:list1) {
		cout << endl <<quess->toQues();
	}
	reader.close();
}