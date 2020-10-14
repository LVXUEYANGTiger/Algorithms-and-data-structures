#include <iostream>
using namespace std;
int SeqSearch(int A[],int n,int k){
	int i = 0;
	for(i = 0;i < n;i++){
		if(A[i] == k){
			break;
		}
	}
	if(i == n){
		return 0;
	} else {
		return (i + 1);
	}
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	cout << "Please enter the number of sequences you want:" << endl; 
	int n = 0;
	cin >> n;
	int A[n] = {0};
	cout << "Please enter the" << n << " elements one after the other: " << endl; 
	for(int i = 0;i < n;i++){
		cin >> A[i];
	}
	cout << "Please enter the number you're looking for:" << endl; 
	int k = 0;
	cin >> k;
	int result = SeqSearch(A,n,k);
	cout << "The position of this number in that sequence of elements is:" << result << endl;
	cout << "test-end" << endl;
	return 0;
}
