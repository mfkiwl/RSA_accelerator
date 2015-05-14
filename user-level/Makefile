CFLAGS = -g -Wall $(INCLUDES)

default: interface-test wrapper-test
debug: prime-generator exteuc

interface-test: c-interface.o c-wrapper.o instructions.o
wrapper-test: c-wrapper.o instructions.o

# prime-generator & exteuc used for testing
prime-generator: prime-generator.o
exteuc: exteuc.o

c-interface.o: c-interface.h c-wrapper.h instructions.h
c-wrapper.o: c-wrapper.h 
instructions.o: instructions.h
prime-generator.o: prime-generator.c prime-generator.h
exteuc.o: exteuc.c exteuc.h

.PHONY: clean
clean:
	rm -f *.o *~ 
	rm -f interface-test
	rm -f wrapper-test
	rm -f prime-generator
	rm -f exteuc
