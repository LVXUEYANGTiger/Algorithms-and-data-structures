#include <iostream>
using namespace std; 
#include <stack>
/**
stack是一种先进后出(First In Last Out,FILO)的数据结构,
它只有一个出口，形式如图所示。stack容器允许新增元素,
移除元素,取得栈顶元素,但是除了最顶端外,没有任何其他方法
可以存取stack的其他元素。换言之，stack不允许有遍历行为。
有元素推入栈的操作称为:push,将元素推出stack的操作称为pop.
1.stack 构造函数
	stack<T> stkT; stack采用模板类实现， stack对象的默认构造形式： 
	stack(const stack &stk);// 拷贝构造函数
2.stack 赋值操作
	stack& operator=(const stack &stk);// 重载等号操作符
3.stack 数据存取操作
	push(elem);// 向栈顶添加元素
	pop();// 从栈顶移除第一个元素
	top();// 返回栈顶元素
4.stack 大小操作
	empty();// 判断堆栈是否为空
	size();// 返回堆栈的大小 
*/ 
int main(int argc, char** argv) 
{
	stack<int> stack;
	cout << "test" << endl;
	cout << "向栈里面添加1-5:" << endl; 
	stack.push(1);
	stack.push(2); 
	stack.push(3);
	stack.push(4); 
	stack.push(5);
	cout << "栈顶是:" << stack.top() << endl;
	stack.pop();
	cout << "移除栈顶元素:" << endl;
	cout << "栈顶是:" << stack.top() << endl;
	cout << "栈的大小是:" << stack.size() << endl;
	cout << "栈是否为空:" << stack.empty() << endl; 
	return 0;
}
