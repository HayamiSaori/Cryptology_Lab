#include <stdio.h>
#include <string.h>
#include "DES-demo.c"
#define MAX_CHAR_NUM 8
void IP(int X[])    //IP初始置换，输入X为64位
{
    int Y[64] = {0};
    int i = 0;
    for(i=0;i<64;i++)
    {
        Y[i] = X[IP_Table[i] - 1];
    }
    for(i=0;i<64;i++)
    {
        X[i] = Y[i];
    }
}
void DIVT(int L[],int R[],int X[])
{
    int i;
    for(i=0;i<32;i++)
    {
        R[i] = X[i + 32];
        L[i] = X[i];
    }
    printf("now print the L and R after DIVT\nL:");
    for(i=0;i<32;i++)
    {
        printf("%d",L[i]);
    }
    printf("\tR:");
    for(i=0;i<32;i++)
    {
        printf("%d",R[i]);
    }
    printf("\n");
}
void DIVK(int C[],int D[],int K[])
{
    int i;
    for(i=0;i<28;i++)
    {
        D[i] = K[i + 28];
        C[i] = K[i];
    }
    printf("now print the C and D after DIVK\nC:");
    for(i=0;i<28;i++)
    {
        printf("%d",C[i]);
    }
    printf("\tD:");
    for(i=0;i<28;i++)
    {
        printf("%d",D[i]);
    }
    printf("\n");
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
    for(i=0;i<28;i++)
    {
        C[i] = C_new[i];
        D[i] = D_new[i];
    }
    printf("now print the C and D after RL\nC:");
    for(i=0;i<28;i++)
    {
        printf("%d",C[i]);
    }
    printf("\tD:");
    for(i=0;i<28;i++)
    {
        printf("%d",D[i]);
    }
    printf("\n");
}
void EXT(int E[],int X[])
{
    int i;
    for(i=0;i<48;i++)
    {
        E[i] = X[E_Table[i] - 1];
    }
    // printf("now print the result after EXT\n");
    // for(i=0;i<48;i++)
    // {
    //     printf("%d",E[i]);
    //     if((i+1)%6==0)printf(" ");
    // }
}
void PC_1(int K[],int P[])
{
    int i;
    for(i=0;i<56;i++)
    {
        K[i] = P[PC1_Table[i] - 1];
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
            plaintext[(7-j)+i*8] = num % 2;
            num = num / 2;
        }
        // n = n | ((int)c << ((7-i) * 8));
    }
}
int main(int argc,char *argv[])
{
    int i,j,TEXT[64] = {0},L[32] = {0},R[32] = {0};
    memcpy(TEXT,TEST_TEXT,sizeof(int)*64);
    IP(TEXT);
    DIVT(L,R,TEXT);
    int R_E[48]={0};
    EXT(R_E,R);
    int PW[64] = {0},KEY[56] = {0},C[28]={0},D[28] = {0};
    memcpy(PW,TEST_KEY,sizeof(int)*64);
    PC_1(KEY,PW);
    DIVK(C,D,KEY);
    RL(C,D);
    // for(i=0;i<64;i++)
    // {
    //     printf("%d",TEXT[i]);
    //     if((i+1)%4==0)printf(" ");
    // }
}