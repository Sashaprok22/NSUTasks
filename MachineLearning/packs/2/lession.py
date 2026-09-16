def reverseStr():
    text = input()
    print(text[::-1])

def sunNums():
    nums = []
    n = int(input())
    while (n != 0):
        nums.append(n)
        n = int(input())
    print(sum(nums))

def printNumsSubSeq():
    count = int(input())
    currentI = 0
    while (count > 0):
        currentI += 1
        print(str(currentI) * min(count, currentI), end='')
        count -= currentI

def genom():
    gen = input().lower()
    gs = gen.count('g')
    cs = gen.count('c')
    print(gs, cs)
    print((gs+cs) / len(gen) * 100)

def sumFromStr():
    nums = map(int, input().split())
    print(sum(nums))

def moveList():
    nums = list(map(int, input().split()))
    nums.append(nums[0])
    nums.pop(0)

    nums.insert(0, nums[-1])
    nums.pop()

def printRepeats():
    nums = list(map(int, input().split()))
    numsCounts = {}
    for n in nums:
        numsCounts.setdefault(n, 0)
        numsCounts[n] += 1
        if (numsCounts[n] == 2): print(n)

def checkX():
    nums = list(map(int, input().split()))
    x = int(input())

    if (not (x in nums)):
        print("Отсутствует")
        return

    for (i, n) in enumerate(nums):
        if (n == x):
            print(i, end=' ')

def powerOfSet():
    n = int(input())
    result = []
    for i in range(n):
        result.append(list(range(1, i + 2)))
    print(result)

def matrixFunc():
    rows = int(input())
    matrix = []
    for i in range(rows):
        nums = list(map(int, input().split()))
        matrix.append(nums)

    diag = [matrix[i][i] for i in range(rows)]
    print(sum(diag))

