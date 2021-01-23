#include<bits/stdc++.h>

using namespace std;

int a[100];
int b[100];

int main(int argc,char** argv) {
	int k;
	int res=0;
	cout << "请输入至少三维以上的两个点的所有坐标,请输入维数" << endl;
	cin >> k;
	for(int i=0; i<k; i++) {
		int m;
		cin >> m;
		a[i]=m;
	}
	for(int i=0; i<k; i++) {
		int m;
		cin >> m;
		b[i]=m;
	}
	
	for(int i=0; i<k; i++) {
		res += pow((a[i]-b[i]),2);
	}
	
	cout << sqrt(res);
	return 0;
}
