# 1
# 2 2 2 2
# 4 4 4 4

result = 1
base = 1
for i in range(3, 1001+1, 2):
    delta = i-1
    for k in range(4):
        base += delta
        result += base

print(result)
