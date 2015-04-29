#include <stdint.h>     /* for unit32_t */
#include <stdlib.h>             /* for malloc */
#include <stdio.h>              /* for printf */
#include "c-interface.h"
#include "c-wrapper.h"          /* for all functions making syscalls */

static int is_initialized = 0;
static int is_set_remote_keys = 0;

void RSA_init(uint32_t *p, uint32_t *q)
{
    uint32_t p_and_q[4];

    if (is_initialized)
        perror("Must quit initialized RSA session.");
    
    p_and_q[0] = *(p + 0);
    p_and_q[1] = *(p + 1);
    p_and_q[2] = *(q + 0);
    p_and_q[3] = *(q + 1);

    store_private_keys(p_and_q);
    is_initialized = 1;
    set_fd();
}

/*
int32_t *RSA_init()
{
    // generate keys
    // RSA_init(p, q);
}
*/

void set_remote_keys(uint32_t *e_other, uint32_t *n_other)
{
    is_set_remote_keys = 1;
}

void encrypt(char *msg, char *cypher_buf, int len)
{
    int i;
    
    if (!is_initialized)
        perror("Must initialize RSA session.");

    for (i = 0; i < len; i++) {
        cypher_buf[i] = 'a'; 
    }
}

void decrypt(char *cypher, char *msg_buf, int len)
{
    if (!is_initialized)
        perror("Must initialize RSA session.");
    if (!is_set_remote_keys)
        perror("Must have remote keys set.");
}

// fill private key registers on hardware with 0s
void RSA_end()
{
    if (!is_initialized)
        perror("Must initialize RSA session.");
    
    uint32_t p_and_q[4] = {0, 0, 0, 0};
    store_private_keys(p_and_q);
    is_initialized = 0;
}
