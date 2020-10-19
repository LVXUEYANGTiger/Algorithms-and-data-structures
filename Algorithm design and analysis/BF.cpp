#include <iostream>
using namespace std;
int BF(char S[],char T[]){
	int index = 0;
	int i = 0,j = 0;
	while(S[i] != '\0' && T[j] != '\0'){
		if(S[i] == T[j]){
			i++;
			j++;
		} else {
			index++;
			i = index;
			j = 0;
		}
	}
	if(T[j] == '\0'){
		return index + 1;
	} else {
		return 0;
	}
}
int main(int argc, char** argv) 
{
	cout << "test-start" << endl;
	cout << "Please enter the main string S:" << endl;
	char S[255];
	gets(S);
	cout << "Please enter the mode string T:" << endl;
	char T[255];
	gets(T);
	cout << "The position of the pattern string T on the main string S is " <<BF(S,T)<< endl;
	cout << "test-end" << endl;
	return 0;
}
