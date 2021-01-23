#include <iostream>
using namespace std;
void selectSort(int r[],int n){
	int i,j,index,temp;
	for(i = 0;i < n - 1;i++){
		index = i;
		// 去无序区间查找最小记录 
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
	cout << "请输入元素的个数:" << endl; 
	cin >> n;
	int r[n];
	cout << "请输入" << n << "个元素:" << endl;
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	selectSort(r,n);
	cout << "最终排好的序列为:" << endl;
	for(int i = 0;i < n;i++){
		cout << r[i] << " ";
	}
	cout << endl;
	return 0;
}
