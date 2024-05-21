text = input("Text: ")

l = 0
w = 1
s = 0

# check for letters
for i in range(len(text)):
    if text[i].isalpha():
        l += 1
# check for words
for i in range(len(text)):
    if text[i].isspace():
        w += 1
# check for setences
for i in range(len(text)):
    p = text[i]
    if p == '.' or p == '!' or p == '?':
        s += 1
# Compute the Coleman-Liau index
m = 100.00 * (l / w)

t = 100.00 * (s / w)

index = 0.0588 * m - 0.296 * t - 15.8

# Print the grade level
if 0 < round(index) and round(index) < 16:
    print(f"Grade {round(index)}")
elif 1 > round(index):
    print("Before Grade 1")
else:
    print("Grade 16+")
