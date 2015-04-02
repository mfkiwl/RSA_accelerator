/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 */

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../rsa_box.h" /* kernel space code */
#include "primes.h"	/* prime number generating code */

#define BIT_WIDTH 	128
#define INT_SIZE	32
#define RSA_SIZE 	BIT_WIDTH / INT_SIZE 
static int BIT_SEGMENTS[RSA_SIZE] =  {0, 2, 4, 6}; 

int vga_led_fd;

//function to write a 128 bit int, sent to kernel space as an int array of size 4
void write_segment(unsigned int *bit_input)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i; 
    for(i = 0; i < RSA_SIZE; i++)
    {
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  bit_input[i];

    	if (ioctl(vga_led_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
    }
}

//function to read 128 bit from kernel space and store the value in bit_output in userspace
void read_segment(unsigned int *bit_output)
{
    rsa_box_arg_t rsa_userspace_vals;

    int i;    
    for(i = 0; i < RSA_SIZE; i++){
    	rsa_userspace_vals.digit = BIT_SEGMENTS[i];
    	
	// reads value from kernel space into user space
	if (ioctl(vga_led_fd, RSA_BOX_READ_DIGIT, &rsa_userspace_vals)) {
      		perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    	}
        
    	bit_output[i] =  rsa_userspace_vals.segments; 
    }
}

//function to print the 128 bit number, it just prints the sections rather than the value. 
void print_128_bit_integer(unsigned int *input_x){
   int i;  
   
   for(i = 0; i < RSA_SIZE; i++)
   {
	printf("Quartile(%d): %u\n", i+1, input_x[i]);  
   }
}

//function to test that the value sent to be written is equal to value read
void check_equality(unsigned int *input_x, unsigned int *return_x){
    int i; 
    print_128_bit_integer(input_x);
    print_128_bit_integer(return_x); 

    for(i = 0; i < RSA_SIZE; i++)
    {
	if(!(input_x[i] == return_x[i]) )
	{
	    perror("Error reading/writing, values do not match\n"); 
	}
    }
    printf("Read/Write Successful\n"); 
}

int main()
{
    int i;
    int randx; 
    unsigned int input_x[RSA_SIZE]; 
    unsigned int return_x[RSA_SIZE]; 

    static const char filename[] = "/dev/rsa_box";

    printf("RSA Box device driver started\n");

    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
 
    for(i=0; i < RSA_SIZE; i++)
    {
        input_x[i] = i; 
    }
/*
    write_segment(input_x);
    read_segment(return_x);

    check_equality(input_x, return_x);   
*/

    // get large primes
    int prime_1[BIT_LENGTH / sizeof(int)]; 
    int prime_2[BIT_LENGTH / sizeof(int)];

    // generate large primes; regenerate if they are equal
    do {
	get_large_prime(prime_1);
	get_large_prime(prime_2);
    } while (are_equal(prime_1, prime_2) == TRUE);

    print_prime(prime_1);
    print_prime(prime_2);

    printf("RSA Box device driver terminating\n");
    return 0;
}
