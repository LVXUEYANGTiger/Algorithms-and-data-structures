#include <bits/stdc++.h>
using namespace std; 
/**
����һ���������飬��n��Ԫ�أ��ҳ����е�һ������Ԫ�أ�
����Ԫ�س��ֵĴ�������? n/2 ?��ע��������Ҳ���ܲ����ڶ���Ԫ�ء�
����ά��һ����ѡ���� candidate �������ֵĴ��� count����ʼʱ candidate ����Ϊ����ֵ��count Ϊ 0��
���Ǳ������� nums �е�����Ԫ�أ�����ÿ��Ԫ�� x�����ж� x ֮ǰ����� count ��ֵΪ 0�������Ƚ� x 
��ֵ���� candidate����������ж� x��
��� x �� candidate ��ȣ���ô������ count ��ֵ���� 1��
��� x �� candidate ���ȣ���ô������ count ��ֵ���� 1��
�ڱ�����ɺ�candidate ��Ϊ���������������
*/
int majorityElement(vector<int>& nums){
	int candidate = -1;
	int count = 0;
	for(int num : nums){
		if(num == candidate){
			count++;
		}else if(--count < 0){
			candidate = num;
			count = 1;
		}
	}
	return candidate;	
} 
int main(int argc, char** argv) {
	cout << "test" << endl;
	vector<int> nums = {1,1,1,1,2,3,4,1,1,1,1,7,8,9};
	cout << "nums����������Ϊ:" << majorityElement(nums) << endl;
	return 0;
}
