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
        //printf("请输入16个字符：\n");
        getString(k,17);
        klen = strlen(k);
        if(klen != 16)
        {
            printf("请输入16个字符，当前长度为%d\n",klen);
        }
        else
        {
            //printf("你的输入：%s\n",k);
            break;
        }
    }
    return;
}
int main()
{
    char p[PLAINTEXT_MAX_LEN] = {0},key[17] = {0},IV[17] = {0},temp_text[17] = {0},ciphertext[PLAINTEXT_MAX_LEN] = {0};
    int plen,clen,block_num,pad_num,i,j,bias=0;
    printf("请输入明文:\n");
    readPlainText(p,&plen);
    clen = plen;
    PadPlainText(p,&clen);
    printf("填充后的明文:\n");
    printASCCI(p,clen);
    //for(i=0;i<plen;i++)printf("%x,",p[i]);
    printf("请输入密钥:\n");
    getKey(key);
    printf("请输入初始化向量:\n");
    getKey(IV);
    block_num = clen / BLOCK_SIZE;
    printf("\ngroup num:%d\n",block_num);
    for(j=0;j<16;j++)
    {
        temp_text[j] = p[j] ^ IV[j];
    }
    temp_text[16] = 0;
    for(i=1;i<=block_num;i++)
    {
        //printASCCI(temp_text,16);
        printf("group %d:\n",i);
        printASCCI(temp_text,16);printf("\n");
        aes(temp_text,16,key);
        bias = i * BLOCK_SIZE;
        printASCCI(temp_text,16);printf("\n");
        for(j=0;j<16;j++)
        {
            ciphertext[j + bias - 16] = temp_text[j];
        }
        for(j=0;j<16;j++)
        {
            temp_text[j] = p[j + bias] ^ temp_text[j];
        }
        temp_text[16] = 0;
    }
    printf("\n--------------------------------\n");
    printASCCI(ciphertext,clen);
    printf("\n--------------------------------\n");
    printf("现在开始解密过程\n");
    for(i=0;i<clen;i++)
    {
        p[i] = 0;
    }
    for(i=1;i<block_num;i++)
    {
        bias = clen - i * 16;
        for(j=0;j<16;j++)
        {
            temp_text[j] = ciphertext[j + bias];
        }
        deAes(temp_text,16,key);
        for(j=0;j<16;j++)
        {
            p[j + bias] = temp_text[j] ^ ciphertext[j + bias - 16];
        }
    }
    pad_num = p[clen - 1];//获取填充数字
    plen = clen - pad_num;
    for(i=0;i<16;i++)
    {
        temp_text[i] = ciphertext[i];
    }
    deAes(temp_text,16,key);
    for(j=0;j<16;j++)
    {
        p[j] = temp_text[j] ^ IV[j];
    }
    printASCCI(p,plen);
    p[plen] = '\0';
    printf("还原回字符串为：\n%s\n",p);
}
