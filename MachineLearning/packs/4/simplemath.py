def add(*args):
    return sum(args)

def mul(*args):
    result = 1
    for v in args: result *= v
    return result

def power(a, b):
    return a ** b