#include <iostream>
using namespace std;
int Partition(int r[],int first,int end){
	int i = first,j = end;
	while(i < j){
		while(i < j && r[i] <= r[j]){
			j--;
		}
		if(i < j){
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i++;
		}
		while(i < j && r[i] <= r[j]){
			i++;
		}
		if(i < j){
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			j--;
		}
	} 
	return i;
}
void QuickSort(int r[],int first,int end){
	int pivot;
	if(first < end){
		pivot = Partition(r,first,end);
		QuickSort(r,first,pivot - 1);
		QuickSort(r,pivot + 1,end);
	}
}
int main(int argc, char** argv) 
{
	int n = 0;
	cout << "请输入要排序元素的个数:" << endl;
	cin >> n; 
	int r[n] = {0};
	cout << "请输入" << n <<  "个元素" << endl;
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	QuickSort(r,0,n);
	cout << "最终排好的序列为:" << endl;
	for(int i = 0;i < n;i++){
		cout << r[i] << " ";
	}
	cout << endl;
	return 0;
}
