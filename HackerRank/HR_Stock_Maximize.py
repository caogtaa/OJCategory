T = int(raw_input())
for _ in xrange(T):
    N = int(raw_input())
    ls = map(int, raw_input().split())
    mx = ls[N-1]
    total = 0
    for i in xrange(N-1, -1, -1):
        if  ls[i] < mx:
            total += mx - ls[i]
        else:
            mx = ls[i]
    print total