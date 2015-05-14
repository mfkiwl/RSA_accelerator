import socket

TCP_IP 		= '127.0.0.1'
TCP_PORT 	= 9000
BF_SIZE 	= 4096

'''socket'''
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

while True:
	
	# SEND 
	msg = raw_input('>> ')
	s.send(msg)

	# RECEIVE
	resp = s.recv(BF_SIZE)
	print "<server>: ", str(resp)

s.close()