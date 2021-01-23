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
	cout << "请输入元素的个数:" << endl;
	cin >> n;
	int r[n] = {0};
	cout << "请输入从小到大已经排好的元素" << endl; 
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	cout << "请输入你想要查找的那个元素:" << endl;
	cin >> k;
	flag = BinSearch(r,n,k);
	if(flag > 0){
		cout << "元素" << k << "在序列r的下标为: " << flag << endl;
	} else {
		cout << "查找失败" << endl; 
	}
	
	return 0;
}
