# pip install num2words
import num2words

def count_letter(s):
    return len([c for c in s if c != ' ' and c != '-'])

result = 0
for i in range(1, 1001):
    result += count_letter(num2words.num2words(i))

print(result)
# 21124