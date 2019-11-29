

def gcd(a, b):
    while b > 0:
        tmp = a
        a = b
        b = tmp % b
    return a

def kthFraction(k):
    if k == 1:
        return 2
    if k % 3 == 0:
        return k // 3 * 2
    return 1

# N = 1
# D = 0
# for i in range(100, 0, -1):
#     tmp = N
#     N = D
#     D = tmp
#     N += D * kthFraction(i)
#     g = gcd(N, D)
#     N = N // g
#     D = D // g

N_1 = 1
D_1 = 0
N_2 = 0
D_2 = 1
for i in range(1, 101):
    N = kthFraction(i) * N_1 + N_2
    D = kthFraction(i) * D_1 + D_2

    N_2 = N_1
    N_1 = N
    D_2 = D_1
    D_1 = D

sum = 0
while N > 0:
    sum += N % 10
    N = N // 10

print(sum)

# In order to find convergent of e in D/N style
# Start from kth digit of continued fraction of e.
# Each time switch D/N and add with current digit

# Find convergent in a forward way 
# https://www.yuque.com/caomou/mgxqtg/melatw
