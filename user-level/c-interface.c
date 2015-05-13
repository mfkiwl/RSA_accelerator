#include <stdint.h>             /* for unit32_t */
#include <stdlib.h>             /* for malloc */
#include <stdio.h>              /* for printf */
#include <string.h>             /* for memcpy */
#include "c-interface.h"
#include "c-wrapper.h"          /* for all functions making syscalls */

#define TRUE    1
#define FALSE   0

void set_private_keys(int32_t *p, int32_t *q)
{
    store_keys(PRIVATE, p, q);
}

void set_public_keys(int32_t *e, int32_t *n)
{
    store_keys(PUBLIC, e, n);
}

void read_public_keys(int32_t *e, int32_t *n)
{
    __read_public_keys(e, n);
}

/*
 * encrypt message and return as 32-bit int array.
 */
void encrypt(char *msg_buf, int32_t *cypher_buf, int len)
{
    int i;
    int32_t curr_val;

    for (i = 0; i < len; i++) 
    {
        memcpy(&curr_val, msg_buf + i, sizeof(int32_t));
        send_int_encrypt_decrypt(ENCRYPT_SEND, &curr_val);
        read_output(&curr_val + i);
        memcpy(cypher_buf + i, &curr_val, sizeof(char));
    }
}

/* 
 * decrypt cypher and return message as char array.
 */
void decrypt(int32_t *cypher_buf, char *msg_buf, int len)
{
    int i;
    int32_t curr_val;

    for (i = 0; i < len; i++) 
    {
        memcpy(&curr_val, cypher_buf + i, sizeof(int32_t));
        send_int_encrypt_decrypt(DECRYPT_SEND, &curr_val);
        read_output(&curr_val);
        memcpy(msg_buf + i, &curr_val, sizeof(char));
    }
}
