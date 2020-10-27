#include <iostream>
using namespace std;
int ClosestPoints(int x[],int y[],int n){
	int index1,index2;
	int d,minDist = 1000;
	for(int i = 0;i < n - 1;i++){
		for(int j = i + 1;j < n;j++){
			d = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			if(d < minDist){
				minDist = d;
				index1 = i;
				index2 = j;
			} 
		}
	}
	cout << "最近的点对是:" << index1 << "和" << index2 << endl;
	return minDist; 
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	cout << "Please enter the number of dot pairs:" << endl;
	int n;
	cin >> n;
	int x[n],y[n];
	cout << "请输入" << n << "对点对的值(x和y):" << endl;
	for(int i = 0;i < n;i++){
		cin >> x[i] >> y[i];
	}
	int min = ClosestPoints(x,y,n);
	cout << "The minimum Euclidean distance is:" << min << endl;
	cout << "test-end" << endl;
	return 0;
}
