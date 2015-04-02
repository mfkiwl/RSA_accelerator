#! /bin/bash
rmmod rsa_box
make
insmod rsa_box.ko
clear
./hello
