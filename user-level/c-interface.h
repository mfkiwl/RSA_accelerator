#ifndef __C_INTERFACE_H__
#define __C_INTERFACE_H__

#include <stdint.h>     /* for unit32_t */

// Start session.
// Use user-specified private key, return public key.
void RSA_init(int32_t *p, int32_t *q); 

// Start session. 
// Use auto-generated private key, return public key.
//void *RSA_init();

// Save remote public keys to register.
void set_remote_keys(int32_t *e_other, int32_t *n_other);

// Encryption and decryption using values stored in registers.
// Raise exception and set errno if relevant register not set.
void encrypt(char *msg, char *cypher_buf, int len);
void decrypt(char *cypher, char *msg_buf, int len);

// End session and clear registers.
void RSA_end();

#endif
