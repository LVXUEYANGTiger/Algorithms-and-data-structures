#include <iostream>
using namespace std;
void selectSort(int r[],int n){
	int i,j,index,temp;
	for(i = 0;i < n - 1;i++){
		index = i;
		// ȥ�������������С��¼ 
		for(j = i + 1;j < n;j++){
			if(r[j] < r[index]){
				index = j;
			}
		}
		if(index != i){
			temp = r[i];
			r[i] = r[index];
			r[index] = temp;
		}
	}
}
int main(int argc, char** argv) 
{
	int n;
	cout << "������Ԫ�صĸ���:" << endl; 
	cin >> n;
	int r[n];
	cout << "������" << n << "��Ԫ��:" << endl;
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	selectSort(r,n);
	cout << "�����źõ�����Ϊ:" << endl;
	for(int i = 0;i < n;i++){
		cout << r[i] << " ";
	}
	cout << endl;
	return 0;
}
