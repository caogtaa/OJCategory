X = 1
for i in range(2, 101):
    X *= i

S = str(X)
ls = map(int, S)
print(sum(ls))
