#include <stdio.h>
int main(void)
{
    unsigned int after[5] = {0x4cb1c576,0xbb32db00,0x0ac73786,0xd0ee8fee ,0x0afd6e37};
    unsigned int before[5] = {0x6fefa324 ,0xee16c477 ,0x9cb2aeb2 ,0x5c1afdcd ,0x2e9cd559};
    unsigned int temp = 0;
    int count = 0;
    int i,j,k;
    for(i=0;i<5;i++)
    {
        temp = before[i] ^ after[i];
        for(j=0;j<32;j++)
        {
            k = temp % 2;
            if(k == 1)
            {
                count++;
            }
            temp = temp / 2;
        }
    }
    printf("%d\n",count);
}