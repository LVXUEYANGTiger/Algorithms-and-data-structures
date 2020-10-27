#include <iostream>
using namespace std;
void ConvexHull(int x[],int y[],int n){
	int i ,j ,k ,sign1,sign2;
	int A,B,C;
	for(int i = 0;i < n -1;i++){
		for(j = i + 1;j < n;j++){
			sign1 = 0;
			sign2 = 0;
			A = y[i] - y[j];
			B = x[j] - x[i];
			C = x[i] * y [j] - x[j] * y[i];
			for(k = 0;k < n;k++){
				if(k != i && k != j){
					if(A * x[k] + B * y[k] + C > 0){
						sign1 = 1;
					} else {
						sign2 = 1;
					}
					if(sign1 == sign2){
						break;
					}
				} 
			}
		}
		if(k == n){
			cout << "(" << i << "," << j << ")" << endl; 
		}
	}
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	int n;
	cout << "Please enter the number of dot pairs:" << endl;
	cin >> n;
	int x[n],y[n];
	cout << "Enter x and y for " << n << " pairs of point pairs:" << endl; 
	for(int i = 0;i < n;i++){
		cin >> x[i] >> y[i];
	}
	ConvexHull(x,y,n);
	cout << "test-end" << endl;
	return 0;
}
