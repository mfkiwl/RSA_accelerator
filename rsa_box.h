#ifndef _RSA_BOX_H
#define _RSA_BOX_H

#include <linux/ioctl.h>

#define COORDINATES 2

typedef struct {
  unsigned char address;    /* 0, 1, .. , VGA_LED_DIGITS - 1 */
  int coord; /* LSB is segment a, MSB is decimal point */
} rsa_box_arg_t;

#define RSA_BOX_MAGIC 'q'

/* ioctls and their arguments */
#define RSA_BOX_WRITE_DIGIT _IOW(RSA_BOX_MAGIC, 1, rsa_box_arg_t *)
#define RSA_BOX_READ_DIGIT  _IOWR(RSA_BOX_MAGIC, 2, rsa_box_arg_t *)

#endif
