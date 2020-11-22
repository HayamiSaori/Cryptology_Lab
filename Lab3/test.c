// #include "aes-demo.c"
#include <stdio.h>
// #include "unistd.h"
#include <string.h>
#include <stdlib.h>
#include <windows.h>
void rightLoop4int(int array[4], int step)
{
//请补充代码
    int i,j,temp;
    for(i=0;i<step%4;i++)
    {
        temp = array[3];
        for(j=3;j>0;j--)
        {
            array[j] = array[j-1];
        }
        array[0] = temp;
    }
}
int main(){
    int i,a[4]={1,2,3,4};
    rightLoop4int(a,3);
    for(i=0;i<4;i++)
    {
        printf("%d ",a[i]);
    }
}