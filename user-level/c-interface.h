#ifndef __C_INTERFACE_H__
#define __C_INTERFACE_H__

#include <stdint.h>     /* for unit32_t */

/*
 * Set private keys to allow encrypting. Set public keys
 * to allow decrypting.
 */
void set_private_keys(int32_t *p, int32_t *q);
void set_public_keys(int32_t *e, int32_t *n);

// Encryption and decryption using values stored in registers.
// Raise exception and set errno if relevant register not set.
void encrypt(char *msg_buf, int32_t *cypher_buf, int len);
void decrypt(int32_t *cypher_buf, char *msg_buf, int len);

#endif
