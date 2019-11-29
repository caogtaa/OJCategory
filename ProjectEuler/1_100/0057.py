result = 0
a,b=3,2
for i in range(2, 1001):
    a, b = a+b*2, a+b
    if len(str(a)) > len(str(b)):
        result += 1

print(result)

# 论坛有分析式解法
# https://projecteuler.net/best_posts=057