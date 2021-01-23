#include <iostream>
using namespace std;
#define n 4
int DataTower(int d[n][n]){
	// 初始化 
	int maxAdd[n][n] = {0},path[n][n] = {0};
	int i,j;
	for(j = 0;j < n;j++){
		maxAdd[n - 1][j] = d[n - 1][j];
	} 
	for(i = n - 2;i >= 0;i--){
		for(j = 0;j <= i;j++){
			if(maxAdd[i + 1][j] > maxAdd[i + 1][j + 1]){
				maxAdd[i][j] =d[i][j] + maxAdd[i + 1][j];
				path[i][j] = j;
			} else {
				maxAdd[i][j] = d[i][j] + maxAdd[i + 1][j + 1];
				path[i][j] = j + 1;
			}
		}
	}
	cout << "路径为:" << d[0][0];
	j = path[0][0];
	for(i = 1;i < n;i++){
		cout << "-->" << d[i][j];
		j = path[i][j];
	}
	cout << endl;
	return maxAdd[0][0];
} 
int main(int argc, char** argv) {
	int d[n][n] = {0},max = 0;
	cout << "请输入数塔里面的元素:" << endl;
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cin >> d[i][j];
		}
	}
	max = DataTower(d);
	cout << "数塔的最大数值和:" << max << endl;
	return 0;
}
