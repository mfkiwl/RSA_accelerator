INCLUDES = -I./gmp-6.0.0

CFLAGS = -g -Wall $(INCLUDES)
#LDLIBS = -lgmp

low-user-level: low-user-level.c primes.o
primes.o: primes.c primes.h

.PHONY: clean
clean:
	rm *.o
	rm low-user-level
