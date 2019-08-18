//-------------------------------------------------可变参数详解--------------------------------------------------------
 
//一、是什么
//我们学习C语言时最经常使用printf()函数，但我们很少了解其原型。其实printf()的参数就是可变参数，想想看，我们可以利用它打印出各种类型的数据。下面我们来看看它的原型：
//int printf( const char* format, ...);
//它的第一个参数是format，属于固定参数,后面跟的参数的个数和类型都是可变的（用三个点“…”做参数占位符）,实际调用时可以有以下的形式: 
//printf("%d",i); 
//printf("%s",s); 
//printf("the number is %d ,string is:%s", i, s); 
//那么它的原型是怎样实现的呢？我今天在看内核代码时碰到了vsprintf，花了大半天时间，终于把它搞的有点明白了。
//二、先看两个例子
//不必弄懂，先大致了解其用法，继续往下看。
//①一个简单的可变参数的C函数 
//在函数simple_va_fun参数列表中至少有一个整数参数,其后是占位符…表示后面参数的个数不定.。在这个例子里，所有输入参数必须都是整数，函数的功能只是打印所有参数的值。
//#include <stdio.h>
//#include <stdarg.h>
//void simple_va_fun(int start, ...) 
//{ 
//       va_list arg_ptr; 
//       int nArgValue =start;
//       int nArgCout=0;     //可变参数的数目
//       va_start(arg_ptr,start); //以固定参数的地址为起点确定变参的内存起始地址。
//       do 
//       {
//              ++nArgCout;
//              printf("the %d th arg: %d\n",nArgCout,nArgValue);     //输出各参数的值
//              nArgValue = va_arg(arg_ptr,int);                      //得到下一个可变参数的值
//       } while(nArgValue != -1);                
//       return; 
//}
//int main(int argc, char* argv[])
//{
//       simple_va_fun(100,-1); 
//       simple_va_fun(100,200,-1); 
//       return 0;
//}
// 
//②格式化到一个文件流，可用于日志文件
//FILE *logfile;
//int WriteLog(const char * format, ...)
//{
//va_list arg_ptr;
//va_start(arg_ptr, format);
//int nWrittenBytes = vfprintf(logfile, format, arg_ptr);
//va_end(arg_ptr);
//return nWrittenBytes;
//}
// 
//稍作解释上面两个例子。
//【这部分的引用地址http://www.cppblog.com/lmlf001/archive/2006/04/19/5874.html】
//从这个函数的实现可以看到,我们使用可变参数应该有以下步骤: 
//⑴在程序中用到了以下这些宏: 
//void va_start( va_list arg_ptr, prev_param ); 
//type va_arg( va_list arg_ptr, type ); 
//void va_end( va_list arg_ptr ); 
//va在这里是variable-argument(可变参数)的意思. 
//这些宏定义在stdarg.h中,所以用到可变参数的程序应该包含这个头文件.
//⑵函数里首先定义一个va_list型的变量,这里是arg_ptr,这个变量是存储参数地址的指针.因为得到参数的地址之后，再结合参数的类型，才能得到参数的值。
//⑶然后用va_start宏初始化⑵中定义的变量arg_ptr,这个宏的第二个参数是可变参数列表的前一个参数,即最后一个固定参数. 
//⑷然后依次用va_arg宏使arg_ptr返回可变参数的地址,得到这个地址之后，结合参数的类型，就可以得到参数的值。
//⑸设定结束条件，①是判断参数值是否为-1。注意被调的函数在调用时是不知道可变参数的正确数目的，程序员必须自己在代码中指明结束条件。②是调用宏va_end。
//三、剖析可变参数真相
//1. va_* 宏定义
//我们已经知道va_start,va_arg,va_end是在stdarg.h中被定义成宏的, 由于1)硬件平台的
//不同 2)编译器的不同,所以定义的宏也有所不同。下面看一下VC++6.0中stdarg.h里的代码
//（文件的路径为VC安装目录下的\vc98\ include\stdarg.h）
//typedef char *  va_list;
//#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
//#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
//#define va_end(ap)      ( ap = (va_list)0 )
//再来看看linux中的定义
//typedef char *va_list;
//#define __va_rounded_size(TYPE) (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))
//#define va_start(AP, LASTARG) (AP=((char*)&(LASTARG) + __va_rounded_size (LASTARG))
//void va_end (va_list);
//#define va_end(AP) （AP= (char *)0）
//#define va_arg(AP,TYPE) (AP+=__va_rounded_size(TYPE),\
//*((TYPE *)(AP - __va_rounded_size (TYPE))))
//要理解上面这些宏定义的意思，需要首先了解：
//①栈的方向②参数的入栈顺序③CPU的对齐方式④内存地址的表达方式。
//2.栈——以Intel 32位的CPU为分析基础
//在Intel CPU中，栈的生长方向是向下的，即栈底在高地址，而栈顶在低地址；从栈底向栈顶看过去，地址是从高地址走向低地址的，因为称它为向下生长，如图。
// 
//【图1 引用自 http://www.yuanma.org/data/2008/0504/article_3027_1.htm，这部分内容，我认为作者讲的很详细，所以引来共享】
//从上面压栈前后的两个图可明显看到栈的生长方向，在Intel 32位的CPU中，windown或linux都使用了它的保护模式，ss指定栈所有在的段，ebp指向栈基址，esp指向栈顶。显然执行push指令后，esp的值会减4，而pop后，esp值增加4。 栈中每个元素存放空间的大小决定push或pop指令后esp值增减和幅度。Intel 32位CPU中的栈元素大小为16位或32位，由定义堆栈段时定义。在Window和Linux系统中，内核代码已定义好栈元素的大小为32位，即一个字长(sizeof(int))。因此用户空间程栈元素的大小肯定为32位，这样每个栈元素的地址向4字节对齐。
//C语言的函数调用约定对编写可变参数函数是非常重要的，只有清楚了，才更欲心所欲地控制程序。在高级程序设计语言中，函数调用约定有如下几种，stdcall，cdecl，fastcall ,thiscal,naked call。cdel是C语言中的标准调用约定，如果在定义函数中不指明调用约定(在函数名前加上约定名称即可），那编译器认为是cdel约定，从上面的几种约定来看，只有cdel约定才可以定义可变参数函数。下面是cdel约定的重要特征：如果函数A调用函数B，那么称函数A为调用者(caller)，函数B称为被调用者(callee)。caller把向callee传递的参数存放在栈中，并且压栈顺序按参数列表中从右向左的顺序；callee不负责清理栈，而是由caller清理。 我们用一个简单的例子来说明问题，并采用Nasm的汇编格式写相应的汇编代码，程序段如下： 
//void callee(int a, int b)
//{
//int c = 0;
//c = a +b;
//} 
//void caller()
//{
//callee(1,2);
//} 
//来分析一下在调用过程发生了什么事情。程序执行点来到caller时，那将要执行调用callee函数，在跳到callee函数前，它先要把传递的参数压到栈上，并按右到左的顺序，即翻译成汇编指令就是push 2； push 1；
//
//图2
//函数栈如图中（a）所示。接着跳到callee函数，即指令call calle。CPU在执行call时，先把当前的EIP寄存器的值压到栈中，然后把EIP值设为callee(地址),这样，栈的图变为如图2(b)。程序执行点跳到了callee函数的第一条指令。C语言在函数调用时，每个函数占用的栈段称为stack frame。用ebp来记住函数stack frame的起始地址。故在执行callee时，最前的两条指令为：
//push ebp
//mov esp, ebp
//经过这两条语句后，callee函数的stack frame就建好了，栈的最新情况如图2(c)所示。 函数callee定义了一个局部变量int c，该变量的储存空间分配在callee函数占用的栈中，大小为4字节(insizeof int)。那么callee会在如下指令：
//sub esp, 4
//mov [ebp-4], 0
//这样栈的情况又发生了变化，最新情况如图2(d)所示。注意esp总是指向栈顶，而ebp作为函数的stack frame基址起到很大的作用。ebp地址向下的空间用于存放局部变量，而它向上的空间存放的是caller传递过来的参数，当然编译器会记住变量c相对ebp的地址偏移量，在这里为-4。跟着执行c = a + b语句，那么指令代码应该类似于：
//mov eax , [ebp +  8] ；这里用eax存放第一个传递进来的参数，记住第一个参数与ebp的偏移量肯定为8
//add eax,  [ebp + 12] ;第二个参数与ebp的偏移量为12，故计算eax = a+b
//mov [ebp -4], eax  ;执行 c = eax, 即c = a+b
//栈又有了新了变化，如图2(e)。至此，函数callee的计算指令执行完毕，但还要做一些事情：释放局部变量占用的栈空间，销除函数的stack-frame过程会生成如下指令：
//mov esp, ebp;把局部变量占用的空间全部略过，即不再使用，ebp以下的空间全部用于局部变量
//pop ebp；弹出caller函数的stack-frame 基址
//在Intel CPU里上面两条指令可以用指令leave来代替，功能是一样。这样栈的内容如图2(f)所示。最后，要返回到caller函数，因此callee的最后一条指令是
//ret
//ret指令用于把栈上的保存的断点弹出到EIP寄存器，新的栈内容如图2(g)所示。函数callee的调用与返回全部结束，跟着下来是执行call callee的下一条语句。
//从caller函数调用callee前，把传递的参数压到栈中，并且按从右到左的顺序；函数返回时，callee并不清理栈，而是由caller清楚传递参数所占用的栈（如上图，函数返回时，1和2还放在栈中，让caller清理）。栈元素的大小为4个字节，每个参数占用栈空间大小为4字节的倍数，并且任何两个参数都不能共用同一个栈元素。
//从C语言的函数调用约定可知，参数列表从右向左依次压栈，故可变参数压在栈的地址比最后一个命名参数还大，如下图3所示：
//
//由图3可知，最后一个命名参数a上面都放着可变参数，每个参数占用栈的大小必为4的倍数。因此：可变参数1的地址 = 参数a的地址 + a占用栈的大小，可变参数2的地址 = 可变参数1的地址 + 可变参数1占用栈的大小，可变参数3的地址 = 可变参数2的地址 + 可变参数2占用栈的大小，依此类推。如何计算每个参数占用栈的大小呢？
//3.数据对齐问题
//对于两个正整数 x, n 总存在整数 q, r 使得
//x = nq + r, 其中  0<= r <n                  //最小非负剩余
//q, r 是唯一确定的。q = [x/n], r = x - n[x/n]. 这个是带余除法的一个简单形式。在 c 语言中， q, r 容易计算出来： q = x/n, r = x % n.
// 
//所谓把 x 按 n 对齐指的是：若 r=0, 取 qn, 若 r>0, 取 (q+1)n. 这也相当于把 x 表示为：
//x = nq + r', 其中 -n < r' <=0                //最大非正剩余   
//nq 是我们所求。关键是如何用 c 语言计算它。由于我们能处理标准的带余除法，所以可以把这个式子转换成一个标准的带余除法，然后加以处理：
//x+n = qn + (n+r')，其中 0<n+r'<=n            //最大正剩余
//x+n-1 = qn + (n+r'-1), 其中 0<= n+r'-1 <n    //最小非负剩余
//所以 qn = [(x+n-1)/n]n. 用 c 语言计算就是：
//((x+n-1)/n)*n
//若 n 是 2 的方幂, 比如 2^m，则除为右移 m 位，乘为左移 m 位。所以把 x+n-1 的最低 m 个二进制位清 0就可以了。得到：
//(x+n-1) & (~(n-1))
//【来自CSDN博客：http://blog.csdn.net/swell624/archive/2008/11/03/3210779.aspx】
//根据这些推导，相信已经了解#define __va_rounded_size(TYPE)  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))的涵义。
//       4.再看va_* 宏定义
//va_start(va_list ap, last)
//last为最后一个命名参数，va_start宏使ap记录下第一个可变参数的地址，原理与“可变参数1的地址 = 参数a的地址 + a占用栈的大小”相同。从ap记录的内存地址开始，认为参数的数据类型为type并把它的值读出来；把ap记录的地址指向下一个参数，即ap记录的地址 += occupy_stack(type)
//va_arg(va_lit ap, type)
//这里是获得可变参数的值，具体工作是：从ap所指向的栈内存中读取类型为type的参数，并让ap根据type的大小记录它的下一个可变参数地址，便于再次使用va_arg宏。从ap记录的内存地址开始，认为存的数据类型为type并把它的值读出来；把ap记录的地址指向下一个参数，即ap记录的地址 += occupy_stack(type)
//va_end(va_list ap)
//用于“释放”ap变量，它与va_start对称使用。在同一个函数内有va_start必须有va_end。
//5.可变参数函数问题
//考虑了参数大小和数据对齐问题，使得可变参数的类型不但可以是基本类型，同样适用于用户定义类型。值的注意的是，如果是用户定义类型，最好用typedef定义的名字作为类型名，这样就会减少在va_arg进行宏展开时出错的机率。
//在可变参数函数中，由va_list变量来记录（或获得）可变参数部分，但是va_list中并没有记录下它们的名字，事实上也是不可能的。要想把可变参数部分传递给下一个函数，唯有通过va_list变量去传递，而原来定义的函数用"..."来表示可变参数部分，而不是用va_list来表示。为了方便程序的标准化，ANSIC在标准库代码中就作出了很好的榜样：在任何形如: type fun( type arg1, type arg2, ...)的函数，都同时定义一个与它功能完全一样的函数，但用va_list类型来替换"..."，即type fun(type arg1, type arg2, va_list ap)。以printf函数为例：
//int printf(const char *format, ...);     
//int vprintf(const char *format, va_list ap);
//第一个函数用"..."表示可变参数，第二个用va_list类型表示可变参数，目的是用于被其它可变参数调用，两者在功能功能上是完全上一样。只是在函数名字相差一个'"v"字母。
//四、可变参数函数的应用
//一个<The C Programming Language>中的例子：一个简单的实现printf函数的例子：
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
///* minprintf: minimal printf with variable argument list */
//void minprintf(char *fmt, ...)
//{
//       va_list ap; /* points to each unnamed arg in turn */
//       char *p, *sval;
//       int ival;
//       double dval;
//       va_start(ap, fmt); /* make ap point to 1st unnamed arg */
//       for (p = fmt; *p; p++) {
//              if (*p != '%') {
//                     putchar(*p);
//                     continue;
//              }
//              switch (*++p) {
//                 case 'd':
//                        ival = va_arg(ap, int);
//                        printf("%d", ival);
//                        break;
//                 case 'x':
//                        ival=va_arg(ap,int);
//                        printf("%#x",ival);
//                        break;
//                 case 'f':
//                        dval = va_arg(ap, double);
//                        printf("%f", dval);
//                        break;
//                 case 's':
//                        for (sval = va_arg(ap, char *); *sval; sval++)
//                               putchar(*sval);
//                        break;
//                 default:
//                        putchar(*p);
//                        break;
//              }
//       }
//       va_end(ap); /* clean up when done */
//}
// 
//int main(int argc, char* argv[])
//{
//       int i = 1234;
//       int j = 5678;
//       char *s="nihao";
//       double f=0.11f;
// 
//       minprintf("the first test:i=%d\n",i,j); 
//       minprintf("the secend test:i=%d; %x;j=%d;",i,0xabcd,j); 
//       minprintf("the 3rd test:s=%s\n",s); 
//       minprintf("the 4th test:f=%f\n",f); 
//       minprintf("the 5th test:s=%s,f=%f\n",s,f); 
//       system("pause");
//       return 0;
//}
// 
//不使用va_*宏定义的实现：
//void minprintf(char* fmt, ...) //一个简单的类似于printf的实现不过参数必须都是int 类型
//{ 
//       char* pArg=NULL;               //等价于原来的va_list 
//       char c;
//       pArg = (char*) &fmt; //注意不要写成p = fmt !因为这里要对//参数取址，而不是取值
//       pArg += sizeof(fmt);         //等价于原来的va_start        
//       do
//       {
//              c =*fmt;
//              if (c != '%')
//              {
//                     putchar(c);            //照原样输出字符
//              }
//              else
//              {
//                     //按格式字符输出数据
//                     switch(*++fmt) 
//                     {
//                     case 'd':
//                            printf("%d",*((int*)pArg));           
//                            break;
//                     case 'x':
//                            printf("%#x",*((int*)pArg));
//                            break;
//                     default:
//                            break;
//                     } 
//                     pArg += sizeof(int);               //等价于原来的va_arg
//              }
//              ++fmt;
//       }while (*fmt != '\0'); 
//       pArg = NULL;                               //等价于va_end
//       return; 
//}


//-------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数
#include <stdarg.h>      //标准头文件，提供宏va_start、va_arg和va_end,用于存取变长参数表
						//c允许定义可接受一个可变参数列表的函数。而且是自己定义的额外的函数。
						//stdarg.h定义的宏。允许在任何时候从头到尾地便利一个附加参数列表。
						//在遇到每一个参数之前，必须知道它的类型，但在一个给定的调用发生之前，不必知道它的细节。
						//宏va_start，一个函数必须至少声明一个固定的参数。宏va_start引用了最后一个固定参数所以它能够对可变参数进行定位,
						//访问所有未命名的参数之前调用宏。对类型va_list ap初始化。
						//宏va_arg,每一次调用都会修改ap，每次调用这个宏展开的表达式的类型和值跟调用的下一个参数的相同。
						//第一次调用返回parmN后面的第一个参数。
						//宏va_end，一个函数在返回到它的调用者之前一定要调用va_end。
						//stdarg.h声明了一种类型，定义了3个宏，这样就可以提前访问一个参数表，调用函数在编译时并不知道这个参数表中参数的数目和类型。
						//在...之前的那个参数起着特殊的作用，记作parmN。
						//声明类型va_list。
						//可重复使用。
						//c标准定义，一个可变参数表在内存中占据了一个连续的字符数组；
						//后继的参数占据着字符数组更高为位。
						//一个参数占据的空间开始于2^N字节的整数倍的存储边界。
						//存储空间的大小是可以表示这个参数2^N字节的最小倍数。
						//存储空间留下的任何间隙总是在参数数据对象的开头或者结尾。

#include <math.h>        //使用了其中的两个符号常量OVERFLOW和UNDERFLOW 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define TRUE 1               //表示逻辑真的常量 
#define FALSE 0              //表示逻辑假的常量

#define MAX_ARRAY_DIM 8      //假设数组维数最大值为8

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //状态标志 
typedef int  ElemType;    //元素类型 

//---------------------数组的顺序存储表示---------------------- 
typedef struct{
    ElemType * base;      //数组元素基址，由InitArray分配
    //这个指针指向的内存空间用于存放数组中的元素。
    //其大小由数组的维数和维界决定。 

    int dim;              //数组维数

    int * bounds;         //数组维界基址，由InitArray分配
    //维界是指数组每一维的长度，比如A[3][4][5]
    //那么需要三个int变量分别存储3、4、5这3个值
    //由于数组维数是不固定的，所以这块内存需动态分配

    int * constants;      	//数组映像函数常量基址，指向一个存放每一维起始地址的数组的起始地址由InitArray分配 
						    //数组印象函数常量是配合数组的映像函数来定位数组元素的
						    //映像常量的值在确定数组维数时就可以确定，提前将它们算出来
						    //并储存在一段连续的内存空间中有利于元素定位操作时计算
						    //元素的相对位置。 

}Array;

//----------------------数组的基本操作------------------------

/*
    函数：InitArray
    参数：Array &A 数组引用
          int dim  数组维数
          ... 可变参数，数组每一维的大小 
    返回值：状态码，操作成功返回OK，操作失败返回ERROR 
    作用：若维数dim和随后的各维长度合法，则构造相应的数组A，并返回OK
*/
Status InitArray(Array &A, int dim, ...){  //初始化数组当我们无法列传递给函数的所有的实参类型和数目时，可以用省略号指定参数列表。

//	------------------------------------------------------------------------------------------
//函数参数时，参数存放在内存的堆栈段中，在函数执行的时候，以数据结构栈的形式进行传递的，从右至左依次入栈。
//因此，从理论上说，我们只要探测到任意一个变量的地址，并且知道其他变量的类型，通过指针位移运算，就可以顺藤摸瓜的找到其他变量了。
//----------------------------------------------------------------------------------------------
    //ap指向可变参数列表 
    va_list ap;

    //检查参数维数dim是否合法 
    if(dim < 1 || dim > MAX_ARRAY_DIM) { //维数参数非法

        //操作失败 
        return ERROR;
    }//if

    //确定数组的维数 
    A.dim = dim;

    //根据维数dim分配数组维界基址的空间 
    if(!(A.bounds = (int *)malloc(dim * sizeof(int)))) {
        printf("内存分配失败！\n");
        //math.h头文件中定义OVERFLOW的值为3
        //OVERFLOW表示上溢错误 
        exit(OVERFLOW);
    }//if

    //若各维长度合法，则存入A.bounds,并求出A的元素总数elemtotal
    int elemtotal = 1;

    //接下来需要根据可变参数传递的每一维的大小计算出数组中的元素总数
    //在这个过程中需要多次读取可变参数的值，所以要调用va_arg宏来
    //循环获取数组每一维的大小bounds，所以va_start宏要放在循环的外面。
    //注：调用va_arg宏获取可变参数之前要调用一下va_start宏。 
    //ap为va_list类型，是可变参数的前一个参数，也就是存放数组维数的dim。
    //在使用可变参数后，对函数的参数列表的声明顺序就有要求了
    //可变参数必须声明成最后一个参数，否则没办法确定传入的值
    //是否应该传给可变参数。而dim必须是可变参数的前一个参数
    //中间不可以有其他参数。 
    //第二个参数就是我们将要在各个操作中使用的可变参数
	//va_start，函数名称，读取可变参数的过程其实就是在堆栈中，
	//使用指针,遍历堆栈段中的参数列表,从低地址到高地址一个一个地把参数内容读出来的过程·
    va_start(ap, dim);

    //根据数组的维数初始化每一维的大小（维界） 
    for(int i = 0; i < dim; ++i){

        //调用va_arg宏从可变参数中取出每一维的大小bounds，类型是int 
        A.bounds[i] = va_arg(ap, int);

        //A.bounds[i] < 0表示出现了下溢错误，此时应立即终止程序执行
        //可变参数传入的值要进行检查后才可以使用 
        if(A.bounds[i] < 0){
            //math.h头文件中定义UNDERFLOW的值为4
            //UNDERFLOW表示下溢错误 
            return UNDERFLOW;
        }//if 

        //元素总数累乘，比如数组A[3][4][2]的元素总数就是
        //3*4*2 = 24 所以算数组元素总数就是每一维大小相乘。 
        elemtotal *= A.bounds[i]; 
    }//for 

    //获取可变参数结束调用va_end宏 
    va_end(ap);

    //计算出数组元素总数之后就要申请相同大小的存储数组元素的内存空间，
    //以便容纳数组中的全部元素 
    if(!(A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType)))){
        printf("内存分配失败！\n");
        //math.h头文件中定义OVERFLOW的值为3
        //OVERFLOW表示上溢错误
        exit(OVERFLOW);
    }//if

    //申请映像函数常量的存储空间，申请存储单元个数等于数组维数 
    if(!(A.constants = (int *)malloc(dim * sizeof(int)))){
        printf("内存分配失败！\n");
        //math.h头文件中定义OVERFLOW的值为3
        //OVERFLOW表示上溢错误
        exit(OVERFLOW);
    }//if

    //求映像函数的常数ci,并存入A.constants[i-1],i=1,...,dim
    //映像函数的常数ci的作用是方便的给元素定位，具体公式n维数组转换为一维的公式 
    //只要算出ci的值，就可以轻松得到某个元素在A.base指示的一维存储空间
    //中的相对地址off，然后就可以通过A.base[off]获取元素的值。 
    A.constants[dim - 1] = 1;  //L=1,指针的增减以元素大小为单位
    for(int i = dim - 2; i >= 0; --i) { 
        A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
    }//for

    //操作成功 
    return OK; 
}//InitArray   

/*
    函数：DestroyArray
    参数：Array &A 数组引用
    返回值：状态码，操作成功返回OK，操作失败返回ERROR 
    作用：销毁数组A 
*/
Status DestroyArray(Array &A){

    //1.释放存储数组元素的A.base指示的内存空间

    //检查此段内存区域是否存在 
    if(!A.base) { //if(!A.base) <=>  if(A.base == NULL)
        return ERROR;
    }//if 

    //释放A.base指向的存储区域的内存空间 
    free(A.base);

    //A.base指针置空，释放掉指针变量本身的内存空间 
    A.base = NULL; 

    //2.释放存储数组维界（每一维大小）的A.bounds指示的内存空间 

    //检查此段内存区域是否存在 
    if(!A.bounds) {   //if(!A.bounds)  <=>  if(A.bounds != NULL) 
        return ERROR;
    }//if

    //释放A.bounds指向的存储区域的内存空间  
    free(A.bounds);

    //A.bounds指针置空，释放掉指针变量本身的内存空间 
    A.bounds = NULL;

    //3.释放存储数组映像函数常量的A.constants指示的内存空间 

    //检查此段内存区域是否存在
    if(!A.constants) {  //if(!A.constants) <=> if(A.constants == NULL)
        return ERROR;
    }//if

    //释放A.constants指向的存储区域的内存空间
    free(A.constants);

    //A.constants指针置空，释放掉指针变量本身的内存空间
    A.constants = NULL;

    //操作成功
    return OK;
}//DestroyArray 

/*
    函数：Locate 
    参数：Array A 数组A
          va_list ap 指向保存待定位元素各个维下标的可变参数的指针
          int &off 带回待定位元素在A.base指示的一维存储空间的相对位置 
    返回值：状态码，操作成功返回OK，操作失败返回ERROR 
    作用：对ap指示的下标对应的元素进行定位，由off带回元素在A.base
          指示的一维存储空间的相对位置。 
          实际上就是使用映像函数配合求得的映像常量完成元素的相对定位，
          得到一个相对位置。 
*/
Status Locate(Array A, va_list ap, int &off){

    //ind临时保存从可变参数中取得的的待定位元素的每一维的下标 
    int ind;

    //off保存求得的待定位元素的相对位置 
    off = 0;

    //根据元素每一维的下标使用映像函数进行定位 
    for(int i = 0; i < A.dim; ++i){

        //从可变参数中获取待定位元素在某一维的下标 
        ind = va_arg(ap, int);
        
//        ap这是一个 va_list 类型的对象，存储了有关额外参数和检索状态的信息。该对象应在第一次调用 va_arg 之前通过调用 va_start 进行初始化。
//		type 这是一个类型名称。该类型名称是作为扩展自该宏的表达式的类型来使用的。
//		返回值
//		该宏返回下一个额外的参数，是一个类型为 type 的表达式。

        //检查下标ind是否越界 
        if(ind < 0 || ind >= A.bounds[i]) { //数组越界 
            return OVERFLOW;
        }//if

        //根据映像函数求出某一维的偏移量，并且累加到off上 
        off += A.constants[i] * ind;
    }//for

    //操作成功 
    return OK;
}//Locate

/*
    函数：Value
    参数：Array A 数组A
          ElemType &e 获取指定下标位置元素的值保存到e 
          ... 可变参数，传递的是待查找元素各维的下标 
    返回值：状态码，操作成功返回OK，操作失败返回ERROR 
    作用：（按下标从数组A中取值）A是n维数组，e为元素变量，
          随后的可变参数是n个下标值。若各下标不超界，
          则e赋值为所指定的数组A的元素值，并返回OK。
*/
Status Value(Array A, ElemType &e, ...){

    //声明指向可变参数的指针ap 
    va_list ap;

    //off保存了指定下标元素的定位结果，也就是这个元素
    //在A.base指示的一维数组中的位置 
    int off;

    //保存定位操作的结果，只要这个结果<=0就说明定位操作失败 
    Status result;

    //开始获取e后面的可变参数，并使ap指向可变参数，供定位函数使用 
    va_start(ap, e);

    //对指定下标的元素进行定位，获取这个元素在A.base指示的
    //一位数组中的相对位置，如果返回值result<=0，定位失败 
    if((result = Locate(A, ap, off)) <= 0) { //数组越界 
        return result;
    }//if

    //根据定位操作计算出的相对位置，直接将其作为一位数组的下标
    //从A.base中按照一维数组的取法取出对应位置的元素(注意下标从0开始) ，
    //也可以用指针的取法来取得对应位置的元素 
    //e = *(A.base + off);  <=>  e = A.base[off]; 
    e = *(A.base + off);

    //结束可变参数的获取。 
    va_end(ap); 

    //操作成功 
    return OK; 
}//Value

/*
    函数：Assign
    参数：Array &A 数组引用 
          ElemType e 修改指定下标位置元素的值为e 
          ... 可变参数，传递的是待修改元素各维的下标 
    返回值：状态码，操作成功返回OK，操作失败返回ERROR 
    作用：A是n维数组，e为元素变量，随后是n个下标值
          若各下标不超界，将e的值赋给所指定的A的元素，并返回OK。
*/
Status Assign(Array &A, ElemType e, ...){

    //ap指向存储下标的可变参数 
    va_list ap;

    //off存储了定位操作获得的元素在A.base一维数组中的相对位置 
    int off;

    //开始获取参数e后面的可变参数，并使ap指向可变参数 
    va_start(ap, e);

    //result存储了定位操作的结果，如果这个值<=0表示定位操作失败 
    Status result;

    //按可变参数指示的下标执行定位操作，获取元素在A.base指示的
    //一维数组中的相对位置off，操作结果作为返回值赋值给result 
    if((result = Locate(A, ap, off)) <= 0) {  //数组越界 
        return result;
    }//if

    //结束可变参数的获取。 
    va_end(ap);

    //根据定位操作获取的相对位置off，将A.base指示的内存空间中
    //对应位置的值修改为e，也可以使用一维数组的写法：
    //*(A.base + off) = e;   <=>   A.base[off] = e;
    *(A.base + off) = e;

    //操作成功 
    return OK; 
}//Assign


int main(int argc, char **argv){
    Array A;
    printf("\n--------------------------------数组顺序存储表示-------------------------------\n\n"); 
    //i,j,k是临时变量 
    int i, j, k;

    //p是工作指针 
    int *p; 

    //设置数组的维数为3 
    int dim = 3;

    //设置数组每一维的大小分别为3,4,2，也就是：A[3][4][2]
    int bound1 = 3, bound2 = 4, bound3 = 2;

    //e保存从键盘输入的元素值和带回的元素值 
    ElemType e, *p1;

    //构造一个3*4*2的三维数组
    InitArray(A, dim, bound1, bound2, bound3);

    //输出数组A的维界基址 
    p = A.bounds;
    printf("数组A的维界（每一维大小）基址：A.bounds=[");
    for(int i = 0; i < dim; i++){
        printf(" %d ", *(p + i));
    }//for
    printf("]\n");

    //输出数组A印象函数常量基址 
    p = A.constants;
    printf("数组印象函数常量基址：A.constants=[");  
    for(int i = 0; i < dim; i++){
        printf(" %d ", *(p + i));
    }//for
    printf("]\n");

    //数组元素赋初值 
    for(int i = 0; i < bound1; i++){
        for(int j = 0; j < bound2; j++){
            for(int k = 0; k < bound3; k++){

                //调用赋值函数Assign初始化数组A
                //第一个参数是数组A
                //第二个参数是初始化的元素值
                //从第三个参数开始到最后的是3个下标（可变参数） 
                Assign(A, i * 100 + j * 10 + k, i, j, k);
            }//for-k
        }//for-j
    }//for-i

    //输出矩阵的所有元素
    printf("A[%d][%d][%d]矩阵元素如下：\n", bound1, bound2, bound3);
    for(int i = 0; i < bound1; i++){
        for(int j = 0; j < bound2; j++){
            for(int k = 0; k < bound3; k++){

                //取出A[i][j][k]位置的元素 
                Value(A, e, i, j, k);

                //输出
                printf("A[%d][%d][%d]=%2d\t", i, j, k, e); 
            }//for-k 
            printf("\n"); 
        }//for-j
        printf("\n");
    }//for-i

    printf("A.dim=%d\n", A.dim);

    DestroyArray(A);
}//main

