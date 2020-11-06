#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_TEXT_LEN 512

int main(int argc,char *argv[])
{
    char key[8] = "security";
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
        gets(text);
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is too long!Please input the plaintext again:\n");
            gets(text);
        }
        for(i=0;i<strlen(text);i++)
        {
            if(isupper(text[i]))
            {
                m = (int)tolower(text[i]) - bias;
            }
            else if(islower(text[i]))
            {
                m = (int)text[i] - bias;
            }
            else
            {
                ciphertext[i] = text[i];
                continue;
            }
            ciphertext[i] = ((m + key[i % key_len] - 'a')) % 26 + bias;
        }
        printf("-------- ciphertext --------\n%s\n",ciphertext);
        // puts(ciphertext);
    }
    else if(c == 'd' || c == 'D')
    {
        printf("Please input the ciphertext:\n");
        gets(text);
        while(strlen(text) >= MAX_TEXT_LEN)
        {
            printf("The size of text is too long!Please input the plaintext again:\n");getchar();
            gets(text);
        }
        for(i=0;i<strlen(text);i++)
        {
            if(islower(text[i]))
            {
                m = (int)text[i] - bias;
                plaintext[i] = (m - (key[i % key_len] - 'a') + 26) % 26 + bias;
            }
            else
            {
                plaintext[i] = text[i];
            }
        }
        printf("-------- plaintext --------\n%s\n",plaintext);
    }
    else
    {
        printf("Error!\n");
    }
}
