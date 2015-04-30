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

int main()
{
    /*
     * main tests
     */

    int i; 
    int32_t input_x_decrypt[12];
    int32_t input_x_encrypt[5]; 
    int32_t input_x_n[4]; 
    int32_t return_x[4]; 
    
    static const char filename[] = "/dev/rsa_box";

    printf("RSA Box device driver started\n");

    if ( (rsa_box_fd = open(filename, O_RDWR)) == -1)
    {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    } 
    
    // [setting] message to decrypt
    for(i = 0; i < 12; i++)
    	input_x_decrypt[i] = 1; 
    
    // [setting] n
    input_x_n[0] = 0;
    input_x_n[1] = 1;
    input_x_n[2] = 0;
    input_x_n[3] = 1;
 
    // DECRYPT
    printf("\n[decrypt...]\n\n");
    intwise_decrypt(input_x_decrypt);

    printf("\n[read result...]\n\n"); 
    read_segment(return_x);
    print_128_bit_integer(return_x); 
    
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

    printf("\n...done\n");
    return 0;
}

