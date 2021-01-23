#include <iostream>
using namespace std;
void Hanoi(int n,char A,char B,char C){
	if(n == 1){
		cout << A << "--->" << C << endl;
	} else {
		Hanoi(n - 1,A,C,B);
		cout << A  << "--->" << C << endl;
		Hanoi(n - 1,B,A,C);
	}
}
int main(int argc, char** argv) {
	cout << "请输入汉诺塔金碟的个数n:" << endl;
	int n;
	cin >> n;
	cout << "(A,B,C为塔的名称)" << endl;
	Hanoi(n,'A','B','C');
	return 0;
}
