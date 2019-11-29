def digitSum(n):
    result = 0
    while n > 0:
        result += n%10
        n //= 10
    
    return result

def digitSum2(n):
    result = 0
    ord0 = ord('0')
    s = str(n)
    for c in s:
        result += ord(c)-ord0

    return result


best = 0
for i in range(1, 100):
    for k in range(1, 100):
        best = max(best, digitSum2(i**k))

print(best)

# 论坛解法是通过理论缩小a,b的范围