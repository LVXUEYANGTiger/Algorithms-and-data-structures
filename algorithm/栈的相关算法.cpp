#include <iostream>
using namespace std; 
#include <stack>
/**
stack��һ���Ƚ����(First In Last Out,FILO)�����ݽṹ,
��ֻ��һ�����ڣ���ʽ��ͼ��ʾ��stack������������Ԫ��,
�Ƴ�Ԫ��,ȡ��ջ��Ԫ��,���ǳ��������,û���κ���������
���Դ�ȡstack������Ԫ�ء�����֮��stack�������б�����Ϊ��
��Ԫ������ջ�Ĳ�����Ϊ:push,��Ԫ���Ƴ�stack�Ĳ�����Ϊpop.
1.stack ���캯��
	stack<T> stkT; stack����ģ����ʵ�֣� stack�����Ĭ�Ϲ�����ʽ�� 
	stack(const stack &stk);// �������캯��
2.stack ��ֵ����
	stack& operator=(const stack &stk);// ���صȺŲ�����
3.stack ���ݴ�ȡ����
	push(elem);// ��ջ�����Ԫ��
	pop();// ��ջ���Ƴ���һ��Ԫ��
	top();// ����ջ��Ԫ��
4.stack ��С����
	empty();// �ж϶�ջ�Ƿ�Ϊ��
	size();// ���ض�ջ�Ĵ�С 
*/ 
int main(int argc, char** argv) 
{
	stack<int> stack;
	cout << "test" << endl;
	cout << "��ջ�������1-5:" << endl; 
	stack.push(1);
	stack.push(2); 
	stack.push(3);
	stack.push(4); 
	stack.push(5);
	cout << "ջ����:" << stack.top() << endl;
	stack.pop();
	cout << "�Ƴ�ջ��Ԫ��:" << endl;
	cout << "ջ����:" << stack.top() << endl;
	cout << "ջ�Ĵ�С��:" << stack.size() << endl;
	cout << "ջ�Ƿ�Ϊ��:" << stack.empty() << endl; 
	return 0;
}
