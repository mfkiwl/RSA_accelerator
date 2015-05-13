def inverse(e, phi_n):
    '''Extended Euclidean Algorithm'''
    d =	0
    new_d = 1
    r =	phi_n
    new_r =	e
	
    while new_r is not 0:
        quotient = r / new_r
        (d, new_d) = (new_d, d - quotient * new_d) 
        (r, new_r) = (new_r, r - quotient * new_r)
		
    if r > 1:
		return -1 # error
    
    if d < 0:
        d = d + phi_n
    
    return d

def print_test(test_no, phi, e, d):
    print "[test %d]: phi_n: %d, e: %d" % (test_no, phi, e)
    print " - desired: %d" % d
    print " - result: %d" % (inverse(e, phi)) 

def main():
    print_test(1, 15, 2, 8)
    print_test(2, 21, 2, 11)
	
main()