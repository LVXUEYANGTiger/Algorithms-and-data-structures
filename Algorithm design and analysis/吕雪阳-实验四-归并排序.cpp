#include <iostream>
using namespace std;
// r-m m+1 - t 
void Merge(int r[],int r1[],int s,int m,int t){
	int i = s,j = m + 1,k = s;
	while(i <= m && j <= t){
		if(r[i] <= r[j]){
			r1[k++] = r[i++];
		} else {
			r1[k++] = r[j++]; 
		}
	}
	while(i <= m){
		r1[k++] = r[i++];
	}
	while(j <= t){
		r1[k++] = r[j++];
	}
}
void MergeSort(int r[],int s,int t){
	int m,r1[1000];
	if(s == t){
		return;
	} else {
		m = (s + t) / 2;
		MergeSort(r,s,m);
		MergeSort(r,m + 1,t);
		Merge(r,r1,s,m,t);
		for(int i = s;i <= t;i++){
			r[i] = r1[i];
		}
	}
}
int main(int argc, char** argv) 
{
	cout << "��������Ҫ����Ԫ�صĸ���:" << endl;
	int n = 0;
	cin >> n;
	int r[n];
	cout << "������Ԫ��:" << endl;
	for(int i = 0;i < n;i++){
		cin >> r[i];
	}
	MergeSort(r,0,n);
	cout << "�����źõ�����Ϊ:" << endl;
	for(int i = 0;i < n;i++){
		cout << r[i] << " "; 
	}
	return 0;
}
