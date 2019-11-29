import math
with open("0082_input.txt", "r") as input:
    content = input.read()
    lines = [l for l in content.split('\n') if l]
    mat = [list(map(int, line.split(','))) for line in lines]

F = [[[-1] * 80 for i in range(0, 80)] for k in range(0, 4)]

def Func(d, r, c):
    if c == 79:
        return mat[r][79]

    if F[d][r][c] != -1:
        return F[d][r][c]

    # try go right
    result = mat[r][c] + Func(1, r, c+1)
    if d != 2 and r > 0:
        # previous is not down, try go up
        result = min(result, mat[r][c] + Func(0, r-1, c))
    
    if d != 0 and r < 79:
        # previous is not up, try go down
        result = min(result, mat[r][c] + Func(2, r+1, c))

    F[d][r][c] = result
    return result

result = -1
for r in range(0, 80):
    tmp = Func(1, r, 0)
    if result == -1 or tmp < result:
        result = tmp

print(result)

# simple DP
# F[4][80][80]
# F[d][r][c] means from mat[r][c] to right side, previous direction is d (0:up, 1:right, 2:down)