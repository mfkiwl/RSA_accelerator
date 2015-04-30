#ifndef _RSA_BOX_H
#define _RSA_BOX_H

#include <linux/ioctl.h>
#include <linux/types.h>     /* for unit32_t */

typedef struct {
  int digit;
  uint32_t segments; 
} rsa_box_arg_t;

#define RSA_BOX_MAGIC 'q'

/* ioctls and their arguments */
#define RSA_BOX_WRITE_DIGIT _IOW(RSA_BOX_MAGIC, 1, rsa_box_arg_t *)
#define RSA_BOX_READ_DIGIT  _IOWR(RSA_BOX_MAGIC, 2, rsa_box_arg_t *)

#endif
