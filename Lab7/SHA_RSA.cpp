#include <iostream>
#include <gmpxx.h>
#include <gmp.h>
#include "SHA1.h"
using namespace std;
const int KEY_LEN = 128;
int main(void)
{
/*---------- Simulate the actions of sender:calculate the hash and encrypt it with RSA private key. ----------*/
    int i;
    getSHA("sender.txt");
    // get the plaintext
    mpz_t m;
    mpz_init(m);
    for(i=0;i<4;i++)
    {
        mpz_add_ui(m,m,state[i]);
        mpz_mul_ui(m,m,4294967296); // left shift 32 bits
    }
    mpz_add_ui(m,m,state[i]);
    gmp_printf("The hash value is:\n%Zx\n",m);
    cout << "\nNow encrypte the hash value" << endl;

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
    mpz_clear(p);
    mpz_clear(q);
    // select e as a prime 65537
    mpz_t e;
    mpz_init(e);
    mpz_set_ui(e,65537);
    gmp_printf("\nPublic key (n,e):\n(%Zx,%Zx)\n",n,e);

    // calculate d
    mpz_t d;
    mpz_init(d);
    mpz_invert(d,e,phi_n);
    gmp_printf("\nPrivate key d:\n%Zx\n",d);

    // sign the hash value with private key 
    mpz_t c;
    mpz_init(c);
    mpz_powm(c,m,d,n);
    gmp_printf("\nSignature of hash value:\n%Zx\n",c);

/*---------- Simulate the actions of reciever:decrypt the hash(using public key) and compare it with the hash of the plaintext. ----------*/
    cout << "\nNow decrypt the hash value" << endl;
    mpz_init(m);
    mpz_powm(m,c,e,n);
    gmp_printf("\nThe decryption result of signature:\n%Zx\n",m);
    getSHA("reciever.txt");
    mpz_t m_compare;
    mpz_init(m_compare);
    for(i=0;i<4;i++)
    {
        mpz_add_ui(m_compare,m_compare,state[i]);
        mpz_mul_ui(m_compare,m_compare,4294967296); // left shift 32 bits
    }
    mpz_add_ui(m_compare,m_compare,state[i]);
    gmp_printf("The hash value is:\n%Zx\n",m_compare);
    // Authentication
    if(mpz_cmp(m,m_compare) == 0)
    {
        cout << "\nThe signature is valid!" << endl;
    }
    else
    {
        cout << "\nThe signature is invalid!" << endl;
    }
    mpz_clear(n);
    mpz_clear(phi_n);
    mpz_clear(m);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(m_compare);
    mpz_clear(c);

}