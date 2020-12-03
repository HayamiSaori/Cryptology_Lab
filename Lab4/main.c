#include <stdio.h>
#include <stdlib.h>
#include "demo.h"
#define PLAINTEXT_MAX_LEN 1024
#define BLOCK_SIZE 16
void PadPlainText(char *p,int *plen)
{
    int i,j,pad;
    //printf("len:%d\n",*plen);
    if(*plen == BLOCK_SIZE)
    {
        for(i=0;i<16;i++)
        {
            p[i+(*plen)] = 16;
        }
        *plen += 16;
        p[*plen] = 0;
    }
    else
    {
        pad = BLOCK_SIZE - (*plen) % BLOCK_SIZE;
        for(i=0;i<pad;i++)
        {
            p[i+(*plen)] = pad;
        }
        *plen += pad;
        p[*plen] = 0;
    }
    return;
}
void getKey(char k[17])
{
    int klen;
    while(1)
    {
        printf("请输入16个字符的密钥或初始化向量：\n");
        getString(k,17);
        klen = strlen(k);
        if(klen != 16)
        {
            printf("请输入16个字符的密钥或初始化向量,当前密钥的长度为%d\n",klen);
        }
        else
        {
            printf("你输入的密钥或初始化向量：%s\n",k);
            break;
        }
    }
    return;
}
int main()
{
    char p[PLAINTEXT_MAX_LEN] = {0},key[17] = {0},IV[17] = {0},temp_plaintext[17] = {0};
    int plen,block_num,i,j,bias;
    readPlainText(p,&plen);
    PadPlainText(p,&plen);
    //for(i=0;i<plen;i++)printf("%x,",p[i]);
    getKey(key);getKey(IV);
    block_num = plen / BLOCK_SIZE;
    printf("\ngroup num:%d\n",block_num);
    for(i=0;i<block_num;i++)
    {
        bias = i * BLOCK_SIZE;
        for(j=0;j<16;j++)
        {
            temp_plaintext[j] = p[bias+j];
        }
        temp_plaintext[16] = 0;
        aes(temp_plaintext,16,key);
    }

}
