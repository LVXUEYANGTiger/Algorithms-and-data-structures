#include <iostream>
#include <math.h>
using namespace std;
typedef int var;
/**
要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的倍数剔除，剩下的就是素数。
同时考虑到大于2的偶数都不是素数，所以可以进一步优化成：
要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的奇数倍剔除，剩下的奇数就是素数。
那么思路就很清晰了：
1、判断n是否大于2，如果大于2了那么至少有一个小于n的质数2。
2、遍历大于1小于n的所有奇数i，如果i是质数，并且i不大于根号n，那么将i的所有奇数倍都标记成合数，如果i是质数但是i大于根号n那么直接转步骤3。
3、标记完成后质数个数+1。
4、循环结束后返回质数个数。
*/ 
int countPrime(var n){
	// 素数的个数 
	var result = 0; 
	// 求出这个数的平方根 
	var sqrt_n = (var)sqrt(n);
	// 标识数组初始化默认值都为 false，为质数标记
	bool b[n] = {false};
	// 如果大于 2 则一定拥有 2 这个质数
	if(n > 2){
		result++;
		b[2] = false; 
	} 
	// 从 3 开始遍历，且只遍历奇数
	for(int i = 3;i < n;i += 2){
		// 是质数
		if(!b[i]){
			if(i <= sqrt_n){
				for(int j = i;j * i < n;j += 2){
					// 将当前质数的奇数倍都设置成非质数标记 true
					b[i * j] = true;
				}
			}
			// 质数加1 
			result++;
		}
	}
	cout << "从0-" << n << "质数为:" << endl;
	for(int i = 2;i < n;i++){
		if(i == 2){
			cout << i << " ";
		}
		if(b[i] == false && i % 2 != 0){
			cout << i << " ";
		}
	}
	cout << endl;
	return result; 
} 
int main(int argc, char** argv) {
	cout << "质数测试开始" << endl;
	var n = 0;
	var result = 0;
	cout << "请输入一个数(正整数)" << endl;
	cin >> n;
	if(n == 1){
		cout << "1不是质数" << endl;
	} else {
		result = countPrime(n);
	}
	cout << "小于" << n << "的质数一共有" << result << "个" << endl;
	cout << "质数测试结束" << endl; 
	return 0;
}
