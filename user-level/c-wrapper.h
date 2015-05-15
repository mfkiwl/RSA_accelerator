#ifndef __C_WRAPPER_H__
#define __C_WRAPPER_H__

#define PRIVATE                 0
#define PUBLIC                  1
#define DECRYPT_SEND            0
#define ENCRYPT_SEND            1 

// comment or uncommon line 10 to add/remove debug print statements
#define PRINTVERBOSE            1

/* store private keys, getting back public key */
void key_swap(int32_t *p, int32_t *q, int32_t *our_n);

/* encrypt or decrypt */
void send_int_encrypt_decrypt(int action, int32_t *message_n, int32_t *output);

/* read back value encrypted/decrypted */
void __read_encryption(int32_t *encryption);
void __read_decryption(int32_t *decryption); 
void read_our_N(int32_t *n);

/* helper functions */
void set_fd();
void print_128_bit_integer(int32_t *input_x);

#endif
