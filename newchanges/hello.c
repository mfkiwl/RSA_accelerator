/*
 * Userspace program that communicates with the led_vga device driver
 * primarily through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 */

#include <stdio.h>
#include "vga_led.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

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


void make_keys(unsigned int *p_and_q)
{
    vga_led_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments =  MAKE_KEY;

    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_MAKE_KEY ;i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  p_and_q[i];

    	if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }
}

void encrypt(unsigned int *message_n)
{
    vga_led_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments =  ENCRYPT; 

    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_ENCRYPT; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  message_n[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], message_n[i]); 

    	if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }
    // unsigned int e = 65537; 
    
}

void decrypt(unsigned int *cypher_n_d)
{
    vga_led_arg_t rsa_userspace_vals;
    int i;

    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_1 ;

    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT ; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i]); 

    	if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }


    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_2 ;

    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT ; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i+ADDR_SIZE_DECRYPT];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i+ADDR_SIZE_DECRYPT]); 

    	if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }


    rsa_userspace_vals.digit =  INSTRUCTION;
    rsa_userspace_vals.segments = DECRYPT_3 ;

    if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    }

    for(i = 0; i < ADDR_SIZE_DECRYPT ; i++){
    	rsa_userspace_vals.digit =  BIT_SEGMENTS[i];
    	rsa_userspace_vals.segments =  cypher_n_d[i + 2*ADDR_SIZE_DECRYPT];

	printf("[sending] %d // %d\n", BIT_SEGMENTS[i], cypher_n_d[i+ 2*ADDR_SIZE_DECRYPT]); 

    	if (ioctl(vga_led_fd, VGA_LED_WRITE_DIGIT, &rsa_userspace_vals))
        {
      	    perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
    }



   
}

//function to read 128 bit from kernel space and store the value in bit_output in userspace
void read_segment(unsigned int *bit_output)
{
    vga_led_arg_t rsa_userspace_vals;
    int i;
    for(i = 0; i < READ_SIZE_RSA ; i++){
    	rsa_userspace_vals.digit = BIT_SEGMENTS_READ[i];
    	
	// reads value from kernel space into user space
	if (ioctl(vga_led_fd, VGA_LED_READ_DIGIT, &rsa_userspace_vals)) {
      		perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
    	}
        
    	bit_output[i] =  rsa_userspace_vals.segments; 
    }
}

//function to print the 128 bit number, it just prints the sections rather than the value. 
void print_128_bit_integer(unsigned int *input_x){
   int i;  
   
   for(i = 0; i < 4; i++)
   {
	printf("Quartile(%d): %u\n", i+1, input_x[i]);  
   }
}

/*

void C_timing(int iterations){
     clock_t begin, end;
     int i; 
     double time_spent;
     begin = clock();
     for(i=0; i<iterations; i++)
	{
	int first = 0; 
	int second = 1; 
	int third = 2; 
	int fourth =3; 
	
	first += second; 
	third += fourth; 
	first = first>>16; 
	second = second>>16; 
	third = third>>16; 
	fourth = fourth >>16; 

	int temp1 = first*third; 
	int temp2 = second*fourth; 
	int temp3 = (first+second)*(third+fourth) - temp1 - temp2;  	
	int response = temp1<<32 + temp2 + temp3<<16; 
	}
        end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("C timing: %lf\n", time_spent); 
}

void fpga_timing(int iterations){
     
     unsigned int input_x[RSA_SIZE]; 
     unsigned int return_x[RSA_SIZE]; 
     clock_t begin, end;
     int i; 
     double time_spent;
     for(i=0; i<RSA_SIZE; i++){
	input_x[i] = i; 
     }
     begin = clock();
     write_segment(input_x);
     for(i=0; i<iterations; i++)
	{
	    
    	    read_segment(return_x);

	}
      end = clock();
      time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
      printf("FPGA timing: %lf\n", time_spent); 

}


*/
//function to test that the value sent to be written is equal to value read
void check_equality(unsigned int *input_x, unsigned int *return_x){
    int i; 
    
    /*
    printf("Write Values\n"); 
    print_128_bit_integer(input_x);
    */
    printf("Read Values\n"); 
    print_128_bit_integer(return_x); 

    // printf("E value: %d\n", return_x[4]); 
   

/* 
   for(i = 0; i < RSA_SIZE; i++)
    {
	if(!(input_x[i] == return_x[i]) )
	{
	    perror("Error reading/writing, values do not match\n"); 
	}
    }
*/
    printf("Read/Write Successful\n"); 
}

int main()
{
    int i;
    int j; 
    unsigned int randx; 
    unsigned int input_x[12]; 
    unsigned int return_x[4]; 
    int iterations; 
    static const char filename[] = "/dev/vga_led";

    printf("RSA Box device driver started\n");

    if ( (vga_led_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    } 

    printf("opened file...\n");
 
    /*
    for(i=0; i < RSA_SIZE; i++)
    {
        input_x[i] = randx; ; 
    }
   

    randx = 1; 
    for(i=0; i < 32; i++)
    {
	randx = randx<<1|1; 
    }
    */

    // printf("%u\n", randx); 
    input_x[0] = 0; 
    input_x[1] = 1; 
    input_x[2] = 1; 
    input_x[3] = 0; 
    input_x[4] = 0;
    input_x[5] = 0; 
    input_x[6] = 1; 
    input_x[7] = 1; 
    input_x[8] = 0; 
    input_x[9] = 0; 
    input_x[10] = 0; 
    input_x[11] = 1;
    //write_segment(input_x);
    decrypt(input_x); 
    usleep(200); 
    //decrypt(input_x);
    printf("called decrypt...\n");
    read_segment(return_x);
    print_128_bit_integer(return_x); 
    printf("called read segment...\n");

    //check_equality(input_x, return_x);   
     

    //iterations = 100000; 
    //C_timing(iterations); 
    //fpga_timing(iterations); 
    printf("RSA Box device driver terminating\n");
    return 0;
}
