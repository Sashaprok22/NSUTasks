correct_nums = list(map(int, input().split()))
check_nums = list(map(int, input().split()))

correct_count = 0
for (i, num) in enumerate(correct_nums):
    if num == check_nums[i]: correct_count += 1

print(correct_count / len(correct_nums))