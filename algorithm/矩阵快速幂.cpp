#include <bits/stdc++.h>
using namespace std;
typedef long long var;
#define maxn 2
// 结构体矩阵类型 
struct Matrix{
	var m[maxn][maxn];
}ans,res;
/**
计算矩阵乘法的函数,参数是矩阵
矩阵b和一个n代表这两个矩阵是几何矩阵 
*/
Matrix Mul(Matrix A,Matrix B){
	// 定义一个临时的矩阵,存放A * B的结果 
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
// 将ans矩阵变为单位阵
void initUnitization(){
	/**
	上面整数的幂的ans初始化为1,对于矩阵的
	乘法来说,ans应该初始化为单位阵,对于单元矩阵E
	任何矩阵A*E=A 
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
// 矩阵的初始化 
void init(Matrix &A){
	cout << "矩阵初始化开始" << endl;
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			cin >> A.m[i][j];
		}
	} 
	cout << "矩阵初始化结束" << endl;
}
//矩阵遍历 
void print(Matrix A){
	cout << "矩阵遍历开始" << endl;
	for(int i = 0;i < maxn;i++){
		for(int j = 0;j < maxn;j++){
			cout << A.m[i][j] << " ";
		}
		cout << endl;
	} 
	cout << "矩阵遍历结束" << endl; 
}
// 快速幂算法,求矩阵res的N次幂
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
	cout << "请输入矩阵的几次幂:" << endl;
	int n = 0;
	cin >> n;
	QuickPower(n);
	print(ans);
	return 0;
}
