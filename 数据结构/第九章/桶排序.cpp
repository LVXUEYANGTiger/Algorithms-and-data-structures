#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

const int BUCKET_NUM = 10;

// ���ݽṹ�Ķ��壬explicit��ʾ�������캯��������ʽת��
struct ListNode {
    explicit ListNode(int i = 0): mData(i), mNext(NULL){};
    ListNode *mNext;
    int mData;
};

ListNode *insert(ListNode *head, int val)
{
    ListNode dummyNode;                         // �ڵ�ָ��
    ListNode *newNode = new ListNode(val);      //��������½ڵ�
    ListNode *pre , *curr;
    dummyNode.mNext = head;                     // ��ָ��ָ������ͷ��
    pre = &dummyNode;                           // ������ʱָ�롣pre�ǵ�ǰ���Ԫ�ص���һ��Ԫ��
    curr = head;

    while (NULL != curr && curr->mData <= val)  // ĩβ���
    {
        pre = curr;                             // ������ǰѭ����ֱ��ĩβ�����ҵ���С��val��Ԫ��
        curr = curr -> mNext;       
    }

    newNode->mNext = curr;                      // �ı�ָ��ָ��
    pre ->mNext =  newNode;
    return dummyNode.mNext;                     // ��������ͷ�ڵ�
}

ListNode *Merge(ListNode *head1, ListNode *head2)   // ��head2�ϲ���head1
{
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;               // ��ʱָ��
    while(NULL != head1 && NULL != head2)       // ѭ��ֱ��ĩβ
    {
        if (head1->mData <= head2 ->mData)      // �����ڹ鲢����
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

    // ��Ԫ�ط��䵽Ͱ
	for(int i=0;i<n;++i){
		int index = arr[i]%BUCKET_NUM;
		ListNode *head = buckets.at(index);
		buckets.at(index) = insert(head,arr[i]);
	}

    // ��һ�ϲ�����Ͱ
	ListNode *head = buckets.at(0);
	for(int i=1;i<BUCKET_NUM;++i){
		head = Merge(head,buckets.at(i));
	}
    //���ź����Ԫ��д��ԭ����
	for(int i=0;i<n;++i){
		arr[i] = head->mData;
		head = head->mNext;
	}
}
int main(int argc,char** argv){
	int n = 20;
	int arr[n] = {63, 157, 189, 51, 101, 47, 141, 121, 157, 156, 194, 117, 98, 139, 67, 133, 181, 13, 28, 109};
	
	BucketSort(n,arr);
	cout << "������Ϊ:" << endl;
	for(int i = 0;i < n;i++){
		cout << arr[i] << " ";
	}
 	return 0;
} 

