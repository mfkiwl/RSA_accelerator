#include <stdlib.h>
#include "c-interface.h"

int main(int argc, char **argv)
{
    int32_t p[2];
    int32_t q[2];

    p[0] = 2;
    p[1] = 3;
    q[0] = 39;
    q[1] = 5000;

    set_private_keys(p, q);

    return 0;
}
