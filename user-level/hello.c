/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 */

#include <stdio.h>
#include "../rsa_box.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// before writing any data, you need to specify which instruction you want to use. 
// this is done by writing address 0, i.e. INSTRUCTION with the appropriate action (MAKE_KEY, ENCRYPT, DECRYPT...)

#define INSTRUCTION 0
#define MAKE_KEY 1
#define ENCRYPT 2
#define DECRYPT_1 3
#define DECRYPT_2 7
#define DECRYPT_3 11

#define ADDR_SIZE_MAKE_KEY 4
#define ADDR_SIZE_ENCRYPT 5
#define ADDR_SIZE_DECRYPT 4
#define READ_SIZE_RSA 4

static int BIT_SEGMENTS[5] =  {1, 2, 3, 4, 5}; 
static int BIT_SEGMENTS_READ[4] = {0, 1, 2, 3};
int vga_led_fd;

// function declarations
void make_keys(unsigned int *p_and_q);
void encrypt(unsigned int *message_n);
void decrypt(unsigned int *cypher_n_d);
void read_segment(unsigned int *bit_output);
void print_128_bit_integer(unsigned int *input_x);

void make_keys(unsigned int *p_and_q)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments =  MAKE_KEY;

    if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_MAKE_KEY ;i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  p_and_q[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], p_and_q[i]); 

    	if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }
}

void encrypt(unsigned int *message_n)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments =  ENCRYPT; 

    if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_ENCRYPT; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  message_n[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], message_n[i]); 

    	if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }
    // unsigned int e = 65537; 
    
}

/* sends decrypt instruction to hardware. */
void decrypt(unsigned int *cypher_n_d)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_1;

    if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT ; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i]); 

    	if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }


    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_2;

    if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT ; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i+ADDR_SIZE_DECRYPT];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i+ADDR_SIZE_DECRYPT]); 

    	if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }


    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_3;

    if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }

    for (i = 0; i < ADDR_SIZE_DECRYPT ;i++) {
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i + 2 * ADDR_SIZE_DECRYPT];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i + 2 * ADDR_SIZE_DECRYPT]); 

    	if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }
}

// read 128 bit from kernel space into user space and store in [bit_output]
void read_segment(unsigned int *bit_output)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    for(i = 0; i < READ_SIZE_RSA ; i++){
    	rsa_userspace_vals.digit = BIT_SEGMENTS_READ[i];
    	
	if (ioctl(vga_led_fd, RSA_BOX_READ_DIGIT, &rsa_userspace_vals)) {
      		perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
        
    	bit_output[i] = rsa_userspace_vals.segments; 
    }
}

// print out 128 bit int, but by [sections]
void print_128_bit_integer(unsigned int *input_x)
{
   int i;  
   
   for (i = 0; i < 4; i++)
   {
	printf("quartile(%d): %u\n", i, input_x[i]);  
   }
}

int main()
{
    /*
     * main tests
     */

    int i, j; 
    unsigned int randx; 
    unsigned int input_x_decrypt[12];
    unsigned int input_x_encrypt[5]; 
    unsigned int input_x_n[4]; 
    
    unsigned int return_x[4]; 
    
    int iterations; 
    static const char filename[] = "/dev/rsa_box";

    printf("RSA Box device driver started\n");

    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
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
    decrypt(input_x_decrypt);

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
    encrypt(input_x_encrypt); 
    
    printf("\n[read result...]\n\n");
    read_segment(return_x);
    print_128_bit_integer(return_x); 
    
    // MAKE KEYS
    printf("\n[make keys...]\n\n");
    make_keys(input_x_n); 

    printf("\n[read result...]\n\n");
    read_segment(return_x);
    print_128_bit_integer(return_x); 

    printf("\n...done\n");
    return 0;
}
