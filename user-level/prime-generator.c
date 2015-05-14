#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <inttypes.h>

#include <time.h>

static uint64_t primes[50] = {
    (((uint64_t) 1) << 63) - 25,
    (((uint64_t) 1) << 63) - 165,
    (((uint64_t) 1) << 63) - 259,
    (((uint64_t) 1) << 63) - 301,
    (((uint64_t) 1) << 63) - 375,
    (((uint64_t) 1) << 63) - 387,
    (((uint64_t) 1) << 63) - 391,
    (((uint64_t) 1) << 63) - 409,
    (((uint64_t) 1) << 63) - 457,
    (((uint64_t) 1) << 63) - 471,

    (((uint64_t) 1) << 62) - 57,
    (((uint64_t) 1) << 62) - 87,
    (((uint64_t) 1) << 62) - 117,
    (((uint64_t) 1) << 62) - 143,
    (((uint64_t) 1) << 62) - 153,
    (((uint64_t) 1) << 62) - 167,
    (((uint64_t) 1) << 62) - 171,
    (((uint64_t) 1) << 62) - 195,
    (((uint64_t) 1) << 62) - 203,
    (((uint64_t) 1) << 62) - 273,
    
    (((uint64_t) 1) << 61) - 1,
    (((uint64_t) 1) << 61) - 31,
    (((uint64_t) 1) << 61) - 45,
    (((uint64_t) 1) << 61) - 229,
    (((uint64_t) 1) << 61) - 259,
    (((uint64_t) 1) << 61) - 283,
    (((uint64_t) 1) << 61) - 339,
    (((uint64_t) 1) << 61) - 391,
    (((uint64_t) 1) << 61) - 403,
    (((uint64_t) 1) << 61) - 465,

    (((uint64_t) 1) << 60) - 93,
    (((uint64_t) 1) << 60) - 107,
    (((uint64_t) 1) << 60) - 173,
    (((uint64_t) 1) << 60) - 179,
    (((uint64_t) 1) << 60) - 257,
    (((uint64_t) 1) << 60) - 279,
    (((uint64_t) 1) << 60) - 369,
    (((uint64_t) 1) << 60) - 395,
    (((uint64_t) 1) << 60) - 399,
    (((uint64_t) 1) << 60) - 453,

    (((uint64_t) 1) << 59) - 55,
    (((uint64_t) 1) << 59) - 99,
    (((uint64_t) 1) << 59) - 225,
    (((uint64_t) 1) << 59) - 427,
    (((uint64_t) 1) << 59) - 517,
    (((uint64_t) 1) << 59) - 607,
    (((uint64_t) 1) << 59) - 649,
    (((uint64_t) 1) << 59) - 687,
    (((uint64_t) 1) << 59) - 861,
    (((uint64_t) 1) << 59) - 871
};

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
    printf("%" PRIu64 "\n",p); 

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
        if(res > (((uint64_t) 1) << 50))
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
        for(j = 0; j <= tries && j <= 1000; j++) {
            // printf("tries: %d, j: %d\n", tries, j);
            num = get_random(tries);

            if(miller(num, iteration) == 1) { return num; }
        }
        tries++;
    }
    return -1;
}

uint64_t pick_prime() {
    int i;
    srand(rdtsc());
    i = rand() % 50;
    return primes[i];
}



#define BIT_MASK 0xffffffff

void generate_prime_as_int32_t(int32_t *prime_64)
{
    uint64_t prime = pick_prime();
    printf("%llX\n", prime);
    prime_64[0] = (int32_t) (prime % BIT_MASK);
    prime_64[1] = (int32_t) (prime >> 32);
}

int main() {
//    printf("%" PRIu64 "\n", generate_prime());
//    printf("%" PRIu64 "\n", generate_prime());
    int32_t prime_64[2];
    generate_prime_as_int32_t(prime_64);
    printf("%X %X", prime_64[0], prime_64[1]);

    return 0;
}
