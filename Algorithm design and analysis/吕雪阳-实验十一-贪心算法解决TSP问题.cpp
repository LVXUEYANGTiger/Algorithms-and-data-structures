#include <iostream>
using namespace std;
#define n 5
int TSP(int arc[n][n],int w){
	// ����Ӷ���w���� 
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
		// ���������·�� 
		cout << u << "-->" << v << endl;
		// �´δ�v���� 
		u = v; 
	} 
	// ������Ļر� 
	cout << v << "-->" << w << endl;
	// ������̹��ܶٻ�·�ĳ��� 
	return (TSPLength + arc[u][w]); 
} 
int main(int argc, char** argv) {
	int arc[n][n] = {0};
	cout << "����������Ԫ��:" << endl; 
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			cin >> arc[i][j];
		}
	}
	int min = TSP(arc,0);
	cout << "��̹��ܶٻ�·�ĳ���Ϊ:" << min << endl;
	return 0;
}
