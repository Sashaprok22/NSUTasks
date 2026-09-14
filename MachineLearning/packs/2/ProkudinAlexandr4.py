rows = int(input())
matrix = []
result = []
for row in range(rows):
    col = list(map(int, input().split()))
    matrix.append(col)

    avg = sum(col) / len(col)
    big_nums = list(filter(lambda x: x > avg, col))
    result.append(len(big_nums))

for count in result:
    print(count)