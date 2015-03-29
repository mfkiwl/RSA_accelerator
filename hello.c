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
#include "rsa_box.h"

#define X_VAL 	0
#define Y_VAL 	1
#define X_MAX 	640
#define Y_MAX 	480
#define RADIUS 	40
#define SPEED 	6000

int rsab_fd;

/* Read and print the segment values */
void print_segment_info() 
{
  rsa_box_arg_t vla;
  int i;

  for (i = 0 ; i < REGISTERS; i++) {
      vla.address = i;
      if (ioctl(rsab_fd, RSA_BOX_READ_DIGIT, &vla)) {
           perror("ioctl(RSA_BOX_READ_DIGIT) failed");
           return;
       }
       printf("Decimal: %d\n", vla.coord);
    }
}

void write_segment(int axis, int coord)
{
    rsa_box_arg_t vla;

    vla.address = axis;
    vla.coord = coord;
    
    if (ioctl(rsab_fd, RSA_BOX_WRITE_DIGIT, &vla)) {
      perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
      return;
    }

}

int main()
{
    rsa_box_arg_t vla;
    static const char filename[] = "/dev/rsa_box"; // must match module name in rsa_box.c

    printf("RSA Box device driver started\n");

    if ( (rsab_fd = open(filename, O_RDWR)) == -1) {
        fprintf(stderr, "could not open %s\n", filename);
        return -1;
    }
  
    // initalize location of ball
    int coords[2] = {RADIUS + 1, RADIUS + 10};
    write_segment(X_VAL, coords[X_VAL]);
    write_segment(Y_VAL, coords[Y_VAL]); 
    usleep(SPEED);
 
    int x_dir = 1;
    int y_dir = 1;
    
    for(;;)
    {
        // change x-value if out of screen
        if (coords[X_VAL] >=  X_MAX - RADIUS ||
		coords[X_VAL] <= RADIUS)
            x_dir *= -1; 
        coords[X_VAL] += x_dir; 
    
        write_segment(X_VAL, coords[X_VAL]);

        usleep(SPEED);

        // change y-value if out of screen
        if (coords[Y_VAL] >= Y_MAX - RADIUS || 
		coords[Y_VAL] <= RADIUS)
	    y_dir *= -1;
        coords[Y_VAL] += y_dir;

        write_segment(Y_VAL, coords[Y_VAL]);

        usleep(SPEED);
    }
 
    printf("RSA Box device driver terminating\n");
  
    return 0;
}
