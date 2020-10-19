#include <iostream>
using namespace std;
int SeqSearch(int r[],int n,int k){
	int i = n;
	while(i > 0 && r[i] != k){
		i--;
	}
	return i;
} 
int main(int argc, char** argv) {
	cout << "test-start" << endl;
	int n = 0;
	cout << "Please enter the number of sequences:" << endl;
	cin >> n;
	int r[n] = {0};
	cout << "Please enter " << n << " digits:" << endl;
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	cout << "Please enter the number you're looking for:" << endl;
	int k = 0;
	cin >> k;
	cout << "The position of the number " << k << " in the sequence r is:" << SeqSearch(r,n,k) << endl;
	cout << "test-end" << endl;
	return 0;
}
