def expMod(x, p, m):
    result = 1
    while p > 0:
        if p % 2 == 1:
            p -= 1
            result *= x
            result = result % m
        else:
            p /= 2
            x *= x
            x = x % m
    return result

print((28433 * expMod(2, 7830457, 10000000000) + 1) % 10000000000)
