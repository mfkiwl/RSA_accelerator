import socket

import ctypes
lib = ctypes.cdll.LoadLibrary("libtest.so")
lib.stuff.restype = ctypes.c_double

ret = lib.stuff()
print ret

TCP_IP      = '127.0.0.1'
TCP_PORT    = 9000
BF_SIZE     = 4096

'''socket'''
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
conn, addr = s.accept() 

while True: 
    
    # RECEIVE
    data = conn.recv(BF_SIZE)
    print "<server>: ", data
    
    # SEND 
    msg = raw_input('>> ')
    conn.send(msg)

conn.close()