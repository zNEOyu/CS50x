from cs50 import get_int

h = 0
while h < 1 or h > 8:
    h = get_int("Height: ")

for i in range(h):
    for j in range(h - i - 1):
        print(" ", end="")
    for x in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for y in range(i + 1):
        print("#", end="")
    print()
