#include<bits/stdc++.h>
using namespace std;
struct node {
	int data;
	int i;
}a[7];
int p[10] = {0};
bool cmp(node a,node b){
    return b.data < a.data;
}
void MultiMachine(int t[], int n, int d[], int m) {
	int S[m][n];
	memset(S,-1,sizeof(S));
	int rear[m] = {0};
	int i,j,k;
	for(i=0; i<m; i++) {
		S[i][0]=p[i];
		rear[i]=0;
		d[i]=t[i];
	}
	for(i=m; i<n; i++) {
		for(j=0,k=1;k<m;k++) {
			if(d[k] < d[j]) {
				j=k;
			}
		}
		rear[j]++;
		S[j][rear[j]] = p[i];
		d[j]=d[j]+t[i];
	}
	for(i=0; i<m; i++) {
		cout << "����" << i << " ";
		for(j=0; S[i][j]>=0; j++) {
			cout << "��ҵ:" << S[i][j] << " ";
		} 
		cout << endl;
	}
}

int main(int argc,char** argv) {
	int m,n;
	
	cout << "�����������m����ҵ��n" << endl;
	cin >> m >> n;
	
	int d[m],t[n];
	
	cout << "����������" << m << "̨�����Ŀ���ʱ��" << endl; 
	for(int i=0; i<m; i++) {
		cin >> d[i];
	}
	cout << "����������" << n << "����ҵ�Ĵ���ʱ��" << endl; 
	for(int i=0; i<n; i++) {
		cin >> a[i].data;
		a[i].i = i;
	}
	sort(a,a+n,cmp); 
	
	for(int i=0; i<n; i++) {
		t[i] = a[i].data;
		p[i] = a[i].i;
	}
	MultiMachine(t,n,d,m);
	return 0;
}
