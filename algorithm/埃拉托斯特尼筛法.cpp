#include <iostream>
#include <math.h>
using namespace std;
typedef int var;
/**
Ҫ�õ���Ȼ��n���ڵ�ȫ������������Ѳ����ڸ���n�����������ı����޳���ʣ�µľ���������
*/ 
int countPrime(var n){
	// �����ĸ��� 
	var result = 0; 
	// ��ʶ�����ʼ��Ĭ��ֵ��Ϊ false��Ϊ�������
	bool b[n] = {false};

	for(int i = 2;i * i< n;i++){
		// ������
		if(!b[i]){
				for(int j = i * i;j < n;j += i){
					b[j] = true;
				}
			}
			
		}
	
	cout << "��0-" << n << "����Ϊ:" << endl;
	for(int i = 2;i < n;i++){
		if(b[i] == false){
			result++;
			cout << i << " ";
		}
	}
	cout << endl;
	return result; 
} 
int main(int argc, char** argv) {
	cout << "�������Կ�ʼ" << endl;
	var n = 0;
	var result = 0;
	cout << "������һ����(������)" << endl;
	cin >> n;
	if(n == 1){
		cout << "1��������" << endl;
	} else {
		result = countPrime(n);
	}
	cout << "С��" << n << "������һ����" << result << "��" << endl;
	cout << "�������Խ���" << endl; 
	return 0;
}

