with open("0098_input.txt", "r") as input:
    content = input.read()

ls = content.split(",")
arr = [line[:-1][1:] for line in ls]
arr.sort(key=lambda x: len(x), reverse=True)

min_counter = dict()
arr_sorted = [''.join(sorted(word)) for word in arr]
for word in arr_sorted:
    if word in min_counter:
        min_counter[word] += 1
    else:
        min_counter[word] = 1

valid_input = dict()
for word in arr:
    s_word = ''.join(sorted(word))
    if min_counter[s_word] > 1:
        if s_word in valid_input:
            valid_input[s_word].append(word)
        else:
            valid_input[s_word] = [word]

for word in valid_input:
    ls = valid_input[word]
    if len(ls) == 2:
        print("{\"%s\", \"%s\"}," % (ls[0], ls[1]))
    elif len(ls) == 3:
        print("{\"%s\", \"%s\", \"%s\"}," % (ls[0], ls[1], ls[2]))
    else:
        raise Exception("not handled")

# preprocess finished, see 0098.cpp for further process