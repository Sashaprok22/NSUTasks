def check_credit(salary, delays, debt):
    if salary <= 30_000: return False
    if delays <= 0: return True
    if debt > 10_000: return False
    return True

salary = int(input("Ваш доход: "))
delays = int(input("Кол-во просрочек: "))
debt = int(input("Задолженность: "))

print("дать кредит" if check_credit(salary, delays, debt) else "отказать")