#include <stdio.h>
#include <string.h>
#include "DES-demo.c"
#define MAX_CHAR_NUM 8
void DIVT(int L[],int R[],int X[])
{
    int i;
    for(i=0;i<32;i++)
    {
        L[i] = X[i + 32];
        R[i] = X[i];
    }
}
void DIVK(int C[],int D[],int K[])
{
    int i;
    for(i=0;i<28;i++)
    {
        C[i] = K[i + 28];
        D[i] = K[i];
    }
}
void LINK(int C[],int D[],int K[])
{
    int i;
    for(i=0;i<28;i++)
    {
        K[i] = D[i];
        K[i + 28] = C[i];
    }

}
void IP(int X[])
{
    int Y[64] = {0};
    int i = 0;
    for(i=0;i<64;i++)
    {
        Y[i] = X[IP_Table[i] - 1];
    }
    // X = Y;
    // memcpy(X,Y,sizeof(int)*64);
    for(i=0;i<64;i++)
    {
        X[i] = Y[i];
    }
}
void EXT(int E[],int X[])
{
    int i;
    for(i=0;i<48;i++)
    {
        E[i] = X[E_Table[i] - 1];
    }
}
void IP_R(int X[])
{
    int Y[64] = {0};
    int i = 0;
    for(i=0;i<64;i++)
    {
        Y[i] = X[IPR_Table[i] - 1];
    }
    // X = Y;
    // memcpy(X,Y,sizeof(int)*64);
    for(i=0;i<64;i++)
    {
        X[i] = Y[i];
    }
}
void PC_1(int K[],int P[])
{
    int i;
    for(i=0;i<56;i++)
    {
        K[i] = P[PC1_Table[i] - 1];
    }
}
void PC_2(int C[],int D[],int K[])
{
    int i;
    int X[56] = {0};
    // int K[48] = {0};
    for(i=0;i<28;i++)
    {
        X[i + 28] = C[i];
        X[i] = D[i];
    }
    for(i=0;i<48;i++)
    {
        K[i] = X[PC2_Table[i] - 1];
    }
    // printf("now print the key_48\n");
    // for(i=0;i<48;i++)
    // {
    //     printf("%d ",K[47-i]);
    // }
    // printf("\n");
}
void RL(int C[],int D[])
{
    int i;
    int C_new[28] = {0};
    int D_new[28] = {0};
    for(i=0;i<28;i++)
    {
        C_new[i] = C[RL_Table[i]];
        D_new[i] = D[RL_Table[i]];
    }
    // memcpy(C,C_new,sizeof(int)*28);
    // memcpy(D,D_new,sizeof(int)*28);
    for(i=0;i<28;i++)
    {
        C[i] = C_new[i];
        D[i] = D_new[i];
    }
}
void XOR_48(int A[],int B[],int C[])
{
    int i;
    for(i=0;i<48;i++)
    {
        C[i] = A[i] ^ B[i];
    }
    // printf("now print the xor_48\n");
    // for(i=0;i<48;i++)
    // {
    //     printf("%d ",C[47-i]);
    // }
    // printf("\n");
}
void XOR_32(int A[],int B[],int C[])
{
    int i;
    for(i=0;i<32;i++)
    {
        C[i] = A[i] ^ B[i];
    }
    // printf("now print the xor_32\n");
    // for(i=0;i<32;i++)
    // {
    //     printf("%d",C[31-i]);
    // }
    // printf("\n");
}
void SFUNC(int IN[],int OUT[])
{
    int i,j,k,bias,col,row,s_value;
    for(i=0;i<8;i++)
    {
        bias = i*6;
        col = IN[bias+1]*8 + IN[bias+2]*4 + IN[bias+3]*2 + IN[bias+4];
        row = IN[bias]*2 + IN[bias+5];
        s_value = S_Box[i][row][col];
        // printf("the s_value of round %d is %d\n",i,s_value);
        for(j=0;j<4;j++)
        {
            OUT[bias+j] = s_value % 2;
            s_value = s_value / 2;
        }
    }
}
void ROUND(int L[],int R[],int K[],int i)
{
    // int i;
    int j,k;
    int C[28] = {0},D[28] = {0};
    printf("now divide the key\n");
    DIVK(C,D,K);        //将密钥分为2部分
    printf("now rotate the C and D\n");
    RL(C,D);            //C，D各自循环左移
    if(i!=1 && i!=2 && i!=9 && i!=16)
    {
        RL(C,D);
    }
    // printf("now re-link the key\n");
    LINK(C,D,K);        //生成下一轮的56位key
    int R_E[48] = {0};
    // printf("now extend the R\n");
    EXT(R_E,R);         //拓展右32位
    int R_XOR_48[48] = {0};
    int K_XOR[48] = {0};
    // printf("now generate the 48-bit key\n");
    PC_2(C,D,K_XOR);    //获取48位密钥
    // printf("now do the 48-bit xor\n");
    XOR_48(R_E,K_XOR,R_XOR_48);   //48位异或运算
    int R_S_32[32] = {0};
    // printf("now do the S-Box\n");
    SFUNC(R_XOR_48,R_S_32); //S盒函数
    int R_XOR_32[32] = {0};
    // printf("now do the 32-bit xor\n");
    XOR_32(L,R_S_32,R_XOR_32);//32位异或
    // printf("now copy the result to R\n");
    // memcpy(R,R_XOR_32,sizeof(int)*32);  //仅右边32位发生了变化
    for(j=0;j<32;j++)
    {
        R[j] = R_XOR_32[j];
    }
}
void GetInput(int plaintext[])
{
    int num,i,j,b;
    char c,temp;
    char text[MAX_CHAR_NUM] = {0};
    printf("Please input here:");
    gets(text);
    while (strlen(text) > MAX_CHAR_NUM)
    {
        printf("Text too long!Please input again.\n");
        gets(text);
    }
    for(i=0;i<8;i++)
    {
        c = text[i];
        num = (int)c;
        for(j=0;j<8;j++)
        {
            plaintext[j+(7-i)*8] = num % 2;
            num = num / 2;
        }
        // n = n | ((int)c << ((7-i) * 8));
    }
    // return plaintext;
    // for(i=0;i<64;i++)
    // {
    //     printf("%d",plaintext[63-i]);
    // }
}
int main(int argc,char *argv[])
{
    int L[32] = {0};
    int R[32] = {0};
    int plaintext[64] = {0};
    printf("-------- now input the plaintext --------\n");
    GetInput(plaintext);
    printf("-------- now input the password --------\n");
    int password[64] = {0};
    GetInput(password);
    printf("-------- generate the key --------\n");
    int key[56] = {0};
    PC_1(key,password);
    printf("-------- initial steps --------\n");
    IP(plaintext);
    DIVT(L,R,plaintext);
    int temp[32] = {0};
    // printf("-------- round 1 --------\n");
    // ROUND(L,R,key,1);
    int i,j,k,bias,left,right;
    for(i=1;i<15;i++)
    {
        printf("-------- round %d --------\n",i);
        ROUND(L,R,key,i);
        memcpy(temp,L,sizeof(int)*32);
        memcpy(L,R,sizeof(int)*32);
        memcpy(R,temp,sizeof(int)*32);
        printf("now print the left 32 bits\n");
        for(j=0;j<8;j++)
        {
            bias = (7-j)*4;
            left = R[bias] + R[bias+1]*2 + R[bias+2]*4 + R[bias+3]*8;
            printf("%x",left);
        }
        printf("\n");
    }


    // int i;
    // for(i=0;i<56;i++)
    // {
    //     printf("%d",key[63-i]);
    // }
}