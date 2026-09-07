def is_die(pass_class, gender, age):
    if pass_class == 1: return True
    elif pass_class == 2:
        if gender == "м" and age > 9: return True
    elif pass_class == 3:
        if gender == "м" or (gender == "ж" and age > 24): return True

    return False

pass_class = int(input())
gender = input()
age = int(input())

print("умер" if is_die(pass_class, gender, age) else "выжил")