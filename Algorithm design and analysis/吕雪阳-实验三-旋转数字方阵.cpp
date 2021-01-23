#include <iostream>
using namespace std;
int data[255][255] = {0};
void Full(int number,int begin,int size){
	int i,j,k;
	if(size == 0){
		return;
	}
	if(size == 1){
		data[begin][begin] = number;
		return;
	}
	i = begin,j = begin;
	for(k = 0;k < size - 1;k++){
		data[i][j] = number;
		number++;
		i++;
	}
	for(k = 0;k < size - 1;k++){
		data[i][j] = number;
		number++;
		j++;
	}
	for(k = 0;k < size - 1;k++){
		data[i][j] = number;
		number++;
		i--;
	}
	for(k = 0;k < size -1;k++){
		data[i][j] = number;
		number++;
		j--;
	}
	Full(number,begin + 1,size - 2);
}
void print(int size){
	for(int i = 0;i < size;i++){
		for(int j = 0;j < size;j++){
			printf("%4d ",data[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}
int main(int argc, char** argv) 
{
	int size;
	cout << "请输入你想要输入矩阵的阶数size:" << endl;
	cin >> size; 
	cout << "填充开始" << endl;
	Full(1,0,size);
	cout << "填充结束" << endl; 
	print(size);
	return 0;
}
