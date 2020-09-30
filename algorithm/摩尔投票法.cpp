#include <bits/stdc++.h>
using namespace std; 
/**
给定一个无序数组，有n个元素，找出其中的一个多数元素，
多数元素出现的次数大于? n/2 ?，注意数组中也可能不存在多数元素。
我们维护一个候选众数 candidate 和它出现的次数 count。初始时 candidate 可以为任意值，count 为 0；
我们遍历数组 nums 中的所有元素，对于每个元素 x，在判断 x 之前，如果 count 的值为 0，我们先将 x 
的值赋予 candidate，随后我们判断 x：
如果 x 与 candidate 相等，那么计数器 count 的值增加 1；
如果 x 与 candidate 不等，那么计数器 count 的值减少 1。
在遍历完成后，candidate 即为整个数组的众数。
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
	cout << "nums容器中众数为:" << majorityElement(nums) << endl;
	return 0;
}
