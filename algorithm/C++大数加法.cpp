#include <bits/stdc++.h>
using namespace std;
string add(string s1,string s2){
	// ���s1����s2Ϊ���򷵻�0 
	if(s1 == "" && s2 == ""){
		return "0";
	} 
	// s1Ϊ�շ���s2 
	if(s1 == ""){
		return s2;
	}
	// s2Ϊ�շ���s1
	if(s2 == ""){
		return s1;
	}
	 
	string maxx = s1,minn = s2;
	if(s1.length() < s2.length()){
		maxx = s2;
		minn = s1;
	}
	// maxx����������  minn������С���� 
	int a = maxx.length() - 1,b = minn.length() - 1;
	// maxx �� minn��� 
	for(int i = b;i >= 0;--i){
		maxx[a--] += minn[i] - '0';
	}
	// ���maxx�е�λ������9 ��һλ�� - 10 ��λ��1 
	for(int i = maxx.length() - 1; i > 0;--i){
		if(maxx[i] > '9'){
			maxx[i] -= 10;
			maxx[i - 1]++;
		}
	}
	// ��������λ������9�����λ-10��λ��1 
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
