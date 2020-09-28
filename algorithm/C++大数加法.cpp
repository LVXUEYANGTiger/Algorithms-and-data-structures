#include <bits/stdc++.h>
using namespace std;
string add(string s1,string s2){
	// 如果s1或者s2为空则返回0 
	if(s1 == "" && s2 == ""){
		return "0";
	} 
	// s1为空返回s2 
	if(s1 == ""){
		return s2;
	}
	// s2为空返回s1
	if(s2 == ""){
		return s1;
	}
	 
	string maxx = s1,minn = s2;
	if(s1.length() < s2.length()){
		maxx = s2;
		minn = s1;
	}
	// maxx就是最大的数  minn就是最小的数 
	int a = maxx.length() - 1,b = minn.length() - 1;
	// maxx 和 minn相加 
	for(int i = b;i >= 0;--i){
		maxx[a--] += minn[i] - '0';
	}
	// 如果maxx有的位数大于9 这一位数 - 10 进位加1 
	for(int i = maxx.length() - 1; i > 0;--i){
		if(maxx[i] > '9'){
			maxx[i] -= 10;
			maxx[i - 1]++;
		}
	}
	// 如果是最高位数大于9则最高位-10进位加1 
	if(maxx[0] > '9'){
		maxx[0] -= 10;
		maxx = '1' + maxx;
	}
	return maxx;
} 
int main(int argc, char** argv) 
{
	cout << "test" << endl;
	string s1 = "911111111",s2 = "222222222";
	cout << add(s1,s2) << endl; 
	return 0;
}
