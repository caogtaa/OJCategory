def pow_mod(n, e, mod):
    result = 1
    while e > 0:
        if e % 2 == 1:
            result = (result * n) % mod
            e -= 1
        else:
            n = (n * n) % mod
            e /= 2

    return result

r = 0
mod = 10000000000
for i in range(1, 1001):
    r += pow_mod(i, i, mod)

print(r % mod)

# = 9110846700