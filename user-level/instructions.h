#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

/*
 * before writing any data, specify which instruction will be used:
 * write INSTRUCTION with desired action (e.g. MAKE_KEY, ENCRYPT, etc)
 */
#define INSTRUCTION             0
#define RESET                   1
#define STORE_PUBLIC_KEYS       2
#define ENCRYPT_BITS            10
#define STORE_PRIVATE_KEY_1     3 // DECRYPT_1
#define STORE_PRIVATE_KEY_2     7 // DECRYPT_2
#define DECRYPT_BITS            11 // DECRYPT_3

#endif
