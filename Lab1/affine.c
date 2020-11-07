#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_TEXT_LEN 512

int gcd(int a,int b)
{
    if(a % b ==0)
    {
        return b;
    }
    else
    {
        return gcd(b,a%b);
    }
}
int getInverse(int a)
{
    int i;
    for(i = 1;i < 26;i++)
    {
        if((i*a) % 26 == 1)
        {
            return i;
        }
    }
}
void genKey(int keys[])
{
    int pos;
    int a[12] = {1,3,5,7,9,11,15,17,19,21,23,25};
    srand((unsigned)time(NULL));
    pos = rand() % 12;
    keys[0] = a[pos];
    keys[1] = rand() % 26;
}
void encryption(char plaintext[],int keys[],char ciphertext[])
{
    int i,m,bias = 97;
    // printf("len:%d\n",strlen(plaintext));
    for(i=0;i<strlen(plaintext);i++)
    {
        if(isupper(plaintext[i]))
        {
            m = (int)tolower(plaintext[i]) - bias;
        }
        else if(islower(plaintext[i]))
        {
            m = (int)plaintext[i] - bias;
        }
        else
        {
            ciphertext[i] = plaintext[i];
            continue;
        }
        ciphertext[i] = (keys[0] * m + keys[1]) % 26 + bias;
    }
    printf("-------- ciphertext --------\n%s\n",ciphertext);
}
void decryption(char ciphertext[],int keys[],char plaintext[])
{
    int i,c,bias = 97;
    int inverse_a = getInverse(keys[0]);
    // int inverse_a;
    // ExtendedEuclid(keys[0],26,&inverse_a);
    // printf("The inverse_a is:%d\n",inverse_a);
    for(i=0;i<strlen(ciphertext);i++)
    {
        if(islower(ciphertext[i]))
        {
            c = (int)ciphertext[i] - bias;
            plaintext[i] = (inverse_a * (c - keys[1] + 26)) % 26 + bias;
        }
        else
        {
            plaintext[i] = ciphertext[i];
        }        
    }
    printf("-------- plaintext --------\n%s\n",plaintext);
}
int main()
{
    char c,text[MAX_TEXT_LEN],i;
    //int key_a,key_b;
    int keys[2];
    printf("What do you want to do?(e|E for encryption,d|D for decryption.)\n");
    c = getchar();getchar();
    if(c == 'e' || c == 'E')
    {
        genKey(keys);
        printf("key a:%d,key b:%d\n",keys[0],keys[1]);
        printf("Please input the plaintext:\n");
        gets(text);
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is too long!Please input the plaintext again:\n");
            gets(text);
        }
        char ciphertext[MAX_TEXT_LEN] = {0};
        encryption(text,keys,ciphertext);
    }
    else if(c == 'd' || c == 'D')
    {
        printf("Please input the keys.\nKey a:");
        scanf("%d",&keys[0]);
        printf("Key b:");
        scanf("%d",&keys[1]);
        printf("%d %d\n",keys[0],keys[1]);
        printf("Please input the ciphertext:\n");getchar();
        gets(text);
        //printf("%s %d\n",text,strlen(text));
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is too long!Please input the ciphertext again:\n");getchar();
            gets(text);
        }
        char plaintext[MAX_TEXT_LEN] = {0};
        decryption(text,keys,plaintext);
    }
    else
    {
        printf("Error!\n");
    }
}
