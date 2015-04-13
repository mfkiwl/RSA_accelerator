def blakely(a,b,n, k_bits):
    r = long(0)
    count = long(k_bits-1)
     
    for i in range(k_bits):
        r = ( (r<<1) + ( ( ((1<<count) & a)>>count )* b))
        if r>=n:
            r -= n
        if r>=n:
            r -= n
        count-=1 
    return r


a = long(5)
print "A: %s A bit length: %s"% (str(a), str(a.bit_length()))

b = long(4)
print "B: %s B bit length: %s" %(str(b), str(b.bit_length()))

n = long(7)
print "n: %s n bit length: %s" %(str(n), str(n.bit_length()))

k_bits = 128#a.bit_length()
print "Blakely: " + str(blakely(a,b,n,k_bits))
print "Python mod: " + str(((a*b)%n))
