#include <stdlib.h>
#include "c-interface.h"

int main(int argc, char **argv)
{
    uint32_t p[2];
    uint32_t q[2];

    p[0] = 2;
    p[1] = 3;
    q[0] = 39;
    q[1] = 5000;

    RSA_init(p, q);

    return 0;
}
