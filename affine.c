#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_TEXT_LEN 100

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
    for(i=0;i<strlen(plaintext);i++)
    {
        m = (int)plaintext[i] - bias;
        ciphertext[i] = (keys[0] * m + keys[1]) % 26 + bias;
    }
    printf("The ciphertext is:%s\n",ciphertext);
}
void decryption(char ciphertext[],int keys[],char plaintext[])
{
    int i,c,bias = 97;
    int inverse_a = getInverse(keys[0]);
    //int inverse_a;
    //ExtendedEuclid(keys[0],26,&inverse_a);
    printf("The inverse_a is:%d\n",inverse_a);
    for(i=0;i<strlen(ciphertext);i++)
    {

        c = (int)ciphertext[i] - bias;
        plaintext[i] = (inverse_a * (c - keys[1] + 26)) % 26 + bias;
    }
    printf("The plaintext is:%s\n",plaintext);
}
int main(int argc,char *argv[])
{
    char c,text[MAX_TEXT_LEN],i;
    //int key_a,key_b;
    int keys[2];
START:
    printf("What do you want to do?(e|E for encryption,d|D for decryption.)\n");
    c = getchar();getchar();
    if(c == 'e' || c == 'E')
    {
        genKey(keys);
        printf("key a:%d,key b:%d\n",keys[0],keys[1]);
        printf("Please input the plaintext:\n");
        scanf("%s",text);
        //printf("%s %d",text,strlen(text));
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is larger than 100!Please input the plaintext again:\n");
            scanf("%s",text);
        }
        //for(i=0;i<strlen(text);i++)
        //{
            //if((!isupper(text[i])) && (!islower(text[i])))
        //}
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
        printf("Please input the ciphertext:\n");
        scanf("%s",text);
        //printf("%s %d\n",text,strlen(text));
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is larger than 100!Please input the ciphertext again:\n");
            scanf("%s",text);
        }
        char plaintext[MAX_TEXT_LEN] = {0};
        decryption(text,keys,plaintext);
    }
    else
    {
        printf("Error!\n");
    }
}
