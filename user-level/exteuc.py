import sys

def inverse(e, phi):
    '''Extended Euclidean Algorithm'''

    d =	0
    new_d = 1
    r =	phi
    new_r =	e
	
    while new_r is not 0:
        quotient = r / new_r
        (d, new_d) = (new_d, d - quotient * new_d) 
        (r, new_r) = (new_r, r - quotient * new_r)
		
    if r > 1:
		return -1 # error
    
    if d < 0:
        d = d + phi
    
    return d

def print_test(test_no, phi, e, d):
    '''verifies the computation of Extended Euclid's'''
    # to test... print_test(1, 15, 2, 8) or print_test(2, 21, 2, 11)

    print "[test %d]: phi: %d, e: %d" % (test_no, phi, e)
    print " - desired: %d" % d
    print " - result: %d" % (inverse(e, phi)) 

def main():

    '''
        argv[1] -> e
        argv[2] to argv[4] -> phi
    '''

    e = int(sys.argv[1])

    phi = int(sys.argv[5])
    
    add1 = int(sys.argv[4]) << 32
    add2 = int(sys.argv[3]) << 64
    add3 = int(sys.argv[2]) << 96
    
    phi += add1
    phi += add2
    phi += add3

    # test values: e = 2; phi = 2**33 + 5

    d = inverse(e, phi)
    print str(bin(d)) + " " + str(d), "\0"
	
main()