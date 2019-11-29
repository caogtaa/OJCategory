
F = [[-1] * 101 for i in range(0, 101)]

# split k, with max number be x
def func(x, k):
    if k == 0:
        return 1

    if x <= 0:
        return 0

    if F[x][k] != -1:
        return F[x][k]

    F[x][k] = func(min(x, k-x), k-x) + func(x-1, k)
    return F[x][k]

print(func(99, 100))

# simple DP
# use Euler's generation function can save some space but have the same time complexity which is O(N^2)
# http://mathworld.wolfram.com/PartitionFunctionP.html (item 11)