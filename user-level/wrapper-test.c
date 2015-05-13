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

int rsa_box_fd;

// print out 128 bit int, but by [sections]
void print_128_bit_integer(int32_t *input_x)
{
    int i;  

    for (i = 0; i < 4; i++)
        printf("quartile(%d): %u\n", i, input_x[i]);  
}

int main()
{
    /*
     * main tests
     */

    // for encryption
    int32_t public_e[4] = {8, 7, 200, 500};
    int32_t public_n[4] = {0, 0, 0, 0};
    int32_t *public_e_output = malloc(sizeof(int32_t) * 4);
    int32_t public_n_output[4];
    printf("RSA Box device driver started\n");

    /* DECRYPT */ 
    printf("\n[test case: storing and reading public keys...]\n\n");
    store_keys(PUBLIC, public_e, public_n); 
    __read_public_keys(public_e_output, public_n_output);
    
    free(public_e_output);
    return 0;
/*
    // [setting] n
    input_x_n[0] = 0;
    input_x_n[1] = 1;
    input_x_n[2] = 0;
    input_x_n[3] = 1;
 
    // [setting] message to encrypt
    input_x_encrypt[0] = 5; 
    input_x_encrypt[1] = 5; 
    input_x_encrypt[2] = 3; 
    input_x_encrypt[3] = 0; 
    input_x_encrypt[4] = 0 ;  
    
    // [setting] return values (reset to 0)
    return_x[0] = 0; 
    return_x[1] = 0; 
    return_x[2] = 0; 
    return_x[3] = 0; 

    // ENCRYPT
    printf("\n[encrypt...]\n\n");
    intwise_encrypt(input_x_encrypt); 
    
    printf("\n[read result...]\n\n");
    read_segment(return_x);
    print_128_bit_integer(return_x); 
    
    // MAKE KEYS
    printf("\n[make keys...]\n\n");
    store_private_keys(input_x_n); 

    printf("\n[read result...]\n\n");
    read_segment(return_x);
    print_128_bit_integer(return_x); 
*/
    printf("\n...done\n");
    return 0;
}

