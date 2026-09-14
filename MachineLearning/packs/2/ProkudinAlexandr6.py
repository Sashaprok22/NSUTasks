rows = int(input())
matrix = []
for row in range(rows):
    col = list(map(int, input().split()))
    matrix.append(col)

def check_matrix(matrix):
    for row in range(len(matrix)):
        for col in range(len(matrix)):
            if matrix[row][col] != matrix[col][row]:
                return False
    return True

print("YES" if check_matrix(matrix) else "NO")