/*
 * Userspace program that communicates with the RSA_Box device driver
 * primarily through ioctls.
 *
 * Original VGA_LED code by Stephen A. Edwards
 * Columbia University
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


/* size constants */
#define ADDR_SIZE_MAKE_KEY 4
#define ADDR_SIZE_ENCRYPT 5
#define ADDR_SIZE_DECRYPT 4
#define READ_SIZE_RSA 4

/* globals */
static int BIT_SEGMENTS[5] =  {1, 2, 3, 4, 5}; 
static int BIT_SEGMENTS_READ[4] = {0, 1, 2, 3};
static int rsa_box_fd;

void set_fd()
{
    char *filename = "/dev/rsa_box";
    if ( (rsa_box_fd = open(filename, O_RDWR)) == -1)
    {
        fprintf(stderr, "could not open %s\n", filename);
    }
}

void store_private_keys(uint32_t *p_and_q)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments =  MAKE_KEY;

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_MAKE_KEY ;i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  p_and_q[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], p_and_q[i]); 

    	if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }
}

void intwise_encrypt(uint32_t *message_n)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments =  ENCRYPT; 

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_ENCRYPT; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  message_n[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], message_n[i]); 

    	if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }
    // uint32_t e = 65537; 
    
}

/* sends decrypt instruction to hardware. */
void intwise_decrypt(uint32_t *cypher_n_d)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_1;

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT ; i++)
    {
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i]); 

    	if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_2;

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT; i++)
    {
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i+ADDR_SIZE_DECRYPT];

	printf("[sending] %d // %d\n", 
                BIT_SEGMENTS[i], 
                cypher_n_d[i+ADDR_SIZE_DECRYPT]); 

    	if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }


    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_3;

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }

    for (i = 0; i < ADDR_SIZE_DECRYPT ;i++)
    {
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments = cypher_n_d[i + 2 * ADDR_SIZE_DECRYPT];

	printf("[sending] %d // %d\n", 
                BIT_SEGMENTS[i], 
                cypher_n_d[i + 2 * ADDR_SIZE_DECRYPT]); 

    	if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }
}

// read 128 bit from kernel space into user space and store in [bit_output]
void read_segment(uint32_t *bit_output)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    for(i = 0; i < READ_SIZE_RSA; i++)
    {
    	rsa_userspace_vals.digit = BIT_SEGMENTS_READ[i];
    	
	if (ioctl(rsa_box_fd, RSA_BOX_READ_DIGIT, &rsa_userspace_vals)) 
        {
      		perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
        
    	bit_output[i] = rsa_userspace_vals.segments; 
    }
}

// print out 128 bit int, but by [sections]
void print_128_bit_integer(uint32_t *input_x)
{
   int i;  
   
   for (i = 0; i < 4; i++)
   {
	printf("quartile(%d): %u\n", i, input_x[i]);  
   }
}
