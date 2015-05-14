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

int main()
{
    /*
     * main tests
     */
    // for encryption
    int i; 
    int32_t public_e[4] = {8,0,0,0};
    int32_t public_n[4] = {0, 0, 1, 0};
    int32_t message[4]  = {0,1,0,0};  

    int32_t *public_e_output = malloc(sizeof(int32_t) * 5);
    printf("RSA Box device driver started\n");

    /* DECRYPT */ 
    printf("\n[test case: storing and reading public keys...]\n");
    store_keys(PUBLIC, public_n, public_e); 
    send_int_encrypt_decrypt(DECRYPT_SEND, message, public_e_output); 
    for(i = 0; i < 5; i++) {
	printf("%d\n", public_e_output[i]);  
    }
    free(public_e_output);
    return 0;
}
