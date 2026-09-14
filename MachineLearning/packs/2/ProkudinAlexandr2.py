nums = list(map(int, input().split()))
direction = input()
positions = int(input())
positions = -positions if direction == "R" else positions
new_nums = nums[positions:] + nums[:positions]
print(new_nums)