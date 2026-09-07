ticket = input()
first_num_sum = sum(map(int, ticket[0:3]))
second_num_sum = sum(map(int, ticket[3:6]))
print("Счастливый" if first_num_sum == second_num_sum else "Обычный")
