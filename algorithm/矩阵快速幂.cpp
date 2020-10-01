#include <bits/stdc++.h>
using namespace std;
typedef long long var;
#define maxn 2
// �ṹ��������� 
struct Matrix{
	var m[maxn][maxn];
}ans,res;
/**
�������˷��ĺ���,�����Ǿ���
����b��һ��n���������������Ǽ��ξ��� 
*/
Matrix Mul(Matrix A,Matrix B){
	// ����һ����ʱ�ľ���,���A * B�Ľ�� 
	Matrix temp; 
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			temp.m[i][j] = 0;
		}
	} 
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			for(int k = 0;k < maxn;k++){
				temp.m[i][j] += A.m[i][k] * B.m[k][j];
			}
		}
	}
	return temp;
}
// ��ans�����Ϊ��λ��
void initUnitization(){
	/**
	�����������ݵ�ans��ʼ��Ϊ1,���ھ����
	�˷���˵,ansӦ�ó�ʼ��Ϊ��λ��,���ڵ�Ԫ����E
	�κξ���A*E=A 
	*/
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			if(i == j){
				ans.m[i][j] = 1;
			}else{
				ans.m[i][j] = 0;
			}
		}
	}
} 
// ����ĳ�ʼ�� 
void init(Matrix &A){
	cout << "�����ʼ����ʼ" << endl;
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			cin >> A.m[i][j];
		}
	} 
	cout << "�����ʼ������" << endl;
}
//������� 
void print(Matrix A){
	cout << "���������ʼ" << endl;
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			cout << A.m[i][j] << " ";
		}
		cout << endl;
	} 
	cout << "�����������" << endl; 
}
// �������㷨,�����res��N����
void QuickPower(int N){
	
	while(N){
		if(N & 1){
			ans = Mul(ans,res);
		} 
		res = Mul(res,res);
		N = N >> 1;
	
	}
} 
int main(int argc, char** argv) 
{
	cout << "test" << endl;
	init(res);
	print(res);
	initUnitization();
	print(ans);
	cout << "���������ļ�����:" << endl;
	int n = 0;
	cin >> n;
	QuickPower(n);
	print(ans);
	return 0;
}
