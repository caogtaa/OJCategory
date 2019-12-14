from fractions import Fraction

F = [[Fraction(-1,1) for k in range(0, 16)] for i in range(0, 16)]

def func(n, k):
    if k > n or k < 0:
        return Fraction(0, 1)
    if n == 1:
        return Fraction(1, 2)
    
    if F[n][k] != -1:
        return F[n][k]
    
    F[n][k] = 1/(n+1) * func(n-1, k-1) + n/(n+1) * func(n-1, k)
    return F[n][k]

n = 15
result = Fraction(0, 1)

# sum{func(15,8), func(15,9), ... (func(15,15))}
for k in range(n//2 + 1, n+1):
    result += func(n, k)

print(1/result)

# https://projecteuler.net/problem=111
# 动态规划
# 设F[n][k]表示取n次能够取到k个蓝球的概率
# 第n次取的时候，袋子里共有n+1个求，取出蓝球的概率是1/(n+1)
# 所以F[n][k] = 1/(n+1) * F[n-1][k-1] + n/(n+1) * F[n-1][k]
# 等号后第一项表示：第n次取出的是蓝球，在前n-1次再取k-1个
# 等号后第二项表示：第n次取出的是红球，在前n-1次中取k个蓝球

# 数论分析
# 拿到递推式了之后，可以用母函数求出通项公式
