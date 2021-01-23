#include <iostream>
using namespace std;
void SiftHeap(int r[],int k,int n){
	int i,j,temp;
	i = k,j = 2 * i + 1;
	while(j < n){
		if(j < n - 1 && r[j] < r[j+1]){
			j++;
		}
		if(r[i] > r[j]){
			break;
		} else {
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i = j;
			j = 2 * i + 1;
		}
	}
}
void print(int r[],int n){
	for(int i = 0;i < n;i++){
		cout << r[i] << " ";
	}
	cout << endl;
}
void HeapSort(int r[],int n){
	int i,temp;
	for(i = (n - 1) / 2;i >= 0;i--){
		SiftHeap(r,i,n);
	}
	cout << "建好堆之后为:" << endl;
	print(r,n);
	for(i = 1;i <= n - 1;i++){
		temp = r[0];
		r[0] = r[n - i];
		r[n - i] = temp;
		SiftHeap(r,0,n - i);
	}
} 
int main(int argc, char** argv) {
	int n = 0,k = 0;
	cout << "请输入元素的个数:" << endl;
	cin >> n;
	int r[n] = {0};
	cout << "请输入元素:" << endl; 
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	HeapSort(r,n);
	cout << "已经排列好的元素序列为:" << endl;
	print(r,n);
	return 0;
}
