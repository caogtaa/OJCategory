
import math

def diophanitineMinimalSolution(n):
    # num should not be a square number
    # see solution of 0064 for meanings of a,b,c
    a0 = int(math.sqrt(n))

    ai_1 = 0
    Pi_1 = 0
    Qi_1 = n

    ai = 0

    Ni_1 = 1
    Di_1 = 0
    Ni_2 = 0
    Di_2 = 1
    while True:
        # continued fraction generator
        Pi = ai_1 * Qi_1 - Pi_1
        Qi = int((n - Pi * Pi) / Qi_1)
        ai = int((a0 + Pi) / Qi)

        ai_1 = ai
        Pi_1 = Pi
        Qi_1 = Qi

        # convergent part
        Ni = ai * Ni_1 + Ni_2
        Di = ai * Di_1 + Di_2
        if Ni*Ni - n*Di*Di == 1:
            return Ni, Di

        Ni_2 = Ni_1
        Ni_1 = Ni
        Di_2 = Di_1
        Di_1 = Di

    # impossible
    return -1, -1

maxN = 0
result = 2
for i in range(2, 1001):
    # skip square number
    rt = int(math.sqrt(i))
    if rt * rt == i:
        continue

    N, D = diophanitineMinimalSolution(i)
    if N > maxN:
        maxN = N
        result = i

print(result)
