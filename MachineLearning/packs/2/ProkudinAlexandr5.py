rows = int(input())
matrix = []
nums = []
for row in range(rows):
    col = list(map(int, input().split()))
    matrix.append(col)
    if row < rows / 2:
        nums.extend(col[:row + 1])
        nums.extend(col[-row - 1:])
    else:
        nums.extend(col[:rows - row])
        nums.extend(col[-(rows - row):])
print(max(nums))