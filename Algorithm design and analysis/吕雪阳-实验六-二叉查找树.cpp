#include <iostream>
using namespace std;
struct BiNode{
	int data;
	BiNode * lchild,* rchild;
}; 
BiNode * SearchBST(BiNode * root ,int k){
	if(root == NULL){
		return NULL;
	} else if(root->data == k){
		return root;
	}else if(k < root->data){
		return SearchBST(root->lchild,k);
	}else{
		return SearchBST(root->rchild,k);
	}
}
BiNode * InsertBST(BiNode * root,int data){
	if(root == NULL){
		root = new BiNode;
		root->data = data;
		root->lchild = NULL;
		root->rchild = NULL; 
		return root;
	}
	if(data <= root->data){
		root->lchild = InsertBST(root->lchild,data);
	} else {
		root->rchild = InsertBST(root->rchild,data);
	}
	return root;
} 
BiNode * createBST(int a[],int n){
	BiNode * T = NULL;
	for(int i = 0;i < n;i++){
		T = InsertBST(T,a[i]);
	}
	return T;
}
int main(int argc, char** argv) {
	int n = 0,k = 0,flag = 0;
	cout << "请输入元素的个数:" << endl;
	cin >> n;
	int a[n] = {0};
	cout << "请输入元素:" << endl;
	for(int i = 0;i < n;i++){
		cin >> a[i];
	}
	BiNode * root = createBST(a,n);
	cout << "请输入你想要查找的元素:" << endl;
	cin >> k;
	BiNode * search = SearchBST(root ,k);
	if(search != NULL){
		cout << "查找成功" << endl; 
	} else {
		cout << "查找失败没有这个元素" << endl; 
	}
	return 0;
}
