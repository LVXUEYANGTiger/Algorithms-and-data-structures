#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#define MAXSIZE 12500   /// �������Ԫ�������ֵΪ12500
#define MAXRC 125      ///�����ÿ�еĸ��������ֵ125
#define ERROR -1
typedef struct {
    int     i,j;        ///  �÷���Ԫ�����±�����±�
    int    	e;
}Triple;
typedef struct {
    Triple data[MAXSIZE + 1];///����Ԫ��Ԫ���
    int rpos[MAXRC + 1]; ///���е�һ������Ԫ��λ�ñ�
    /*
    �Ծ���NΪ��
    rpos[row]ָʾ����N�ĵ�row���е�һ������Ԫ��N.data�е���ţ���rpos[row+1]-1ָʾ����N��
    ��row�������һ������Ԫ��N.data�е���ţ����һ������Ԫ��N.data�е�λ����Ȼ����N.tu�ˡ�
    Ҳ����˵rpos���ľ��Ǹ��е�һ������Ԫ��š�
    */
    int mu,nu,tu;   ///����������������ͷ���Ԫ����
}RLSMatrix;
void ScanfRLSMatrix(RLSMatrix &M)
{
    int x=0,k=1;
    M.tu = 0;//��ʼ��M�ķ���Ԫ���� 
    for(int i=1;i<=M.mu;i++)
	{
        for(int j=1;j<=M.nu;j++)
		{
            scanf("%d",&x);
            if(x!=0)//����Ƿ���ԪԪ�أ��������Ԫ��ֵ,��������������M.data[k] 
			{
                M.data[k].e = x;
                M.data[k].i=i;
                M.data[k].j=j;
                k++;
                M.tu++;
            }
        }
    }
    ///���rpos��ֵ
    int num[MAXSIZE + 1];
    if(M.tu)
	{
        for(int row=1; row<=M.mu; ++row)  
		{
			num[row]=0; //����
		}
        for(int t=1; t<=M.tu; ++t)
		{
			++num[M.data[t].i];  //��M��ÿһ�к��������
		} 
        M.rpos[1]=1;
        /// ���col���е�һ������Ԫ��b.data�е����
        for(int row =2; row <= M.mu; ++row)
		{
        	M.rpos[row] = M.rpos[row - 1] + num[row - 1];
		} 
    }
}
void PrintfRLSMatrix(RLSMatrix M)
{
    printf("��ǰ����Ϊ��\n");
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
    ///�����˻�Q=M*N,�������߼����Ӵ洢��ʾ
    if(M.nu != N.mu)
	{
		return ERROR;
	} 
    Q.mu = M.mu; Q.nu = N.nu; Q.tu=0;           ///Q��ʼ��
    int ctemp = 0;  ///�����ۼ���
    if(M.tu * N.tu != 0)
	{   //Q�Ƿ������
        for(int arow = 1; arow <= M.mu; ++arow)
		{    
			///����M��ÿһ��
            int ctemp[500];
            memset(ctemp,0,sizeof(ctemp));      //c++��ʼ����䵱ǰ�и�Ԫ���ۼ�������
            //memset() ����������һ���ڴ�������ĳ��������ֵ����Ϊ��ֻ�����һ��ֵ�����Ըú����ĳ�ʼ��Ϊԭʼ��ʼ����
			//�޷���������ʼ��Ϊ��������Ҫ�����ݡ���memset��ʼ����󣬺��������������ڴ�ռ��д����Ҫ�����ݡ�
            Q.rpos[arow]=Q.tu+1;
            int tp=0;       ///����ľ���Mÿһ�����һ������Ԫ����һ�����
            if(arow < M.mu)
			{
				tp = M.rpos[arow + 1];
			}  
            else 
			{ 
				tp = M.tu + 1; 
			}
            /*
            ǰmu�У�����Mÿ�����һ������Ԫ����M.rpos[arow + 1]-1;
            ��mu�У�����Mÿ�����һ������Ԫ����M.tu;
            */
            for(int p=M.rpos[arow];p<tp;++p)
			{    
				//������ǰ�е�ÿһ������Ԫ��
                int brow = M.data[p].j; ///�ҵ���ӦԪ��N�е��к�
                int t = 0;
                //�������tpͬ���������Nÿһ�����һ������Ԫ����һ�����

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
                    int ccol = N.data[q].j;     ///�˻�Ԫ����Q�е��к�
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                }//for q
            }//���Q�еĵ�crow( = arow)�еķ���Ԫ
            /**
            ����M�еĵ�һ������Ԫ��ȥ�˾���N�����Ӧ����q��ÿһ������Ԫ
            ����洢��ctemp�����С�
            ������M���е�ÿһ������Ԫp�����꣬
            ��ʱctemp������洢�ľ���Q�е�һ�����з���Ԫ(����)�Ľ��
            */

            for(int ccol = 1; ccol <= Q.nu; ++ccol)
            {
            	// ѹ���洢�÷���Ԫ������������ý��Ϊ0��Ԫ��ȥ��
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

    printf("������ϡ��M�ľ�����mu����nu:\n");
    scanf("%d%d",&M.mu,&M.nu);
    ScanfRLSMatrix(M);
    PrintfRLSMatrix(M);
    RLSMatrix N;

    printf("������ϡ��N�ľ�����mu����nu:\n");
    scanf("%d%d",&N.mu,&N.nu);
    ScanfRLSMatrix(N);
    PrintfRLSMatrix(N);
	RLSMatrix Q;

    MultSMareix(M,N,Q);
    printf("�����:\n");
    PrintfRLSMatrix(Q);

    return 0;

}

