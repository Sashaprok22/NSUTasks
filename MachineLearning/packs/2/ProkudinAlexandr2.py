nums = list(map(int, input().split()))
direction = input()
positions = int(input())
positions %= len(nums)
positions = -positions if direction == "R" else positions
new_nums = nums[positions:] + nums[:positions]
print(new_nums)