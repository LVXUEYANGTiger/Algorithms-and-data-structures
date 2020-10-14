#include <iostream>
using namespace std;
void Union(int A[],int n,int B[],int m,int C[]){
	int i = 0,j = 0,k = 0;
	while(i < n && j < m){
		if(A[i] <= B[j]){
			C[k++] = A[i++];
		} else {
			C[k++] = B[j++];
		}
	}
	while(i < n){
		C[k++] = A[i++];
	}
	while(j < m){
		C[k++] = B[j++];
	}
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	cout << "Please enter two numbers (the number of elements of the two sequences):"  << endl; 
	int n = 0,m = 0;
	cin >> n >> m;
	int A[n] = {0},B[m] = {0};
	cout << "Please enter "<< n <<" elements in ascending order:" << endl; 
	for(int i = 0;i < n;i++){
		cin >> A[i];
	}
	cout << endl;
	cout << "Please enter "<< m <<" elements in ascending order:" << endl; 
	for(int i = 0;i < m;i++){
		cin >> B[i];
	}
	cout << endl;
	int C[m + n] = {0};
	cout << "Merging of two sequences:" << endl;
	Union(A,n,B,m,C);
	cout << "The final C result is:" << endl;
	for(int i = 0;i < m + n;i++){
		cout << C[i] << " ";
	}
	cout << endl;
	cout << "test-end" << endl;
	return 0;
}
