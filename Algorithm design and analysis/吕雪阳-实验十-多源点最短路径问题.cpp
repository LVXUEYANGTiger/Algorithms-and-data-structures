#include <iostream>
#define n 3
using namespace std;
// 1000为∞ 
void print(int dist[n][n]){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(dist[i][j] == 1000){
				printf("\t∞");
			} else {
				printf("%4d ",dist[i][j]);
			}
			
		}
		cout << endl;
	}
}
void Floyd(int arc[n][n],int dist[n][n]){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			dist[i][j] = arc[i][j];
		}
	}
	cout << "dist初始化为:" << endl;
	print(dist);
	for(int k = 0;k < n;k++){
		for(int i = 0;i < n;i++){
			for(int j = 0;j < n;j++){
				if(dist[i][k] + dist[k][j] < dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
					print(dist);
				}
				cout << "i:" << i << "经过k:" << k << "到达j:" << j << "的最短路径为:" << dist[i][j] << endl;
			}
		}
	} 
} 
int main(int argc, char** argv) 
{
	int arc[n][n] = {0};
	int dist[n][n];
	cout << "请输入数字" << endl;
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cin >> arc[i][j];
		}
	}
	Floyd(arc,dist);
	cout << "求解完成后的dist矩阵为:" << endl;
	print(dist);
	return 0;
}
