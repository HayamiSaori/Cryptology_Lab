#include <gmp.h>
#include <gmpxx.h>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;
const int MAX_PLAINTEXT_LEN = 2048;
const int MAX_CIHPERTEXT_LEN = 2048;
const int KEY_LEN = 128;
int main(void)
{
    // get the plaintext
    char plaintext[MAX_PLAINTEXT_LEN];
    int i,j;
    cout << "Please input the plain text:" << endl;
    cin.getline(plaintext,MAX_PLAINTEXT_LEN);
    cout << "The plaintext(ascii) is:" << endl;
    for(i=0;i<strlen(plaintext);i++)
    {
        printf("%x",plaintext[i]);
    }
    cout << endl;
    // cout << "The plaintext is:" << endl << plaintext << endl;

    // generate p,q
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt,time(NULL));
    mpz_t p,q;
    mpz_init(p);
    mpz_init(q);
    mpz_urandomb(p,grt,KEY_LEN);
    mpz_urandomb(q,grt,KEY_LEN);
    mpz_nextprime(p,p);
    mpz_nextprime(q,q);
    gmp_printf("p:\t%Zx\nq:\t%Zx\n",p,q);

    // calculate n = p * q
    mpz_t n;
    mpz_init(n);
    mpz_mul(n,p,q);
    gmp_printf("n:\t%Zx\n",n);

    // calculate phi(n) = (p-1) * (q-1)
    mpz_t phi_n;
    mpz_init(phi_n);
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
    mpz_mul(phi_n,p,q);
    gmp_printf("phi(n):\t%Zx\n",phi_n);
    
    // select e as a prime 65537
    mpz_t e;
    mpz_init(e);
    mpz_set_ui(e,65537);
    gmp_printf("Public key (n,e):\n(%Zx,%Zx)\n",n,e);

    // calculate d
    mpz_t d;
    mpz_init(d);
    mpz_invert(d,e,phi_n);
    gmp_printf("Private key d:\n%Zx\n",d);

    // Encryption
    mpz_t temp_plaintext,temp_ciphertext;
    mpz_init(temp_plaintext);
    mpz_init(temp_ciphertext);
    int block_len,bias,group_num;
    unsigned long ch;
    // cout << "n len:" << mpz_sizeinbase(n,16) << endl;
    block_len = ((mpz_sizeinbase(n,16) - 1) / 2) * 2;   // make sure that m < n
    // cout << "block len:" << block_len << endl;
    group_num = (strlen(plaintext) * 2) / block_len + 1;
    cout << "The ciphertext is:" << endl;
    for(i=0;i<group_num;i++)
    {
        bias = i * (block_len / 2);
        mpz_init(temp_plaintext);
        mpz_init(temp_ciphertext);
        for(j=0;j<(block_len/2);j++)
        {
            if((bias + j) == strlen(plaintext))
            {
                break;
            }
            ch = plaintext[bias+j];
            mpz_mul_ui(temp_plaintext,temp_plaintext,256);  // left-shift 8 hex bits
            mpz_add_ui(temp_plaintext,temp_plaintext,ch);
        }
        mpz_powm(temp_ciphertext,temp_plaintext,e,n);       // c = m^e mod n
        cout << "group " << i << ":" << endl;
        gmp_printf("%Zx\n",temp_ciphertext);
        // cout << "group " << i << ":\tsize:" << mpz_sizeinbase(temp_plaintext,16) << endl;
        // gmp_printf("%Zx\n",temp_plaintext);
    }
    cout << endl;

    // Decryption
    for(i=0;i<group_num;i++)
    {
        mpz_init(temp_plaintext);
        mpz_init(temp_ciphertext);
        cout << "Please input the ciphertext group " << i << ":" << endl;
        mpz_inp_str(temp_ciphertext,NULL,16);
        mpz_powm(temp_plaintext,temp_ciphertext,d,n);
        cout << "the cipher text of group " << i << ":" << endl;
        gmp_printf("%Zx\n",temp_plaintext);
    }
    
    // Exit
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(phi_n);
    mpz_clear(e);
    mpz_clear(temp_plaintext);
    mpz_clear(temp_ciphertext);
    return 0;
}