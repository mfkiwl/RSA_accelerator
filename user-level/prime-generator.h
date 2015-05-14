#ifndef _PRIMEGENERATOR_H_
#define _PRIMEGENERATOR_H_

#include <stdint.h>
#include <inttypes.h>

/* GNU C seeder */
unsigned long long rdtsc();

/* modular exponentiation */
uint64_t modulo(uint64_t base, uint64_t exponent, uint64_t mod);

/* Miller-Rabin Primality Test */
int miller(uint64_t p, int iteration);

/* get random # */
uint64_t get_random(int tries);

/* generate prime */
uint64_t generate_prime();

#endif