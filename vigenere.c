#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_TEXT_LEN 100

int main(int argc,char *argv[])
{
    //char key[8] = "security";
    int key[8] = {19,5,3,21,18,9,20,25};//security
    int key_len = 8;
    char plaintext[MAX_TEXT_LEN] = {0};
    char ciphertext[MAX_TEXT_LEN] = {0};
    char text[MAX_TEXT_LEN];
    char c,m,k;
    int i,j = 0,bias = 97;
    printf("The default key:security\n");
    printf("What do you want to do?(e|E for encryption,d|D for decryption.)\n");
    c = getchar();getchar();
    if(c == 'e' || c == 'E')
    {
        printf("Please input the plaintext:\n");
        scanf("%s",text);
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is larger than 100!Please input the plaintext again:\n");
            scanf("%s",text);
        }
        for(i=0;i<strlen(text);i++)
        {
            if(j == key_len)
            {
                j = 0;
            }
            else
            {
                j += 1;
            }
            m = (int)text[i] - bias;

            ciphertext[i] = (m + key[i]) % 26 + bias;
        }
        printf("ciphertext is:%s\n",ciphertext);
    }
    else if(c == 'd' || c == 'D')
    {
        printf("Please input the plaintext:\n");
        scanf("%s",text);
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is larger than 100!Please input the plaintext again:\n");
            scanf("%s",text);
        }
        for(i=0;i<strlen(text);i++)
        {
            if(j == key_len)
            {
                j = 0;
            }
            else
            {
                j += 1;
            }
            m = (int)text[i] - bias;

            plaintext[i] = (m - key[i] + 26) % 26 + bias;
        }
        printf("plaintext is:%s\n",plaintext);
    }
    else
    {
        printf("Error!\n");
    }
}
