#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "demo.h"


#define BLOCK_SIZE 128

int main(int argc, char const *argv[])
{
    char plaintext[MAXLEN];
    int plen;
    readPlainText(plaintext,&plen);
    printf("%d",MAXLEN);
    /*aes(p,plen,k);
    printASCCI(p, plen);*/
}

