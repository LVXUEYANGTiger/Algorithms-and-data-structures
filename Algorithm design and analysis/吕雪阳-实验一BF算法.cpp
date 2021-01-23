#include <iostream>
#include <cstring>
using namespace std;
int BF(char S[],char T[]){
	int index = 0;
	int i = 0,j = 0;
	
	while((S[i] != '\0') && (T[j] != '\0')){
		if(S[i] == T[j]){
			i++;
			j++;
		}else{
			cout << "主串S的下标" << i << "的字符" << S[i] << "和模式串T的下标" << j << "的字符" << T[j] << "不匹配" << endl; 
			index++;
			i = index;
			j = 0;
			cout << "主串S回溯到" << i << "的位置模式串T回溯到" << j <<  "的位置" << endl; 
		}
	}
	
	if(T[j] == '\0'){
		// 返回本趟匹配的开始位置(不是下标) 
		return index + 1;
	} else {
		cout << "没有匹配成功" << endl; 
		return 0;
	}
} 
int main(int argc, char** argv) 
{
	char S[255],T[255];
	cout << "请输入主串S(最多不超过255个字符):" << endl; 
	gets(S);
	cout << "请输入模式串T(最多不超过255个字符):" << endl; 
	gets(T);
	int flag =  BF(S,T);
	if(flag > 0){
		cout << "匹配成功" << endl;
		cout << "模式串T: " << T << "在主串S: " << S <<  "首次匹配的位置为:" << flag << endl;
	}
	return 0;
}
