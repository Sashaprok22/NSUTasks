def is_palindrome(s):
    return s == s[::-1]

text = input().lower()
print("YES" if is_palindrome(text) else "NO")