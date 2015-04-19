INCLUDES = -I./gmp-6.0.0

CFLAGS = -g -Wall $(INCLUDES)
#LDLIBS = -lgmp

c-wrapper: c-wrapper.c primes.o
primes.o: primes.c primes.h

.PHONY: clean
clean:
	rm *.o
	rm c-wrapper
