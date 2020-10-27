#include <iostream>
using namespace std;
void selectSort(int r[],int n){
	int i,j,index,temp;
	for(i = 0;i < n - 1;i++){
		index = i;
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
	cout << "test-start" << endl;
	int n;
	cout << "Please enter the number of sequences to sort." << endl; 
	cin >> n;
	int r[n];
	cout << "Please enter " << n << " digits:" << endl;
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	selectSort(r,n);
	for(int i = 0;i < n;i++){
		cout << r[i] << " ";
	}
	cout << endl;
	cout << "test-end" << endl;
	return 0;
}
