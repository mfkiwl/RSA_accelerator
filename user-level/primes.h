#ifndef __PRIMES_H__
#define __PRIMES_H__

#define BIT_LENGTH 	64 // 64 bit primes yield 128 bit keys
#define TRUE 		1
#define FALSE 		0

// returns a large prime number. If other_prime is not null,
// we ensure that the number returned does not equal other_prime.
void get_large_prime(int *other_prime);

// returns TRUE if all bits are equal; FALSE otherwise
int are_equal(int *prime_a, int *prime_b);

// outputs the bit string to STDOUT
void print_prime(int *num);

#endif
