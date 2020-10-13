#include <iostream>
using namespace std;
int CommFactor2(int m,int n){
	int r = m % n;
	while(r != 0){
		m = n;
		n = r;
		r = m % n;
	}
	return n;
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	int n = 0,m = 0;
	cout << "Please enter two integers:" << endl;
	cin >> n >> m;
	int result = CommFactor2(m,n);
	cout << "The maximum common denominator of " << m << "and " << n << " is " << result << endl;
	cout << "test-end" << endl;
	return 0;
	return 0;
}
