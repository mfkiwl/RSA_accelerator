a = 0b0001001110
b = 0b0011011010
n = 0b1110110101
R = 0b0

for i in range(5):
    R = 4 * R + ((a & (0b11 << (8 - 2 * i))) >> (8 - 2 * i)) * b
    if R >= n:
        R -= n
    if R >= n:
        R -= n
    if R >= n:
        R -= n
    if R >= n:
        R -= n



print R
print a * b % n
