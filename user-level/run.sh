#! /bin/bash
rmmod rsa_box
make "wrapper-test"
insmod ../rsa_box.ko
clear
./wrapper-test
