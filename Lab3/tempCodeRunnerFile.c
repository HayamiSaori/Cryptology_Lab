#include "aes-demo.c"
int main(){
    int i,a[4]={1,2,3,4};
    leftLoop4int(a,3);
    for(i=0;i<4;i++)
    {
        printf("%d ",a[i]);
    }
}