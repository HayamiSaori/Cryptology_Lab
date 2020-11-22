#include <stdio.h>
// #include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
int S_INIT[16][16];
int S_INVERSE[16][16];
void PrintS(int mode)
{
    int i,j;
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            switch (mode)
            {
            case 1:
                printf("0x%x ",S_INIT[i][j]);
                break;
            case 2:
                printf("0x%x ",S_INVERSE[i][j]);
                break;                
            default:
                break;
            }
            
        }
        printf("\n");
    }
}
// GF(256)下的多项式乘法
int MUL(int a, int b)
{
    int temp[8];
    int i,temp_a,temp_b,result;
    for(i=0;i<8;i++)
    {
        temp_a = a << i;    // 被乘数
        temp_b = (b>>i) & 1;// 乘数
        temp[i] = temp_a * temp_b;  // 部分积
    }
    result = temp[0];
    for(i=1;i<8;i++)
    {
        result = result ^ temp[i];// 将部分积相加，注意到多项式加法以异或处理
    }
    return result;
}
// 寻找一个数的二进制最高位索引
int HighestBit(int x)
{
    int result = 0;
    while(x>0)
    {
        result++;
        x = x >> 1;
    }
}
// GF(256)下的多项式除法，计算 a/b 的商和余数（余数以指针的方式传入）
int DIV(int a,int b,int *mod)
{
    int r,q,count;
    r = b;
    q = 0;
    count = HighestBit(a) - HighestBit(b);
    while (count >= 0)
    {
        q = q | (1<<count);
        r = r ^ (b<<count);
        count = HighestBit(r) - HighestBit(b);
    }
    *mod = r;
    return q;
}
// 求a和b的最大公因数，欧几里得算法
int Euclidean(int a,int b)
{
    int r,r1,r2,q;
    r1 = a;
    r2 = b;
    while(r2>0)
    {
        q = r1 / r2;
        r = r1 - q*r2;
        r1 = r2;
        r2 = r;
    }
    return r1;
}
// 求b在模n下的乘法逆元，拓展欧几里得，注意到在GF(256)下乘除法不同
int ExtendedEuclidean(int n,int b)
{
    int r,r1,r2,t1,t2,q,t;
    r1 = n;
    r2 = b;
    t1 = 0;
    t2 = 1;
    while (r2>0)
    {
        // q = r1 / r2;
        q = DIV(r1,r2,&r);

        // r = r1 - q*r2;
        r1 = r2;
        r2 = r;

        // t = t1 - q*t2;
        t = DIV(t1,t2,&t);
        t1 = t2;
        t2 = t;
    }
    if(r1 == 1)
    {
        return t1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    int i,j,k;
    
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            S_INIT[i][j] = i*16 + j;
        }
    }
    printf("-------- initial matrix --------\n");
    PrintS(1);
    printf("-------- get inverse --------\n");
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if(i==0 && j==0)
            {
                S_INVERSE[i][j] = 0;
            }
            else
            {
                S_INVERSE[i][j] = ExtendedEuclidean(S_INIT[i][j],0x11B);
            }
        }
    }
    PrintS(2);
}