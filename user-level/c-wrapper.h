#ifndef __C_WRAPPER_H__
#define __C_WRAPPER_H__

// function declarations
void store_private_keys(int32_t *p_and_q);
void intwise_encrypt(int32_t *message_n);
void intwise_decrypt(int32_t *cypher_n_d);
void set_fd();
void print_128_bit_integer(int32_t *input_x);
void read_segment(int32_t *bit_output);

#endif
