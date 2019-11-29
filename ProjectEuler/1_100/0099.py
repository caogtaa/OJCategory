import math

def toInt(t):
    return (int(t[0]), int(t[1]))

def cmp1(n1, e1, n2, e2):
    while True:
        if n1 <= n2 and e1 <= e2:
            return -1

        if n1 >= n2 and e1 >= e2:
            return 1

        if n1 <= n2:    # then e1 >= e2
            e1 = e1-e2
            n2 = n2/n1
            # return cmp(n1, e1-e2, n2/n1, e2)
        else:
            n1 = n1/n2
            e2 = e2-e1
            # return cmp(n1/n2, e1, n2, e2-e1)

def cmp2(n1, e1, n2, e2):
    r1 = e1*math.log(n1)
    r2 = e2*math.log(n2)
    if r1 <= r2:
        return -1
    return 1

with open("0099_input.txt", "r") as input:
    content = input.read()

ls = list(map(toInt, [line.split(",") for line in content.split("\n")]))
result = 0
for x in range(1, len(ls)):
    if cmp2(ls[result][0], ls[result][1], ls[x][0], ls[x][1]) < 0:
        result = x

print(result+1)

# solution 1:
# divide n1^e1, n2^e2 by min(n1,n2)^min(e1,e2), until the number is comparable (number and exponential are both little/large than another)
# solution 2 (from forum and simpler):
# compare log(n1^e1) and log(n1^e2), which is e1*log(n1) and e2*log(n2)