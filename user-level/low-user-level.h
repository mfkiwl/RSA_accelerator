#ifndef __LOW_USER_LEVEL_H__
#define __LOW_USER_LEVEL_H__


// function declarations
void make_keys(unsigned int *p_and_q);
void encrypt(unsigned int *message_n);
void decrypt(unsigned int *cypher_n_d);
void read_segment(unsigned int *bit_output);
void print_128_bit_integer(unsigned int *input_x);


#endif
