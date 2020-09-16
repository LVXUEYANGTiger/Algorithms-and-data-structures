#include <iostream>
#include <math.h>
using namespace std;
typedef int var;
/**
要得到自然数n以内的全部素数，必须把不大于根号n的所有素数的倍数剔除，剩下的就是素数。
*/ 
int countPrime(var n){
	// 素数的个数 
	var result = 0; 
	// 标识数组初始化默认值都为 false，为质数标记
	bool b[n] = {false};

	for(int i = 2;i * i< n;i++){
		// 是质数
		if(!b[i]){
				for(int j = i * i;j < n;j += i){
					b[j] = true;
				}
			}
			
		}
	
	cout << "从0-" << n << "质数为:" << endl;
	for(int i = 2;i < n;i++){
		if(b[i] == false){
			result++;
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

