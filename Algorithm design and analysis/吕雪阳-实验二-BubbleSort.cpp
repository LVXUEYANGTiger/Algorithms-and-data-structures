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
				// һ�ν�����3���ƶ� 
				move += 3;
				// ��¼ÿ�ν�����λ�� 
				exchange = j;
			}
		}
	}
	cout << "������бȽϵĴ���Ϊ" << compare << endl; 
	cout << "��������ƶ��Ĵ���Ϊ" << move << endl; 
}
int main(int argc, char** argv) 
{
	int n = 0;
	cout << "������Ҫ����Ԫ�صĸ���:" << endl;
	cin >> n; 
	int A[n] = {0};
	cout << "������" << n <<  "��Ԫ��" << endl;
	for(int i = 0;i < n;i++){
		cin >> A[i];
	}
	BubbleSort(A,n);
	cout << "�����źõ�����Ϊ:" << endl;
	for(int i = 0;i < n;i++){
		cout << A[i] << " ";
	}
	cout << endl;
	return 0;
}
