#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

/*
 * before writing any data, specify which instruction will be used:
 * write INSTRUCTION with desired action (e.g. MAKE_KEY, ENCRYPT, etc)
 */
#define INSTRUCTION             0
#define RESET                   1
#define STORE_PUBLIC_KEY_1      2 // n
#define STORE_PUBLIC_KEY_2      3 // e
#define STORE_PRIVATE_KEY_1     4 // p
#define STORE_PRIVATE_KEY_2     5 // q
#define DECRYPT_BITS            6 // DECRYPT_3
#define ENCRYPT_BITS            7
#define READ_PUBLIC_KEY_1       8 // n
#define READ_PUBLIC_KEY_2       9 // e
#define STORE_MESSAGE           10 // m
#define STORE_MESSAGE2          11 // m
#define STORE_D                 12 // m
#define MAKE_OUR_N              13 // carry out p * q op
#define READ_OUR_N              14 // read back (p * q) 

void log_instruction(int opcode);

#endif
