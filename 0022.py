def score(s):
    L = list(map(ord, s))
    L = [x - ord('A') + 1 for x in L]
    return sum(L)

with open("1022_input.txt", "r") as input:
    content = input.read()
    ls = content.split(',')
    ls = [s[1:][:-1] for s in ls]
    ls.sort()

    result = 0
    for i in range(0, len(ls)):
        result += (i+1) * score(ls[i])

    print(result)

# = 871198282