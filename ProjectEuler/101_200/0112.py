def is_bouncy(x):
    inc = False
    dec = False
    s = str(x)
    for i in range(1, len(s)):
        if s[i] > s[i-1]:
            inc = True
        elif s[i] < s[i-1]:
            dec = True

    return inc and dec

bouncy_count = 0
n = 1
while True:
    if is_bouncy(n):
        bouncy_count += 1

    if bouncy_count * 100 >= n * 99:
        break

    n += 1

print(n)

# bruteforce
