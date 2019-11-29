import math

with open('0067_input.txt', 'r') as input:
    content = input.read()
    rows = [r for r in content.split('\n') if r]
    mat = [list(map(int, r.split(' '))) for r in rows]

F = mat[99].copy()
for i in range(98, -1, -1):
    F2 = mat[i].copy()
    for j in range(0, i+1):
        F2[j] += max(F[j], F[j+1])

    F = F2

print(F[0])