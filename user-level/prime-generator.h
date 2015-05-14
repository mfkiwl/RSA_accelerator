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
uint64_t get_random(int tries);
uint64_t generate_prime();
void generate_prime_as_int32_t(int32_t *prime_64);

#endif
