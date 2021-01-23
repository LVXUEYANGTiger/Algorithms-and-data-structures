#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
int Comp(char a,char b){
	if(a > b){
		return 1;
	} else {
		return 0;
	}
} 
char Game(char r[],int n){
	int i = n;
	while(i > 1){
		i = i / 2;
		for(int j = 0;j < i;j++){
			cout << "在" << r[j + i] << "和" << r[j] << "的比赛中:" ; 
			if(Comp(r[j + i],r[j])){
				r[j] = r[j + i];
			}
			cout << r[j] << "胜出" << endl; 
		}
	}
	return r[0];
}
int main(int argc, char** argv) {
	char r[255];
	bool flag = false;
	cout << "请输入选手的名称:(每个选手是一个字符不用以空格隔开)" << endl;
	gets(r); 
	int len = strlen(r);
	for(int i = 0;i < len;i++){
		if(len == int(pow(2,i))){
			flag = true;
			break;
		}
	}
	char final; 
	if(flag){
		final = Game(r,len);
		cout << "最终的胜者为:" << final << endl;
	} else {
		cout << "选手的个数必须是2^k次方" << endl; 
	}

	return 0;
}
