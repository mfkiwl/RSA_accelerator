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

    int32_t e[1] = {3};
    int32_t n[4];	
    int32_t n_1[4];
    int32_t e_check[4];
    int32_t n_check[4];
    int32_t e_message[4]; 
    int32_t d_message[4]; 
    int32_t extended_e; 

    int32_t d_n[4];  
    int32_t message[4]  = {13,0,0,0};  

    printf("RSA Box device driver started\n");
    
    /* STORING PRIVATE KEY. */ 
    p[0] = 23;
    p[1] = 0;
    q[0] = 17;
    q[1] = 0;
 

	
    printf("\n[test case: storing private key...]\n");
    store_keys(PRIVATE, p, q); 
    // need to be able to get back n to send to other client

    /* DECRYPT */ 
    read_our_N(n);
    print_128_bit_integer(n);


    

    store_keys(PRIVATE, p, q); 
    // need to be able to get back n to send to other client

    /* DECRYPT */ 

    //p[0] -= 1; 
    //q[0] -= 1;
    printf("Our n1\n"); 
    read_our_N(n_1);
    print_128_bit_integer(n_1);
   


    store_keys(PUBLIC, n, e);

    printf("print n\n"); 
    print_128_bit_integer(n); 
    
    printf("print e\n"); 
    print_128_bit_integer(e); 


    send_int_encrypt_decrypt(ENCRYPT_SEND, message, e_message);  

    d_n[0] = 235; 
    d_n[1] =  0; 
    d_n[2] =  0; 
    d_n[3] = 0;   

    printf("E\n"); 
    print_128_bit_integer(e_message);
    store_d(d_n); 

    send_message2(e_message); 
    

    send_int_encrypt_decrypt(DECRYPT_SEND, e_message, d_message);  
    printf("message\n"); 
    print_128_bit_integer(d_message); 

/*
    	printf("store_d.....\n");
    store_d(d_n, e_message, d_message); 
    
    //send_int_encrypt_decrypt(DECRYPT_SEND, e_message, d_message);
    print_128_bit_integer(d_message); 
    
*/	
    
   
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
