/*
 * Userspace program that communicates with the RSA_Box device driver
 * primarily through ioctls.
 *
 * Original VGA_LED code by Stephen A. Edwards, Columbia University
 */

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
#include "instructions.h"
#include "c-wrapper.h"

void read_segment(int32_t *bit_output, int size);
void send_bits(int32_t *value, int count); 

/* globals */
static int BIT_SEGMENTS[5] =  {1, 2, 3, 4, 5}; 
static int BIT_SEGMENTS_READ[5] = {0, 1, 2, 3, 4};
static int rsa_box_fd = -1;
static int empty[4] = {0, 0, 0, 0}; 

void set_fd()
{
    char *filename = "/dev/rsa_box";
    if ( (rsa_box_fd = open(filename, O_RDWR)) == -1)
    {
        fprintf(stderr, "could not open %s\n", filename);
    }
}

/*
 * Tells hardware what instruction to include the incoming
 * data with.
 */
void send_instruction(int operation)
{
    rsa_box_arg_t rsa_userspace_vals;
    if (rsa_box_fd == -1)
        set_fd();

    rsa_userspace_vals.address =  INSTRUCTION;
    rsa_userspace_vals.data_in = operation;

#ifdef PRINTVERBOSE
    log_instruction(operation);
#endif

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }
}

/*
 * Sends count int32_t's to the hardware. 
 * Always call send_instruction() first or the hardware won't know
 * what to do with the incoming data.
 */
void send_bits(int32_t *value, int count)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;
    
    if (rsa_box_fd == -1)
        set_fd();

    for (i = 0; i < count; i++)
    {
        rsa_userspace_vals.address = BIT_SEGMENTS[i];
        rsa_userspace_vals.data_in = value[i];

#ifdef PRINTVERBOSE
        printf("[sending] %d // %d\n", BIT_SEGMENTS[i], value[i]); 
#endif

        if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
            perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
        }
    }

}

/*
 * Stores keys into the specified registers, PUBLIC or PRIVATE
 * key registers.
 */
void store_keys(int type, int32_t *key_1, int32_t *key_2)
{
    if (type == PRIVATE)
    {
        send_instruction(STORE_PRIVATE_KEY_1);
        send_bits(key_1, 2); // p
        send_instruction(STORE_PRIVATE_KEY_2);
        send_bits(key_2, 2); // q
    }
    
    if (type == PUBLIC)
    {
        send_instruction(STORE_PUBLIC_KEY_1);
        send_bits(key_1, 4); // n 
       
        

	send_instruction(STORE_PUBLIC_KEY_2);
        send_bits(key_2, 1); // e
    }
}

/*
 * Send data to encrypt/decrypt to device.
 */
void send_int_encrypt_decrypt(int action, int32_t *input, int32_t *output)
{
    if (action == ENCRYPT_SEND)
    {
	send_instruction(STORE_MESSAGE);
        send_bits(input, 4); // m

        send_instruction(ENCRYPT_BITS);
        send_bits(input, 4);

	__read_encryption(output); 
    }
    
    if (action == DECRYPT_SEND)
    {
        send_instruction(DECRYPT_BITS);
        send_bits(input, 4);
    }
}

/*
 * Return the public keys on this device.
 *
 * (Note: the interface to read private keys was intentionally ommitted.
 */

void __read_encryption(int32_t *encryption){
	
	int32_t valid[5] = {0,0,0,0,0};
	int i; 		
	send_instruction(ENCRYPT_BITS); 
	send_bits(valid, 2); 
	while(!valid[4]){
		send_instruction(ENCRYPT_BITS); 
		read_segment(valid, 5); 
	} 

	read_segment(valid, 5); 
	
	//sleep(5); 
        //read_segment(valid, 5);
 	
        for(i=0; i<4; i++){
		encryption[i] = valid[i]; 
	}

}
void __read_public_keys(int32_t *key_1, int32_t *key_2)
{
    send_instruction(READ_PUBLIC_KEY_1);
    send_bits(empty, 1); 
    read_segment(key_1, 5);
    
    send_instruction(READ_PUBLIC_KEY_2);
    send_bits(empty, 1); 
    read_segment(key_2, 5);
}

void read_segment(int32_t *bit_output, int size)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    if (rsa_box_fd == -1)
        set_fd();

    for (i = 0; i < size; i++)
    {
        rsa_userspace_vals.address = BIT_SEGMENTS_READ[i];

        if (ioctl(rsa_box_fd, RSA_BOX_READ_DIGIT, &rsa_userspace_vals)) 
        {
            perror("ioctl(RSA_BOX_READ_DIGIT) failed");
        }

        bit_output[i] = rsa_userspace_vals.data_in; 
#ifdef PRINTVERBOSE
        printf("[sending] %d // %d\n", BIT_SEGMENTS_READ[i], bit_output[i]); 
#endif        
    }
}

/*
 * Get the product of p and q.
 */
void read_our_N(int32_t *n)
{
    send_instruction(READ_OUR_N);
    send_bits(empty, 4); 
    read_segment(n, 4);
}

/* 
 * Read 128 bits from hardware output into into [bit_output]. 
 */
void read_output(int32_t *bit_output)
{
    read_segment(bit_output, 4);
}
