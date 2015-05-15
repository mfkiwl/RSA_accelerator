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

    //int32_t n[4];	
    int32_t n_our[4]; // our copy of n
    int32_t e_message[4]; 
    int32_t d_message[4] = {0,0,0,0}; 

    int32_t message[4]  = {13,0,0,0};  

    printf("RSA Box device driver started\n");

    /* STORING PRIVATE KEYS, e.g. 23 and 17. */ 
    p[0] = 23;
    p[1] = 0;
    q[0] = 17;
    q[1] = 0;
 
    printf("\n[test case: storing private key...]\n");
    key_swap(p, q, n_our);
    
    printf("current value of n:\n");
    print_128_bit_integer(n_our);
 

     
    /* ENCRYPT/DECRYPT TEST */ 
    printf("Original message:");
    print_128_bit_integer(message);

    send_int_encrypt_decrypt(ENCRYPT_SEND, message, e_message);  

    printf("Encrypted message:");
    print_128_bit_integer(e_message);
    print_128_bit_integer(e_message); 

    //return 0; 
    send_int_encrypt_decrypt(DECRYPT_SEND, e_message, d_message);  

    printf("Decrypted message (should match original):");
    print_128_bit_integer(d_message); 


    return 0;
}
