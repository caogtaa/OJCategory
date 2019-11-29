def pow5(n):
    return int(n) ** 5

ls = []
for i in range(2, 1000000+1):
    digit_sum = sum(list(map(pow5, str(i))))
    if digit_sum == i:
        ls.append(i)

result = sum(ls)
print(result)

# 本题采用暴力法，需要确定问题的上界
# 9^5 = 59049
# 6 * 9^5 = 354294
# 以此可以得出上界是354294，此后的digit_sum增长速度会远低于数字增长速度，并且永远无法追上

# ls = [4150, 4151, 54748, 92727, 93084, 194979]