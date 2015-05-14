#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>       /* for sleep() */
#include <stdint.h>     /* for unit32_t */
#include "../rsa_box.h"
#include "c-wrapper.h"
#include "instructions.h"

#include "prime-generator.h"

int rsa_box_fd;

// print out 128 bit int, but by [sections]
void print_128_bit_integer(int32_t *input_x)
{
    int i;  

    for (i = 0; i < 4; i++)
        printf("quartile(%d): %u\n", i, input_x[i]);  
}

/*
 * Return 1 if all size 32 bit numbers in the value are 
 * equal; else return 0.
 */
int large_numbers_equal(int32_t *a, int32_t *b, int size)
{
    int i;
    for (i = 0; i < size; i++)
        if (a[i] != b[i]) return 0;

    return 1;
}

int main()
{
    /*
     * main tests
     */
    int32_t p[2];
    int32_t q[2];

    int32_t e[1] = {13};
    int32_t n[4];
    int32_t e_check[4];
    int32_t n_check[4];

    //int32_t message[4]  = {0,1,0,0};  

    printf("RSA Box device driver started\n");
    
    /* STORING PRIVATE KEY. */ 
    p[0] = 0;
    p[1] = 13;
    q[0] = 0;
    q[1] = 7;

    printf("\n[test case: storing private key...]\n");
    store_keys(PRIVATE, p, q); 
    // need to be able to get back n to send to other client

    /* DECRYPT */ 
    read_our_public_key(n);
    print_128_bit_integer(n);
   
    return 0; 
/*
    printf("\n[test case: storing and reading public keys...]\n");
    send_int_encrypt_decrypt(DECRYPT_SEND, message, public_e_output); 
    for(i = 0; i < 5; i++) {
	printf("%d\n", public_e_output[i]);  
    }
*/
    
    /* STORING AND READING OTHER'S PUBLIC KEY. */
    printf("\n[test case: storing and reading public keys...]\n");
    store_keys(PUBLIC, n, e);
    __read_public_keys(n_check, e_check);
    if (large_numbers_equal(n, n_check, 4) &&
         large_numbers_equal(e, e_check, 4))
    {
        printf("successfully storing and reading public keys.\n");;    }
    
    return 0;
}
