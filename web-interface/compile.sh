#!/bin/bash

gcc -o TCPEchoServer TCPEchoServer.c DieWithError.c HandleTCPClient.c
gcc -o TCPEchoClient TCPEchoClient.c DieWithError.c
