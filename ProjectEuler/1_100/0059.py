def decryptWithK(s, k):
    # a = map(lambda c:chr(k^c), s)
    # print(''.join(list(a)))

    marks = {':', '/', '\\', ' ', ',', '.', '\'', '\"', '?', '-', ')', '(', '+', '-', '~', '%', '!', '=', '|', '[', ']', '{', '}', '\n', ';'}
    for c in s:
        if chr(k^c).isalnum() or chr(k^c) in marks:
            continue
        
        return False

    return True

def tryDecrypt(s):
    for k in range(ord('a'), ord('z')+1):
        if decryptWithK(s, k):
            return k

    return 0    # decrypt fail

def decryptWithPwd(nums, pwd):
    k = 0
    for i in range(0, len(nums)):
        nums[i] = nums[i]^pwd[k]
        k = (k+1) % 3

with open("0059_input.txt", "r") as input:
    content = input.read()
    nums = list(map(int, content.split(",")))

s1 = set()
s2 = set()
s3 = set()

for i in range(0, len(nums), 3):
    s1.add(nums[i])
for i in range(1, len(nums), 3):
    s2.add(nums[i])
for i in range(2, len(nums), 3):
    s3.add(nums[i])

pwd = [tryDecrypt(s1), tryDecrypt(s2), tryDecrypt(s3)]
decryptWithPwd(nums, pwd)

print(''.join(list(map(chr, nums))))
print(sum(nums))

# pwd = 'exp'