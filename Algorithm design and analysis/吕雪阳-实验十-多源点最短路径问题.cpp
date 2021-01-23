#include <iostream>
#define n 3
using namespace std;
// 1000Ϊ�� 
void print(int dist[n][n]){
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			if(dist[i][j] == 1000){
				printf("\t��");
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
	cout << "dist��ʼ��Ϊ:" << endl;
	print(dist);
	for(int k = 0;k < n;k++){
		for(int i = 0;i < n;i++){
			for(int j = 0;j < n;j++){
				if(dist[i][k] + dist[k][j] < dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
					print(dist);
				}
				cout << "i:" << i << "����k:" << k << "����j:" << j << "�����·��Ϊ:" << dist[i][j] << endl;
			}
		}
	} 
} 
int main(int argc, char** argv) 
{
	int arc[n][n] = {0};
	int dist[n][n];
	cout << "����������" << endl;
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cin >> arc[i][j];
		}
	}
	Floyd(arc,dist);
	cout << "�����ɺ��dist����Ϊ:" << endl;
	print(dist);
	return 0;
}
