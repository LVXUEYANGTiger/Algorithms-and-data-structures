#include <bits/stdc++.h>
using namespace std; 
/**
������ֱ�۵ļ�������Ϊ 1 ��λ������������ 1 ֮��� 0�����磺10001000��
���������У��������ұߵ� 1 ��������������м�� 0��ֱ��������һ�� 1��Ч�ʻ�ߺܶࡣ
���ǲ������������λ�����㷨�Ļ���˼�롣���㷨ʹ���ض�����λ�����������Ƴ����� 1 �����ұ���λ��
�������� number �� number-1 ���� AND λ����ʱ��ԭ���� number �����ұߵ��� 1 �ı��ػᱻ�Ƴ���
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
// ��������֮��ĺ�������ָ�������������ֶ�Ӧ������λ��ͬ��λ�õ���Ŀ. 
int main(int argc, char** argv) 
{
	cout << "test" << endl;
	int x,y;
	cout << "������������:(���������):" << endl;
	cin >> x >> y;
	cout << (bitset<32>)x  << endl  << (bitset<32>)y << endl <<"�������ĺ�������Ϊ:" 
	<< hammingDistance(x,y) << endl;
	return 0;
}
