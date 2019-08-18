#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#define MAXSIZE 12500   /// 假设非零元个数最大值为12500
#define MAXRC 125      ///假设的每行的个数的最大值125
#define ERROR -1
typedef struct {
    int     i,j;        ///  该非零元的行下标和列下标
    int    	e;
}Triple;
typedef struct {
    Triple data[MAXSIZE + 1];///非零元三元组表
    int rpos[MAXRC + 1]; ///各行第一个非零元的位置表
    /*
    以矩阵N为例
    rpos[row]指示矩阵N的第row行中第一个非零元在N.data中的序号，则rpos[row+1]-1指示矩阵N的
    第row行中最后一个非零元在N.data中的序号，最后一个非零元在N.data中的位置显然就是N.tu了。
    也就是说rpos里存的就是各行第一个非零元序号。
    */
    int mu,nu,tu;   ///矩阵的行数、列数和非零元个数
}RLSMatrix;
void ScanfRLSMatrix(RLSMatrix &M)
{
    int x=0,k=1;
    M.tu = 0;//初始化M的非零元个数 
    for(int i=1;i<=M.mu;i++)
	{
        for(int j=1;j<=M.nu;j++)
		{
            scanf("%d",&x);
            if(x!=0)//如果是非零元元素，则把它的元素值,行数和列数存入M.data[k] 
			{
                M.data[k].e = x;
                M.data[k].i=i;
                M.data[k].j=j;
                k++;
                M.tu++;
            }
        }
    }
    ///求出rpos的值
    int num[MAXSIZE + 1];
    if(M.tu)
	{
        for(int row=1; row<=M.mu; ++row)  
		{
			num[row]=0; //清零
		}
        for(int t=1; t<=M.tu; ++t)
		{
			++num[M.data[t].i];  //求M中每一列含非零个数
		} 
        M.rpos[1]=1;
        /// 求第col列中第一个非零元在b.data中的序号
        for(int row =2; row <= M.mu; ++row)
		{
        	M.rpos[row] = M.rpos[row - 1] + num[row - 1];
		} 
    }
}
void PrintfRLSMatrix(RLSMatrix M)
{
    printf("当前矩阵为：\n");
    int k=1;
    for(int i=1;i<=M.mu;i++)
	{
        for(int j=1;j<=M.nu;j++)
		{
            if(M.data[k].i==i&&M.data[k].j==j)
			{
                printf("%3d",M.data[k].e);
                k++;
            }
            else
			{
				printf("%3d",0);
			} 
        }
        puts("");
    }
    return ;
}
int MultSMareix(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
{
    ///求矩阵乘积Q=M*N,采用行逻辑链接存储表示
    if(M.nu != N.mu)
	{
		return ERROR;
	} 
    Q.mu = M.mu; Q.nu = N.nu; Q.tu=0;           ///Q初始化
    int ctemp = 0;  ///定义累加器
    if(M.tu * N.tu != 0)
	{   //Q是非零矩阵
        for(int arow = 1; arow <= M.mu; ++arow)
		{    
			///处理M的每一行
            int ctemp[500];
            memset(ctemp,0,sizeof(ctemp));      //c++初始化语句当前行个元素累加器清零
            //memset() 的作用是在一段内存块中填充某个给定的值。因为它只能填充一个值，所以该函数的初始化为原始初始化，
			//无法将变量初始化为程序中需要的数据。用memset初始化完后，后面程序中再向该内存空间中存放需要的数据。
            Q.rpos[arow]=Q.tu+1;
            int tp=0;       ///定义的矩阵M每一行最后一个非零元的下一个序号
            if(arow < M.mu)
			{
				tp = M.rpos[arow + 1];
			}  
            else 
			{ 
				tp = M.tu + 1; 
			}
            /*
            前mu行，矩阵M每行最后一个非零元素是M.rpos[arow + 1]-1;
            第mu行，矩阵M每行最后一个非零元素是M.tu;
            */
            for(int p=M.rpos[arow];p<tp;++p)
			{    
				//便利当前行的每一个非零元素
                int brow = M.data[p].j; ///找到对应元在N中的行号
                int t = 0;
                //和上面的tp同理，定义矩阵N每一行最后一个非零元的下一个序号

                if(brow < N.mu)
				{
					t = N.rpos[brow + 1];
				} 
                else 
				{
					t = N.tu + 1; 
				}
                for(int q = N.rpos[brow]; q < t; ++q)
				{
                    int ccol = N.data[q].j;     ///乘积元素在Q中的列号
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                }//for q
            }//求得Q中的第crow( = arow)行的非零元
            /**
            就是M行的第一个非零元，去乘矩阵N的相对应的列q的每一个非零元
            结果存储在ctemp数组中。
            当矩阵M该行的每一个非零元p都乘完，
            此时ctemp数组里存储的就是Q中第一行所有非零元(含零)的结果
            */

            for(int ccol = 1; ccol <= Q.nu; ++ccol)
            {
            	// 压缩存储该非零元，即把上面求得结果为0的元素去掉
                if(ctemp[ccol])
				{
                    if(++Q.tu>MAXSIZE)
					{
					 	return ERROR; 
					}
                    Q.data[Q.tu].i = arow;
                    Q.data[Q.tu].j = ccol;
                    Q.data[Q.tu].e = ctemp[ccol];
                }// if  	
			}

        }// for arow

    }// if

}
int main()
{
    RLSMatrix M;

    printf("请输入稀疏M的矩阵行mu和列nu:\n");
    scanf("%d%d",&M.mu,&M.nu);
    ScanfRLSMatrix(M);
    PrintfRLSMatrix(M);
    RLSMatrix N;

    printf("请输入稀疏N的矩阵行mu和列nu:\n");
    scanf("%d%d",&N.mu,&N.nu);
    ScanfRLSMatrix(N);
    PrintfRLSMatrix(N);
	RLSMatrix Q;

    MultSMareix(M,N,Q);
    printf("结果是:\n");
    PrintfRLSMatrix(Q);

    return 0;

}

