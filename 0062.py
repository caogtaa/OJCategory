def least_presentation(n):
    s = str(n)
    return ''.join(sorted(s))

mp = dict()

i = 1
while True:
    x = i * i * i
    key = least_presentation(x)

    if key not in mp:
        mp[key] = []
    
    mp[key].append(x)
    if len(mp[key]) == 5:
        ls = sorted(mp[key])
        print(ls[0])
        break

    i += 1
