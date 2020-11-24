#include <stdio.h>
// #include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


#define MAXLEN 8192

//��Կ��Ӧ����չ����
int w[44];
/**
 * S��
 */
int S[16][16] = { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
                };

/**
 * ��S��
 */
int S2[16][16] = { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
                   0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
                   0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
                   0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
                   0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
                   0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
                   0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
                   0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
                   0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
                   0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
                   0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
                   0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
                   0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
                   0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
                   0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
                   0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
                 };

/**
 * ������ֵ��
 */
unsigned int Rcon[10] = { 0x01000000, 0x02000000,
                 0x04000000, 0x08000000,
                 0x10000000, 0x20000000,
                 0x40000000, 0x80000000,
                 0x1b000000, 0x36000000
               };
/**
 * �л��Ҫ�õ��ľ���
 */
int colM[4][4] = { 2, 3, 1, 1,
                   1, 2, 3, 1,
                   1, 1, 2, 3,
                   3, 1, 1, 2
                 };
/**
 * ���л���õ��ľ���
 */
int deColM[4][4] = { 0xe, 0xb, 0xd, 0x9,
                     0x9, 0xe, 0xb, 0xd,
                     0xd, 0x9, 0xe, 0xb,
                     0xb, 0xd, 0x9, 0xe
                   };
/**
 * ��ȡ�������ݵĵ�8λ����4��λ
 */
int getLeft4Bit(int num)
{
    int left = num & 0x000000f0;
    return left >> 4;
}

/**
 * ��ȡ�������ݵĵ�8λ����4��λ
 */
int getRight4Bit(int num)
{
    return num & 0x0000000f;
}
/**
 * ������������S���л��Ԫ��
 */
int getNumFromSBox(int index)
{
//�벹�����
    int col,row;
    row = getLeft4Bit(index);
    col = getRight4Bit(index);
    return S[row][col];
}

/**
 * ��һ���ַ�ת�������
 */
int getIntFromChar(char c)
{
    int result = (int) c;
    return result & 0x000000ff;
}

/**
 * ��16���ַ�ת���4X4�����飬
 * �þ������ֽڵ�����˳��Ϊ���ϵ��£�
 * �������������С�
 */
void convertToIntArray(char *str, int pa[4][4])
{
    int k = 0;
    int i,j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
        {
            pa[j][i] = getIntFromChar(str[k]);
            k++;
        }
}

/**
 * ��������4���ַ��ϲ���һ��4�ֽڵ�����
 */
int getWordFromStr(char *str)
{
    int one, two, three, four;
    one = getIntFromChar(str[0]);
    one = one << 24;
    two = getIntFromChar(str[1]);
    two = two << 16;
    three = getIntFromChar(str[2]);
    three = three << 8;
    four = getIntFromChar(str[3]);
    return one | two | three | four;
}

/**
 * ��һ��4�ֽڵ����ĵ�һ�����������ĸ��ֽ�ȡ����
 * ���һ��4��Ԫ�ص������������档
 */
void splitIntToArray(int num, int array[4])
{
    int one, two, three;
    one = num >> 24;
    array[0] = one & 0x000000ff;
    two = num >> 16;
    array[1] = two & 0x000000ff;
    three = num >> 8;
    array[2] = three & 0x000000ff;
    array[3] = num & 0x000000ff;
}

/**
 * �������е�Ԫ��ѭ������stepλ
 */
void leftLoop4int(int array[4], int step)
{
//�벹�����
    int i,j,temp;
    for(i=0;i<step%4;i++)
    {
        temp = array[0];
        for(j=0;j<3;j++)
        {
            array[j] = array[j+1];
        }
        array[3] = temp;
    }
}

/**
 * �������еĵ�һ������������Ԫ�طֱ���Ϊ
 * 4�ֽ����͵ĵ�һ�������������ֽڣ��ϲ���һ��4�ֽ�����
 */
int mergeArrayToInt(int array[4])
{
    int one = array[0] << 24;
    int two = array[1] << 16;
    int three = array[2] << 8;
    int four = array[3];
    return one | two | three | four;
}
/**
 * ��Կ��չ�е�T��������ѭ�����ֽڴ��������
 */
int T(int num, int round)
{
    int numArray[4];
    int i;
    int result;
    splitIntToArray(num, numArray);
//�벹�����
    leftLoop4int(numArray,1);
    int s_array[4];
    for(i=0;i<4;i++)
    {
        s_array[i] = getNumFromSBox(numArray[i]);
    }
    result = mergeArrayToInt(s_array) ^ Rcon[round-1];
    return result;
}

/**
 * ��ӡW����
 */
void printW()
{
    int i, j;
    for(i = 0, j = 1; i < 44; i++,j++)
    {
        printf("w[%d] = 0x%x ", i, w[i]);
        if(j % 4 == 0)
            printf("\n");
    }
    printf("\n");
}


/**
 * ��չ��Կ������ǰ�w[44]�е�ÿ��Ԫ�س�ʼ��
 */
void extendKey(char *key)
{
    int i,j;
    //�벹�������ɺ����w[0]-w[43]
    int Nk=4,Nb=4,Nr=10;
    int temp[4],tempnum;
    for(i=0;i<Nk;i++)
    {
        // for(j=0;j<3;j++)
        // {
        //     temp[i] = key[4*i+j];
        // }
        // w[i] = mergeArrayToInt(temp);
        w[i] = getWordFromStr(key+i*Nb);
    }
    for(i=Nk;i<Nb*(Nr+1);i++)
    {
        // tempnum = w[i-1];
        if(i%Nk == 0)
        {
            // splitIntToArray(tempnum,temp);
            // leftLoop4int(temp,1);
            // tempnum = mergeArrayToInt(temp);
            // getArrayFrom4W()
            // temp = getNumFromSBox(mergeArrayToInt(leftLoop4int(splitIntToArray(tempnum),1)))
                    // ^ Rcon[i/Nk];
            tempnum = T(w[i-1],i/Nk);
        }
        else
        {
            tempnum = w[i-1];
        }
        w[i] = w[i-Nk] ^ tempnum;
    }
}

/**
 * ����Կ��
 */
void addRoundKey(int array[4][4], int round)
{

  //�벹�����
    int i,j;
    int temp[4];
    for(i=0;i<4;i++)
    {
        splitIntToArray(w[round*4+i],temp);
        for(j=0;j<4;j++)
        {
            array[j][i] = array[j][i] ^ temp[j];    // ���м���
        }
    }
}

/**
 * �ֽڴ���
 */
void subBytes(int array[4][4])
{
//�벹�����
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            array[i][j] = getNumFromSBox(array[i][j]);
        }
    }
}

/**
 * ����λ
 */
void shiftRows(int array[4][4])
{
//�벹�����
    int temp_line[4];
    int i,j;
    for(i=1;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            temp_line[j] = array[i][j];
        }
        leftLoop4int(temp_line,i);
        for(j=0;j<4;j++)
        {
            array[i][j] = temp_line[j];
        }
    }
}

int GFMul2(int s)
{
    int result = s << 1;
    int a7 = result & 0x00000100;

    if(a7 != 0)
    {
        result = result & 0x000000ff;
        result = result ^ 0x1b;
    }

    return result;
}

int GFMul3(int s)
{
    return GFMul2(s) ^ s;
}

int GFMul4(int s)
{
    return GFMul2(GFMul2(s));
}

int GFMul8(int s)
{
    return GFMul2(GFMul4(s));
}

int GFMul9(int s)
{
    return GFMul8(s) ^ s;
}

int GFMul11(int s)
{
    return GFMul9(s) ^ GFMul2(s);
}

int GFMul12(int s)
{
    return GFMul8(s) ^ GFMul4(s);
}

int GFMul13(int s)
{
    return GFMul12(s) ^ s;
}

int GFMul14(int s)
{
    return GFMul12(s) ^ GFMul2(s);
}

/**
 * GF�ϵĶ�Ԫ����
 */
int GFMul(int n, int s)
{
    int result;

    if(n == 1)
        result = s;
    else if(n == 2)
        result = GFMul2(s);
    else if(n == 3)
        result = GFMul3(s);
    else if(n == 0x9)
        result = GFMul9(s);
    else if(n == 0xb)//11
        result = GFMul11(s);
    else if(n == 0xd)//13
        result = GFMul13(s);
    else if(n == 0xe)//14
        result = GFMul14(s);

    return result;
}
/**
 * �л��
 */
void mixColumns(int array[4][4])
{

//�벹�����
    int temp[4][4];
    int i,j,k,t;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            temp[i][j] = array[i][j];
        }
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            array[i][j] = GFMul(colM[i][0],temp[0][j]);
            for(k=1;k<4;k++)
            {
                array[i][j] = array[i][j] ^ GFMul(colM[i][k],temp[k][j]);
            }
        }
    }
}
/**
 * ��4X4����ת���ַ���
 */
void convertArrayToStr(int array[4][4], char *str)
{
    int i,j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            *str++ = (char)array[j][i];
}
/**
 * �����Կ����
 */
int checkKeyLen(int len)
{
    if(len == 16)
        return 1;
    else
        return 0;
}


/**
 * ���� p: ���ĵ��ַ������顣
 * ���� plen: ���ĵĳ��ȡ�
 * ���� key: ��Կ���ַ������顣
 */
void aes(char *p, int plen, char *key)
{

    int keylen = strlen(key);
    int pArray[4][4];
    int k,i;

    /*if(plen == 0 || plen % 16 != 0)
    {
        printf("�����ַ����ȱ���Ϊ16�ı�����\n");
        exit(0);
    }

    if(!checkKeyLen(keylen))
    {
        printf("��Կ�ַ����ȴ��󣡳��ȱ���Ϊ16����ǰ����Ϊ%d\n",keylen);
        exit(0);
    }*/

    extendKey(key);//��չ��Կ
    //printW();
    for(k = 0; k < plen; k += 16)
    {
        convertToIntArray(p + k, pArray);

        addRoundKey(pArray, 0);//һ��ʼ������Կ��

        for(i = 1; i < 10; i++)
        {

            subBytes(pArray);//�ֽڴ���

            shiftRows(pArray);//����λ

            mixColumns(pArray);//�л��

            addRoundKey(pArray, i);

        }

        subBytes(pArray);//�ֽڴ���

        shiftRows(pArray);//����λ

        addRoundKey(pArray, 10);

        convertArrayToStr(pArray, p + k);
    }
}
/**
 * ������������S���л�ȡֵ
 */
int getNumFromS1Box(int index)
{
//�벹�����
    int col,row;
    row = getLeft4Bit(index);
    col = getRight4Bit(index);
    return S2[row][col];
}
/**
 * ���ֽڱ任
 */
void deSubBytes(int array[4][4])
{
//�벹�����
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            array[i][j] = getNumFromS1Box(array[i][j]);
        }
    }
}
/**
 * ��4��Ԫ�ص�����ѭ������stepλ
 */
void rightLoop4int(int array[4], int step)
{
//�벹�����
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

/**
 * ������λ
 */
void deShiftRows(int array[4][4])
{
//�벹�����
    int temp_line[4];
    int i,j;
    for(i=1;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            temp_line[j] = array[i][j];
        }
        rightLoop4int(temp_line,i);
        for(j=0;j<4;j++)
        {
            array[i][j] = temp_line[j];
        }
    }
}
/**
 * ���л��
 */
void deMixColumns(int array[4][4])
{
//�벹�����
    int temp[4][4];
    int i,j,k,t;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            temp[i][j] = array[i][j];
        }
    }
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            array[i][j] = GFMul(deColM[i][0],temp[0][j]);
            for(k=1;k<4;k++)
            {
                array[i][j] = array[i][j] ^ GFMul(deColM[i][k],temp[k][j]);
            }
        }
    }
}
/**
 * ������4X4����������
 */
void addRoundTowArray(int aArray[4][4],int bArray[4][4])
{
    int i,j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            aArray[i][j] = aArray[i][j] ^ bArray[i][j];
}
/**
 * ��4��32λ����Կ���л��4X4���飬
 * ���ڽ������л��
 */
void getArrayFrom4W(int i, int array[4][4])
{
    int index,j;
    int colOne[4], colTwo[4], colThree[4], colFour[4];
    index = i * 4;
    splitIntToArray(w[index], colOne);
    splitIntToArray(w[index + 1], colTwo);
    splitIntToArray(w[index + 2], colThree);
    splitIntToArray(w[index + 3], colFour);

    for(j = 0; j < 4; j++)
    {
        array[j][0] = colOne[j];
        array[j][1] = colTwo[j];
        array[j][2] = colThree[j];
        array[j][3] = colFour[j];
    }

}

/**
 * ���� c: ���ĵ��ַ������顣
 * ���� clen: ���ĵĳ��ȡ�
 * ���� key: ��Կ���ַ������顣
 */
void deAes(char *c, int clen, char *key)
{

    int cArray[4][4];
    int keylen,k;
    keylen = strlen(key);
    if(clen == 0 || clen % 16 != 0)
    {
        printf("�����ַ����ȱ���Ϊ16�ı��������ڵĳ���Ϊ%d\n",clen);
        exit(0);
    }

    if(!checkKeyLen(keylen))
    {
        printf("��Կ�ַ����ȴ��󣡳��ȱ���Ϊ16��24��32����ǰ����Ϊ%d\n",keylen);
        exit(0);
    }


    //�벹�����
    int i;
    int ciphertext[4][4],temp_w[4][4];
    extendKey(key); // ��Կ��չ
    for(k = 0; k < keylen; k += 16)
    {
        convertToIntArray(c + k, ciphertext);

        addRoundKey(ciphertext, 10);//һ��ʼ������Կ��

        for(i = 9; i > 0; i--)
        {

            deSubBytes(ciphertext);// ���ֽڴ���

            deShiftRows(ciphertext);// ������λ

            deMixColumns(ciphertext);// ���л��
            getArrayFrom4W(i,temp_w);
            deMixColumns(temp_w);
            addRoundTowArray(ciphertext, temp_w);
        }

        deSubBytes(ciphertext);// ���ֽڴ���

        deShiftRows(ciphertext);// ������λ

        addRoundKey(ciphertext, 0);

        convertArrayToStr(ciphertext, c + k);
    }
}
/**
*��ȡ�ַ���
*/
void getString(char *str, int len)
{

    int slen = read(0, str, len);
    for(int i = 0; i < slen; i++,str++)
    {
        if(*str == '\n')
        {
            *str = '\0';
            break;
        }
    }
}
/**
*��ӡASCCI��
*/
void printASCCI(char *str, int len)
{
    int c;
    for(int i = 0; i < len; i++)
    {
        c = (int)*str++;
        c = c & 0x000000ff;
        printf("0x%x ", c);
    }
    printf("\n");
}

/**
 * �ӱ�׼�����ж�ȡ�û�������ַ���
 */
void readPlainText(char *str, int *len)
{
    int plen;
    while(1)
    {
        getString(str, MAXLEN);
        plen = strlen(str);
        if(plen != 0 /*&& plen % 16 == 0*/)
        {
            printf("�����������Ϊ��%s\n", str);
            break;
        }
        else
        {
            printf("�����ַ����ȱ���Ϊ16�ı���,���ڵĳ���Ϊ%d\n", plen);
        }
    }
    *len = plen;
}
/**
 * ���ַ���д���ļ�
 */
void writeStrToFile(char *str, int len, char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "wb");
    for(int i = 0; i < len; i++)
        putc(str[i], fp);
    fclose(fp);
}

/**
*���ܺ�������ַ�д���ļ�
*/
void aesStrToFile(char *key)
{

    char p[MAXLEN];
    int plen;

    printf("������������ģ������ַ����ȱ���Ϊ16�ı���\n");
    readPlainText(p,&plen);

    printf("����Կ..................\n");
    aes(p, plen, key);//AES����
    printf("����AES����..................\n");
    printf("�����������ĵ�ASCCIΪ��\n");
    printASCCI(p, plen);
    char fileName[64];
    printf("����������Ҫд�����ļ���������'test.txt':\n");
    if(scanf("%s", fileName) == 1)
    {
        writeStrToFile(p, plen, fileName);
        printf("�Ѿ�������д��%s����,���������иó���ĵ�ǰĿ¼���ҵ�����\n", fileName);
    }
}
/**
 * ���ļ��ж�ȡ�ַ���
 */
int readStrFromFile(char *fileName, char *str)
{
    FILE *fp = fopen(fileName, "rb");
    if(fp == NULL)
    {
        printf("���ļ���������ȷ���ļ����ڵ�ǰĿ¼�£�\n");
        exit(0);
    }

    int i;
    for(i = 0; i < MAXLEN && (str[i] = getc(fp)) != EOF; i++);

    if(i >= MAXLEN)
    {
        printf("�����ļ�����\n");
        exit(0);
    }

    str[i] = '\0';
    fclose(fp);
    return i;
}


void deAesFile(char *key)
{
    char fileName[64];
    char c[MAXLEN];//�����ַ���
    printf("������Ҫ���ܵ��ļ��������ļ�����ͱ�������ͬһ��Ŀ¼\n");
    if(scanf("%s", fileName) == 1)
    {
        int clen = readStrFromFile(fileName, c);
        printf("��ʼ����.........\n");
        deAes(c, clen, key);
        printf("���ܺ������ASCIIΪ��\n");
        printASCCI(c, clen);
        printf("����Ϊ��%s\n", c);
        writeStrToFile(c,clen,fileName);
        printf("���ڿ��Դ�%s���鿴���ܺ�������ˣ�\n",fileName);
    }
}