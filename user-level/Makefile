CFLAGS = -g -Wall $(INCLUDES)

default: interface-test wrapper-test

interface-test: c-interface.o c-wrapper.o

wrapper-test: c-wrapper.o

c-interface.o: c-interface.h c-wrapper.h
c-wrapper.o: c-wrapper.h 

.PHONY: clean
clean:
	rm -f *.o
	rm -f interface-test
	rm -f wrapper-test
