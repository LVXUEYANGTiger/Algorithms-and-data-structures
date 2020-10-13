#include <iostream>
using namespace std;
int CommFactor1(int m,int n){
	int i = 0,factor = 1;
	for(i = 2;i <= m && i <= n;i++){
		while(m % i == 0 && n % i == 0){
			factor = factor * i;
			m = m / i;
			n = n / i;
		}
	}
	return factor;
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	int n = 0,m = 0;
	cout << "Please enter two integers:" << endl;
	cin >> n >> m;
	int result = CommFactor1(m,n);
	cout << "The maximum common denominator of " << m << "and " << n << " is " << result << endl;
	cout << "test-end" << endl;
	return 0;
}
