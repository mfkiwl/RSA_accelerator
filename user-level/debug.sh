#!/bin/bash
gcc -c -fPIC test.c -o test.o
gcc test.o -shared -o libtest.so