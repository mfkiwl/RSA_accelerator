import sys

def extended_euclids(e, phi):

    d =	0
    updated_d = 1
    r =	phi
    updated_r = e
    
    while updated_r != 0:
        quotient = r / updated_r
        (d, updated_d) = (updated_d, d - quotient * updated_d) 
        (r, updated_r) = (updated_r, r - quotient * updated_r)
		
    if r > 1:
		return -1 # error
    
    if d < 0:
        d = d + phi
    
    return d

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

    d = extended_euclids(e, phi)
    # print str(bin(d)) + " " + str(d), "\0"

    d_list = format(d, '#0130b')
    temp = int(str(d_list[2:34]), 2) # topmost 32 bits
    temp2 = int(str(d_list[34:66]), 2) 
    temp3 = int(str(d_list[66:98]), 2)
    temp4 = int(str(d_list[98:130]), 2) 

    ret = str(temp) + " " + str(temp2) + " " + str(temp3) + " " + str(temp4)
    # print str(d_list)
    print ret
main()
