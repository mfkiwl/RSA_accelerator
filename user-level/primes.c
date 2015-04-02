/*
 * Generating prime numbers for use in RSA.
 *
 * RSA Box - Embedded Systems (CSEE 4840) spring 2015 Columbia University
 */

#include <stdio.h>
#include <stdlib.h>
#include "primes.h"

void get_large_prime(int *other_prime)
{
    int i;
    
    for (i = 0; i < BIT_LENGTH; i++)
    {
        *other_prime |= (rand() % 2) << i; // bitwise OR a 1 or a 0 at index i
    }
}

int are_equal(int *prime_a, int *prime_b)
{
    int i;

    for (i = 0; i < BIT_LENGTH; i++)
    {
	if (prime_a[i] != prime_b[i])
	    return FALSE;
    }

    return TRUE;
}

void print_prime(int *num)
{
    int i;
    int mask = 1;

    for (i = 0; i < BIT_LENGTH; i++)
    {
        if (*num & mask) // if both values are 1
            printf("%d", 1);
        else // value is 0
	    printf("%d", 0);
        mask = mask << 1;
    }
    
    printf("\n");
}
