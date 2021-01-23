#include <iostream>
using namespace std;
void BubbleSort(int r[],int n){
	int compare = 0,move = 0;
	int bound,exchange = n - 1;
	while(exchange != 0){
		bound = exchange;
		exchange = 0;
		for(int j = 0;j < bound;j++){
			if(++compare && r[j] > r[j + 1]){
				int temp = r[j];
				r[j] = r[j + 1];
				r[j + 1] = temp;
				// 一次交换是3次移动 
				move += 3;
				// 记录每次交换的位置 
				exchange = j;
			}
		}
	}
	cout << "这个序列比较的次数为" << compare << endl; 
	cout << "这个序列移动的次数为" << move << endl; 
}
int main(int argc, char** argv) 
{
	int n = 0;
	cout << "请输入要排序元素的个数:" << endl;
	cin >> n; 
	int A[n] = {0};
	cout << "请输入" << n <<  "个元素" << endl;
	for(int i = 0;i < n;i++){
		cin >> A[i];
	}
	BubbleSort(A,n);
	cout << "最终排好的序列为:" << endl;
	for(int i = 0;i < n;i++){
		cout << A[i] << " ";
	}
	cout << endl;
	return 0;
}
