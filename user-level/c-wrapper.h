#ifndef __C_WRAPPER_H__
#define __C_WRAPPER_H__

// Start session.
// Use user-specified private key, return public key.
int32_t *RSA_init(int32_t *p, int32_t *q); 

// Start session. 
// Use auto-generated private key, return public key.
int32_t *RSA_init();

// Save remote public keys to register.
void set_remote_keys(int32_t *e_other, int32_t *n_other);

// Encryption and decryption using values stored in registers.
// Raise exception and set errno if relevant register not set.
char *encrypt(char *msg);
char *decrypt(char *cypher);

// End session and clear registers.
void RSA_end();

#endif
