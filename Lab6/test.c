#include <stdio.h>
#define CLS(x, n) ((x) << (n)) | ((x) >> ((32) - (n)))
int main(void){
    unsigned int a=0xffffffff;
    a += 0xffffffff;
    // long b;printf("%d\n",sizeof(b));
    printf("%x\n",sizeof(a));
    printf("%x\n",a);printf("%x\n",CLS(a,30));
}