#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

const int BUCKET_NUM = 10;

// 数据结构的定义，explicit表示不允许构造函数发生隐式转换
struct ListNode {
    explicit ListNode(int i = 0): mData(i), mNext(NULL){};
    ListNode *mNext;
    int mData;
};

ListNode *insert(ListNode *head, int val)
{
    ListNode dummyNode;                         // 节点指针
    ListNode *newNode = new ListNode(val);      //待插入的新节点
    ListNode *pre , *curr;
    dummyNode.mNext = head;                     // 将指针指向链表头部
    pre = &dummyNode;                           // 设置临时指针。pre是当前检查元素的上一个元素
    curr = head;

    while (NULL != curr && curr->mData <= val)  // 末尾检测
    {
        pre = curr;                             // 不断向前循环，直到末尾或者找到不小于val的元素
        curr = curr -> mNext;       
    }

    newNode->mNext = curr;                      // 改变指针指向
    pre ->mNext =  newNode;
    return dummyNode.mNext;                     // 返回链表头节点
}

ListNode *Merge(ListNode *head1, ListNode *head2)   // 将head2合并到head1
{
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;               // 临时指针
    while(NULL != head1 && NULL != head2)       // 循环直到末尾
    {
        if (head1->mData <= head2 ->mData)      // 类似于归并排序
        {
            dummy->mNext = head1;
            head1 = head1 -> mNext;
        }else{
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;
    }
    if (NULL != head1) dummy->mNext = head1;
    if(NULL!=head2) dummy->mNext = head2;
    return dummyNode.mNext;
}

void BucketSort(int n,int arr[]){
	vector<ListNode*> buckets(BUCKET_NUM,(ListNode*)(0));

    // 将元素分配到桶
	for(int i=0;i<n;++i){
		int index = arr[i]%BUCKET_NUM;
		ListNode *head = buckets.at(index);
		buckets.at(index) = insert(head,arr[i]);
	}

    // 逐一合并各个桶
	ListNode *head = buckets.at(0);
	for(int i=1;i<BUCKET_NUM;++i){
		head = Merge(head,buckets.at(i));
	}
    //将排好序的元素写回原数组
	for(int i=0;i<n;++i){
		arr[i] = head->mData;
		head = head->mNext;
	}
}
int main(int argc,char** argv){
	int n = 20;
	int arr[n] = {63, 157, 189, 51, 101, 47, 141, 121, 157, 156, 194, 117, 98, 139, 67, 133, 181, 13, 28, 109};
	
	BucketSort(n,arr);
	cout << "输出结果为:" << endl;
	for(int i = 0;i < n;i++){
		cout << arr[i] << " ";
	}
 	return 0;
} 

