#include <bits/stdc++.h>
using namespace std; 
/**
像人类直观的计数比特为 1 的位数，跳过两个 1 之间的 0。例如：10001000。
上面例子中，遇到最右边的 1 后，如果可以跳过中间的 0，直接跳到下一个 1，效率会高很多。
这是布赖恩·克尼根位计数算法的基本思想。该算法使用特定比特位和算术运算移除等于 1 的最右比特位。
当我们在 number 和 number-1 上做 AND 位运算时，原数字 number 的最右边等于 1 的比特会被移除。
*/ 
int hammingDistance(int x,int y){
	int ans = x ^ y;
	int distance = 0;
	while(ans != 0){
		distance += 1;
		ans = ans & (ans - 1);
	}
	return distance;
}
// 两个整数之间的汉明距离指的是这两个数字对应二进制位不同的位置的数目. 
int main(int argc, char** argv) 
{
	cout << "test" << endl;
	int x,y;
	cout << "请输入俩个数:(计算其距离):" << endl;
	cin >> x >> y;
	cout << (bitset<32>)x  << endl  << (bitset<32>)y << endl <<"两个数的汉明距离为:" 
	<< hammingDistance(x,y) << endl;
	return 0;
}
