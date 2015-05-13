import sys

def inverse(e, phi_n):
    '''Extended Euclidean Algorithm'''
    e_cast = int(e)
    phi_cast = int(phi_n)

    d =	0
    new_d = 1
    r =	phi_cast
    new_r =	e_cast
	
    while new_r is not 0:
        quotient = r / new_r
        (d, new_d) = (new_d, d - quotient * new_d) 
        (r, new_r) = (new_r, r - quotient * new_r)
		
    if r > 1:
		return -1 # error
    
    if d < 0:
        d = d + phi_cast
    
    return d

def print_test(test_no, phi, e, d):
    '''verifies the computation of Extended Euclid's'''
    # to test... print_test(1, 15, 2, 8) or print_test(2, 21, 2, 11)

    print "[test %d]: phi_n: %d, e: %d" % (test_no, phi, e)
    print " - desired: %d" % d
    print " - result: %d" % (inverse(e, phi)) 

def main():
    d = inverse(sys.argv[1], sys.argv[2])
    print str(d), "\0"
	
main()