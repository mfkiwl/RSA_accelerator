#ifndef __EXTEUC_H__
#define __EXTEUC_H__

#include <stdint.h>     /* for unit32_t */

void err_sys(char *err);
void e_euclid(int32_t e, int32_t phi[4], int32_t *d);

#endif
