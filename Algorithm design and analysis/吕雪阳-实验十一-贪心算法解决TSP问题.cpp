#include <iostream>
using namespace std;
#define n 5
int TSP(int arc[n][n],int w){
	// 假设从顶点w出发 
	int edgeCount = 0,TSPLength = 0;
	int min,u,v;
	int flag[n] = {0};
	u = w;
	flag[w] = 1;
	while(edgeCount < n - 1){
		min = 100;
		for(int j = 0;j < n;j++){
			if((flag[j] == 0) && (arc[u][j] != 0) && (arc[u][j] < min)){
				v= j;
				min = arc[u][j];
			}
		}
		TSPLength += arc[u][v];
		flag[v] = 1;
		edgeCount++;
		// 输出经过的路径 
		cout << u << "-->" << v << endl;
		// 下次从v出发 
		u = v; 
	} 
	// 输出最后的回边 
	cout << v << "-->" << w << endl;
	// 返回最短哈密顿回路的长度 
	return (TSPLength + arc[u][w]); 
} 
int main(int argc, char** argv) {
	int arc[n][n] = {0};
	cout << "请输入矩阵的元素:" << endl; 
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cin >> arc[i][j];
		}
	}
	int min = TSP(arc,0);
	cout << "最短哈密顿回路的长度为:" << min << endl;
	return 0;
}
