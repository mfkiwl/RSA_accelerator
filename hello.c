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

#define X_VAL 	0
#define Y_VAL 	1
#define X_MAX 	640
#define Y_MAX 	480
#define RADIUS 	40
#define SPEED 	6000

int vga_fd;

/* Read and print the segment values */
void print_segment_info() 
{
  vga_led_arg_t vla;
  int i;

  for (i = 0 ; i < COORDINATES; i++) {
      vla.address = i;
      if (ioctl(vga_fd, VGA_LED_READ_DIGIT, &vla)) {
           perror("ioctl(VGA_LED_READ_DIGIT) failed");
           return;
       }
       printf("Decimal: %d\n", vla.coord);
    }
}

void write_segment(int axis, int coord)
{
    vga_led_arg_t vla;

    vla.address = axis;
    vla.coord = coord;
    
    if (ioctl(vga_fd, VGA_LED_WRITE_DIGIT, &vla)) {
      perror("ioctl(VGA_LED_WRITE_DIGIT) failed");
      return;
    }

}

int main()
{
  vga_led_arg_t vla;
  static const char filename[] = "/dev/vga_led";

  printf("VGA LED Userspace program started\n");

  if ( (vga_fd = open(filename, O_RDWR)) == -1) {
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
    
    // print_segment_info(); // just for testing
  }
 
  printf("VGA LED Userspace program terminating\n");
  return 0;
}
