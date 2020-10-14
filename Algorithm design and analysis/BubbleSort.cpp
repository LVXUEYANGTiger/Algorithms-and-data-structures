#include <iostream>
using namespace std;
void BubbleSort(int r[],int n){
	int bound,exchange = n - 1;
	while(exchange != 0){
		bound = exchange;
		exchange = 0;
		for(int j = 0;j < bound;j++){
			if(r[j] > r[j + 1]){
				int temp = r[j];
				r[j] = r[j + 1];
				r[j + 1] = temp;
				exchange = j;
			}
		}
	}
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	cout << "Please enter the number of elements in a disordered sequence:" << endl;
	int n = 0;
	cin >> n; 
	int A[n] = {0};
	cout << "Please enter a disordered sequence:" << endl;
	for(int i = 0;i < n;i++){
		cin >> A[i];
	}
	cout << "Sorting a disordered sequence:" << endl;
	BubbleSort(A,n);
	cout << "The final ranked results are:" << endl;
	for(int i = 0;i < n;i++){
		cout << A[i] << " ";
	}
	cout << endl;
	cout << "test-end" << endl;
	return 0;
}
