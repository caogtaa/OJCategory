def r_max(a):
    result = 2  # (x^0 + y^0) mod a^2
    m = a*a
    x,y = a-1,a+1
    rx,ry = x,y
    while True:
        result = max(result, (rx+ry) % m)
        rx = (rx * x) % m
        ry = (ry * y) % m
        if rx == 1 and ry == 1:
            break
    return result

result = 0
for a in range(3, 1000+1):
    result += r_max(a)

print(result)

# https://projecteuler.net/problem=120
# 暴力
# 通过观察发现(a-1)^n % a^2 和(a+1)^n % a^2的周期最大是2a，在可计算范围内

# 数论分析
# https://projecteuler.net/best_posts=120
