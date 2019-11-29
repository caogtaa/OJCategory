import math

base = ord('A') - 1
def pos(letter):
    return ord(letter) - base

def isTriangleNumber(n):
    n *= 2
    q = int(math.sqrt(n))
    return q*(q+1) == n

with open("0042_input.txt", "r") as input:
    content = input.read()
    ls = content.split(",")
    ls = [s[1:][:-1] for s in ls]               # remove quotes
    ls = [sum(list(map(pos, s))) for s in ls]   # to word value
    count = sum(list(map(isTriangleNumber, ls)))
    print(count)

# judge triangle number directly