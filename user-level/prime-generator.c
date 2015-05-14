#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <inttypes.h>

#include <time.h>
#

/* GNU C seeder: measures total pseudo-cycles since device on */
unsigned long long rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}

/* modular exponentiation (base ^ exponent % mod) */
uint64_t modulo(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t x = 1; uint64_t y = base;

    while (exponent > 0) {
        if (exponent % 2 == 1) // odd exponents
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin Primality Test, iteration = accuracy
 */
int miller(uint64_t p, int iteration) {
    int i;

    if (p < 2) { return 0; }
    if (p != 2 && p % 2 == 0) { return 0; }

    uint64_t s = p - 1;
    while (s % 2 == 0) { s /= 2; }

    for (i = 0; i < iteration; i++) {

        uint64_t a = rand() % (p - 1) + 1, temp = s;
        uint64_t mod = modulo(a, temp, p);

        while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = (mod * mod) % p;
            mod = (mod * mod) % p;
            temp *= 2;
        }

        if (mod != p - 1 && temp % 2 == 0) { return 0; }
    }
    return 1;
}

uint64_t get_random(int tries) {

    uint64_t r30 = (uint64_t)rand();	// top 30
    uint64_t s30 = (uint64_t)rand(); 	// middle 30
    uint64_t t4  = rand() & 0xf; 		// bottom 4

    uint64_t res = (r30 << 34) + (s30 << 4) + t4;

    while(tries > 0) {
        res >>= 1;
        tries--;
    }

    return res;
}

uint64_t generate_prime() {

    int iteration = 5;
    int tries = 0; /* LINEAR BACKOFF */

    srand(rdtsc()); // randomize seed

    for(;;) {

        uint64_t num = 0x0LL; int j;
        for(j = 0; j <= tries && j <= 10; j++) {
            // printf("tries: %d, j: %d\n", tries, j);
            num = get_random(tries);

            if(miller(num, iteration) == 1) { return num; }
        }
        tries++;
    }
    return -1;
}


#define BIT_MASK 0xaaaaaaaa

void generate_prime_as_int32_t(int32_t *prime_64)
{
    uint64_t prime = generate_prime();
    prime_64[0] = (int32_t) (prime & BIT_MASK);
    prime_64[1] = (int32_t) (prime & (BIT_MASK << 32));
}

/*
int main() {
    printf("%" PRIu64 "\n", generate_prime());
    printf("%" PRIu64 "\n", generate_prime());

    return 0;
}
*/
