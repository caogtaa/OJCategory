
import math
from decimal import *

getcontext().prec = 102

def digitsSum(n):
    s = str(Decimal(n).sqrt())
    return sum([int(c) for c in s if c !='.']) - int(s[-1]) - int(s[-2])

result = 0
for i in range(2, 101):
    rt = int(math.sqrt(i))
    if rt * rt == i:
        continue

    result += digitsSum(i)

print(result)
