#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
int Comp(char a,char b){
	if(a > b){
		return 1;
	} else {
		return 0;
	}
} 
char Game(char r[],int n){
	int i = n;
	while(i > 1){
		i = i / 2;
		for(int j = 0;j < i;j++){
			cout << "��" << r[j + i] << "��" << r[j] << "�ı�����:" ; 
			if(Comp(r[j + i],r[j])){
				r[j] = r[j + i];
			}
			cout << r[j] << "ʤ��" << endl; 
		}
	}
	return r[0];
}
int main(int argc, char** argv) {
	char r[255];
	bool flag = false;
	cout << "������ѡ�ֵ�����:(ÿ��ѡ����һ���ַ������Կո����)" << endl;
	gets(r); 
	int len = strlen(r);
	for(int i = 0;i < len;i++){
		if(len == int(pow(2,i))){
			flag = true;
			break;
		}
	}
	char final; 
	if(flag){
		final = Game(r,len);
		cout << "���յ�ʤ��Ϊ:" << final << endl;
	} else {
		cout << "ѡ�ֵĸ���������2^k�η�" << endl; 
	}

	return 0;
}
