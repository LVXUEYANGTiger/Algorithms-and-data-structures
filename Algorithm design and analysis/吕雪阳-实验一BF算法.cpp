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
			cout << "����S���±�" << i << "���ַ�" << S[i] << "��ģʽ��T���±�" << j << "���ַ�" << T[j] << "��ƥ��" << endl; 
			index++;
			i = index;
			j = 0;
			cout << "����S���ݵ�" << i << "��λ��ģʽ��T���ݵ�" << j <<  "��λ��" << endl; 
		}
	}
	
	if(T[j] == '\0'){
		// ���ر���ƥ��Ŀ�ʼλ��(�����±�) 
		return index + 1;
	} else {
		cout << "û��ƥ��ɹ�" << endl; 
		return 0;
	}
} 
int main(int argc, char** argv) 
{
	char S[255],T[255];
	cout << "����������S(��಻����255���ַ�):" << endl; 
	gets(S);
	cout << "������ģʽ��T(��಻����255���ַ�):" << endl; 
	gets(T);
	int flag =  BF(S,T);
	if(flag > 0){
		cout << "ƥ��ɹ�" << endl;
		cout << "ģʽ��T: " << T << "������S: " << S <<  "�״�ƥ���λ��Ϊ:" << flag << endl;
	}
	return 0;
}
