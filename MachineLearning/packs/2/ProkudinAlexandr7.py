def encode_gen(gen):
    count = 0
    current_char = None
    result = ""
    for char in gen + " ":
        if current_char == char:
            count += 1
        else:
            if current_char is not None:
                result += current_char + str(count)
            count = 1
            current_char = char
    return result

gen = input()
print(encode_gen(gen))