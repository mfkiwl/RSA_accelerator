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

#define ADDR_SIZE       128 / 32

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

/*
 * Tells hardware what instruction to include the incoming
 * data with.
 */
void send_instruction(int operation)
{
    rsa_box_arg_t rsa_userspace_vals;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = operation;

    printf("[instruction] calling %d\n", operation);

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
    
    for (i = 0; i < count; i++)
    {
        rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
        rsa_userspace_vals.segments =  value[i];

        printf("[sending] %d // %d\n", BIT_SEGMENTS[i], value[i]); 

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
        send_instruction(STORE_PUBLIC_KEYS);
        send_bits(key_1, 4); // n
        send_bits(key_2, 1); // e
    }
}

void send_int_encrypt_decrypt(int action, int32_t *input)
{
    if (action == ENCRYPT_SEND)
    {
        send_instruction(ENCRYPT_BITS);
        send_bits(input, 4);
    }
    
    if (action == DECRYPT_SEND)
    {
        send_instruction(DECRYPT_BITS);
        send_bits(input, 4);
    }
}

void read_segment(int32_t *bit_output, int size)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    for (i = 0; i < size; i++)
    {
        rsa_userspace_vals.digit = BIT_SEGMENTS_READ[i];

        if (ioctl(rsa_box_fd, RSA_BOX_READ_DIGIT, &rsa_userspace_vals)) 
        {
            perror("ioctl(RSA_BOX_READ_DIGIT) failed");
        }

        bit_output[i] = rsa_userspace_vals.segments; 
    }
}

/* 
 * Read 128 bits from hardware output into into [bit_output]. 
 */
void read_output(int32_t *bit_output)
{
    read_segment(bit_output, 4);
}
