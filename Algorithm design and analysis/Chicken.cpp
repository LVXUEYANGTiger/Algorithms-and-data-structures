#include <iostream>
using namespace std;
void Chicken(){
	int x,y,z;
	int count = 0;
	for(x = 0;x <= 20;x++){
		for(y = 0;y <= 33;y++){
			z = 100 - x - y;
			if((z % 3 == 0) && (5 * x + 3 * y + z / 3 == 100)){
				count++;
				cout << "����:" << x << "ĸ��" << y << "С��:" << z << endl; 
			}
		}
	}
	if(count == 0){
		cout << "�����޽�" << endl;
	}
}
int main(int argc, char** argv) {
	Chicken();
	return 0;
}
