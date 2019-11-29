result = 0

p = 1
while True:
    if len(str(9 ** p)) != p:
        break

    for i in range(9, 0, -1):
        x = i ** p
        if len(str(x)) == p:
            result += 1
        else:
            break

    p += 1

print(result)

# if k^p has p digits, k should in [1, 9]. because 10^p = p+1, and all k > 10 has more digits
# then it's easy to enumerate them