import math
with open("0081_input.txt", "r") as input:
    content = input.read()
    lines = [l for l in content.split('\n') if l]
    mat = [list(map(int, line.split(','))) for line in lines]

F = [0] * 80
F[0] = mat[0][0]
for c in range(1, 80):
    F[c] = F[c-1] + mat[0][c]

for r in range(1, 80):
    F[0] += mat[r][0]
    for c in range(1, 80):
        F[c] = mat[r][c] + min(F[c], F[c-1])

print(F[79])

# simple DP
# F(r, c) = mat(r,c) + min(F(r-1, c), F(r, c-1))
# compress the space into 1-dimension array
