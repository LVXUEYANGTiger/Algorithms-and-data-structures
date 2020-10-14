#include <iostream>
using namespace std;
int ArrayMin(int a[],int n){
	int min = a[0];
	for(int i = 1;i < n;i++){
		if(a[i] < min){
			min = a[i];
		}
	}
	return min;
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	int n = 0;
	cout << "Please enter the number of sequences:" << endl;
	cin >> n;
	cout << "Please enter " <<  n << " digits to initialize this sequence:" << endl;
	int a[n] = {0};
	for(int i = 0;i < n;i++){
		cin  >> a[i];
	}
	cout << endl;
	int result = ArrayMin(a,n);
	cout << "The minimum value of this sequence is:" << result << endl; 
	cout << "test-end" << endl;
	return 0;
}
