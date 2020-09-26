#include <iostream>
using namespace std;
/**
 *  ��[l, h)��Χ�ڲ���ֵv,�����±�
 *  ����a�����Ѿ�����С��������
 *  ʧ�ܷ���-1
*/

int binarySearch_first(int nums[],int left,int right,int num){
	int mid;
	while(left < right){
		mid = (left + right) >> 1;
		if(nums[mid] == num){
			return mid;
		}else if(nums[mid] < num){
			left = mid + 1;
		}else{
			right = mid;
		}
	}
	return -1;
}
/*
 *  �������������a[l]��a[h]֮��
 *  ����a�����Ѿ�����С��������
 *  ����ֵl���Ǻ����
 */
int binarySearch_second(int nums[],int left,int right,int num){
	int mid;
	while(left < right){
		mid = (left + right) >> 1;
		if(nums[mid] < num){
			left = mid + 1;
		}else{
			right = mid;
		}
	}
	return nums[left];
}
/*
 *  ���±�[l, r]��Χ�ڲ���,�����±�
 *  ����a�����Ѿ�����С��������
 *  ʧ�ܷ���-1
*/
int binarySearch_third(int nums[],int left,int right,int num){
	int mid;
	while(left < right){
		mid = (left + right + 1) >> 1;
		if(nums[mid] > num){
			right = mid - 1;
		}else{
			left = mid;
		}
	}
	if(nums[left] > num){
		return -1;
	}
	return left;
}
int main(int argc, char** argv) 
{
	cout << "test binarySearch_first��ʼ" << endl;
	int nums[] = {0,1,2,3,4,6,7,9,11,15,23,45,45,78,98};
	int left = 0,right = sizeof(nums) / sizeof (nums[0]);
	int num = 11;
	cout << "����" << num << " ��nums���±���:" << binarySearch_first(nums,left,right,num) << endl;
	cout << "test binarySearch_first����" << endl;
	
	cout << "test binarySearch_second��ʼ" << endl;
	num = 10;
	cout << "�������Χ��" << "���ڵ���" << num << "������:"<< binarySearch_second(nums,left,right,num) << endl;
	cout << "test binarySearch_second����" << endl;
	
	cout << "test binarySearch_third��ʼ" << endl;
	num = 10;
	cout << "�������Χ��" << "С�ڵ���" << num << "�����һ������:"<< nums[binarySearch_third(nums,left,right,num)] << endl;
	cout << "test binarySearch_third����" << endl;
	return 0;
}
