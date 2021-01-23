#include <iostream>
using namespace std;
int BinSearch(int r[],int n,int k){
	int low = 0,high = n - 1;
	while(low <= high){
		int mid = (low + high) / 2 ;
		if(k < r[mid]){
			high = mid - 1;
		} else if(k > r[mid]){
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return 0;
}
int main(int argc, char** argv) {
	int n = 0,k = 0,flag = 0;
	cout << "������Ԫ�صĸ���:" << endl;
	cin >> n;
	int r[n] = {0};
	cout << "�������С�����Ѿ��źõ�Ԫ��" << endl; 
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	cout << "����������Ҫ���ҵ��Ǹ�Ԫ��:" << endl;
	cin >> k;
	flag = BinSearch(r,n,k);
	if(flag > 0){
		cout << "Ԫ��" << k << "������r���±�Ϊ: " << flag << endl;
	} else {
		cout << "����ʧ��" << endl; 
	}
	
	return 0;
}
