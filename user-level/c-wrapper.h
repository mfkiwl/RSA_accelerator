#ifndef __C_WRAPPER_H__
#define __C_WRAPPER_H__

// function declarations
void store_private_keys(uint32_t *p_and_q);
void intwise_encrypt(uint32_t *message_n);
void intwise_decrypt(uint32_t *cypher_n_d);
void set_fd();
void print_128_bit_integer(uint32_t *input_x);
void read_segment(uint32_t *bit_output);

#endif
