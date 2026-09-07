n_1 = float(input())
n_2 = float(input())
operation = input()

if operation == "+": print(n_1 + n_2)
elif operation == "-": print(n_1 - n_2)
elif operation == "*": print(n_1 * n_2)
elif operation == "/":
    if n_2 == 0: print("Деление на 0!")
    else: print(n_1 / n_2)
elif operation == "mod":
    if n_2 == 0: print("Деление на 0!")
    else: print(n_1 % n_2)
elif operation == "pow": print(n_1 ** n_2)
elif operation == "div":
    if n_2 == 0: print("Деление на 0!")
    else: print(n_1 // n_2)