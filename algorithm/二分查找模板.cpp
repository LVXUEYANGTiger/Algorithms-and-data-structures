#include <iostream>
using namespace std;
/**
 *  在[l, h)范围内查找值v,返回下标
 *  假设a数组已经按从小到大排序
 *  失败返回-1
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
 *  传入参数必须在a[l]与a[h]之间
 *  假设a数组已经按从小到大排序
 *  返回值l总是合理的
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
 *  在下标[l, r]范围内查找,返回下标
 *  假设a数组已经按从小到大排序
 *  失败返回-1
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
	cout << "test binarySearch_first开始" << endl;
	int nums[] = {0,1,2,3,4,6,7,9,11,15,23,45,45,78,98};
	int left = 0,right = sizeof(nums) / sizeof (nums[0]);
	int num = 11;
	cout << "数字" << num << " 在nums的下标是:" << binarySearch_first(nums,left,right,num) << endl;
	cout << "test binarySearch_first结束" << endl;
	
	cout << "test binarySearch_second开始" << endl;
	num = 10;
	cout << "在这个范围内" << "大于等于" << num << "的数字:"<< binarySearch_second(nums,left,right,num) << endl;
	cout << "test binarySearch_second结束" << endl;
	
	cout << "test binarySearch_third开始" << endl;
	num = 10;
	cout << "在这个范围内" << "小于等于" << num << "的最后一个数字:"<< nums[binarySearch_third(nums,left,right,num)] << endl;
	cout << "test binarySearch_third结束" << endl;
	return 0;
}
