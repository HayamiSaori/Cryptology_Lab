#include <stdio.h>
#include <string.h>
// #include "DES-demo.c"
int main()
{
  int a[5] = {1,2,3,4,5};
  int b[5] = {0};
  memcpy(b,a,sizeof(int)*5);
  int i;
  for(i=0;i<5;i++)
  {
    printf("%d ",b[i]);
  }
}